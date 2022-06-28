#include "fft.h"
#include "ui_fft.h"

#include <QLabel>
#include <QImage>
#include <fftw3.h>

FourierTransformVisualisation::FourierTransformVisualisation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FourierTransformVisualisation)
{
    ui->setupUi(this);
    //    QLabel redLabel(tr("Red"));
    //    QLabel redPhaseLabel(tr("Phase"));
    //    QLabel redMagnitudeLabel(tr("Magnitude"));
    //    redPhase = new imagewidget();
    //    redMagnitude = new imagewidget();
    //    ui->gridLayout->addWidget(&redLabel, 0, 0) ;
    //    ui->gridLayout->addWidget(&redPhaseLabel, 1, 0);
    //    ui->gridLayout->addWidget(&redMagnitudeLabel, 1, 1);
    //    ui->gridLayout->addWidget(redPhase, 2, 0);
    //    ui->gridLayout->addWidget(redMagnitude, 2, 1);

    //    //

    //    int W, H;
    //    QImage imageRedPhase(W, H, QImage::Format_RGB32);

    //    fftw_complex ∗in;
    //    fftw_complex ∗out;




    //-------------

    setWindowTitle("Transformata Furiera");


    setMinimumSize(1050,900);

    iwFazaRed = new imagewidget();
    iwModulRed = new imagewidget();
    iwFazaGreen = new imagewidget();
    iwModulGreen = new imagewidget();
    iwFazaBlue = new imagewidget();
    iwModulBlue = new imagewidget();

    int i = 0;

    ui->gridLayout->addWidget(new QLabel(tr("Red"), this), i, 0);
    i++;
    ui->gridLayout->addWidget(new QLabel(tr("Faza"), this), i, 0);
    ui->gridLayout->addWidget(new QLabel(tr("Modul"), this), i, 1);
    i++;
    ui->gridLayout->addWidget(iwFazaRed, i, 0);
    ui->gridLayout->addWidget(iwModulRed, i, 1);
    i++;
    ui->gridLayout->addWidget(new QLabel(tr("Green"), this), i, 0);
    i++;
    ui->gridLayout->addWidget(new QLabel(tr("Faza"), this), i, 0);
    ui->gridLayout->addWidget(new QLabel(tr("Modul"), this), i, 1);
    i++;
    ui->gridLayout->addWidget(iwFazaGreen, i, 0);
    ui->gridLayout->addWidget(iwModulGreen, i, 1);
    i++;
    ui->gridLayout->addWidget(new QLabel(tr("Blue"), this), i, 0);
    i++;
    ui->gridLayout->addWidget(new QLabel(tr("Faza"), this), i, 0);
    ui->gridLayout->addWidget(new QLabel(tr("Modul"), this), i, 1);
    i++;
    ui->gridLayout->addWidget(iwFazaBlue, i, 0);
    ui->gridLayout->addWidget(iwModulBlue, i, 1);


}

FourierTransformVisualisation::~FourierTransformVisualisation()
{
    delete ui;
}

void FourierTransformVisualisation::setImage(QImage *im)
{
    image = im;
    tImage = *im;
}


void FourierTransformVisualisation::updateTransformata()
{

    int W = image->width();
    int H = image->height();
    iwFazaRed->setMinimumSize(W, H);
    iwFazaRed->setMaximumSize(W, H);
    iwModulRed->setMinimumSize(W, H);
    iwModulRed->setMaximumSize(W, H);
    iwFazaGreen->setMinimumSize(W, H);
    iwFazaGreen->setMaximumSize(W, H);
    iwModulGreen->setMinimumSize(W, H);
    iwModulGreen->setMaximumSize(W, H);
    iwFazaBlue->setMinimumSize(W, H);
    iwFazaBlue->setMaximumSize(W, H);
    iwModulBlue->setMinimumSize(W, H);
    iwModulBlue->setMaximumSize(W, H);

    const uchar MaxRGB = 255;

    QRgb* pixels = (QRgb*) image->bits();

    fftw_complex *inR , *outR;

    inR = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;
    outR = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;

    for (int i = 0; i < W * H; i++)

    {
        inR[i][0] = qRed(pixels[i]);
        inR[i][1] = 0 ;

    }

    fftw_plan planR = fftw_plan_dft_2d (H, W, inR , outR , FFTW_FORWARD, FFTW_ESTIMATE) ;
    fftw_execute(planR);
    fftw_destroy_plan(planR);


    QImage phaseRImage(W, H, QImage::Format_RGB32);
    QImage magnitudeRImage(W, H, QImage::Format_RGB32);


    QRgb* phaseRPixels = (QRgb*)phaseRImage.bits();

    for(int i = 0; i < H * W; i++)

    {

        double realR = outR[i][0];
        double imagR = outR[i][1];
        double phaseR = atan(imagR / realR);
        uchar scaledPhaseR = ((phaseR  + M_PI / 2) * MaxRGB) / M_PI;
        phaseRPixels[i] = qRgb(scaledPhaseR, scaledPhaseR, scaledPhaseR); //skalowanie wartośc fazy

    }

    zmianaCw(&phaseRImage);
    QRgb* magnitudeRPixels = (QRgb*)magnitudeRImage.bits();
    double* magRValues = new double[W*H];
    for(int i = 0; i < H * W; i++)

    {

        double realR = outR[i][0];
        double imagR = outR[i][1];
        double magR = sqrt((realR * realR) + (imagR * imagR));

        magR = log(magR + 1);
        magRValues[i] = magR;

    }

    double maxModul = magRValues[0];
    double minModul = magRValues[0];

    for(int i = 1; i < H * W; i++)
    {
        if (magRValues[i] > maxModul)
            maxModul = magRValues[i];
        if (magRValues[i] < minModul)
            minModul = magRValues[i];
    }


    for(int i = 0; i < W *H; i++)

    {
        magRValues[i] = (magRValues[i] - minModul)*255/(maxModul - minModul); //skalowanie wartości modułu
        magnitudeRPixels[i] = qRgb(magRValues[i], magRValues[i], magRValues[i]);
    }


    delete[] magRValues;
    zmianaCw(&magnitudeRImage);


    fftw_free(inR);
    fftw_free(outR);


    iwFazaRed->setImage(phaseRImage);
    iwModulRed->setImage(magnitudeRImage);


    //green początek

    fftw_complex *inG, *outG;
    inG = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;
    outG = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;


    for (int i = 0; i < W * H; i++)
    {
        inG[i][0] = qGreen(pixels[i]);
        inG[i][1] = 0 ;
    }


    fftw_plan planG = fftw_plan_dft_2d (H, W, inG , outG , FFTW_FORWARD, FFTW_ESTIMATE) ;
    fftw_execute(planG);
    fftw_destroy_plan(planG);


    QImage phaseGImage(W, H, QImage::Format_RGB32);
    QRgb* phaseGPixels = (QRgb*)phaseGImage.bits();

    for(int i = 0; i < H * W; i++)
    {
        double realG = outG[i][0];
        double imagG = outG[i][1];
        double phaseG = atan(imagG / realG);
        uchar scaledPhaseG = ((phaseG + M_PI / 2) * MaxRGB) / M_PI;
        phaseGPixels[i] = qRgb(scaledPhaseG, scaledPhaseG, scaledPhaseG);
    }

    zmianaCw(&phaseGImage);
    QImage magnitudeGImage(W, H, QImage::Format_RGB32);
    QRgb* magnitudeGPixels = (QRgb*)magnitudeGImage.bits();

    double* magGValues = new double[W*H];

    for(int i = 0; i < H * W; i++)
    {
        double realG = outG[i][0];
        double imagG = outG[i][1];
        double magG = sqrt(realG * realG + imagG * imagG);
        magG = log(magG + 1);
        magGValues[i] = magG;
    }

    double maxModulG = magGValues[0];
    double minModulG = magGValues[0];

    for(int i = 0; i < H * W; i++)
    {
        if (magGValues[i] > maxModulG)
            maxModulG = magGValues[i];

        if (magGValues[i] < minModulG)
            minModulG = magGValues[i];
    }

    for(int i = 0; i < W *H; i++)
    {
        magGValues[i] = (magGValues[i] - minModulG)*255/(maxModulG - minModulG); //skalowanie wartości modułu
        magnitudeGPixels[i] = qRgb(magGValues[i], magGValues[i], magGValues[i]);
    }

    delete[] magGValues;
    zmianaCw(&magnitudeGImage);


    fftw_free(inG);
    fftw_free(outG);

    iwFazaGreen->setImage(phaseGImage);
    iwModulGreen->setImage(magnitudeGImage);

    //green koniec

    //blue początek

    fftw_complex *inB, *outB;
    inB = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;
    outB = (fftw_complex*) fftw_malloc (sizeof(fftw_complex) * W * H) ;

    for (int i = 0; i < W * H; i++)

    {
        inB[i][0] = qBlue(pixels[i]);
        inB[i][1] = 0 ;

    }

    fftw_plan planB = fftw_plan_dft_2d (H, W, inB , outB , FFTW_FORWARD, FFTW_ESTIMATE) ;
    fftw_execute(planB);
    fftw_destroy_plan(planB);

    QImage phaseBImage(W, H, QImage::Format_RGB32);
    QRgb* phaseBPixels = (QRgb*)phaseBImage.bits();

    for(int i = 0; i < H * W; i++)

    {

        double realB = outB[i][0];
        double imagB = outB[i][1];
        double phaseB = atan(imagB / realB);
        uchar scaledPhaseB = ((phaseB + M_PI / 2) * MaxRGB) / M_PI;
        phaseBPixels[i] = qRgb(scaledPhaseB, scaledPhaseB, scaledPhaseB);

    }

    zmianaCw(&phaseBImage);
    QImage magnitudeBImage(W, H, QImage::Format_RGB32);
    QRgb* magnitudeBPixels = (QRgb*)magnitudeBImage.bits();
    double* magBValues = new double[W*H];

    for(int i = 0; i < H * W; i++)

    {

        double realB = outB[i][0];
        double imagB = outB[i][1];
        double magB = sqrt(realB * realB + imagB * imagB);
        magB = log(magB + 1);
        magBValues[i] = magB;

    }

    double maxModulB = magBValues[0];
    double minModulB = magBValues[0];

    for(int i = 0; i < H * W; i++)
    {

        if (magBValues[i] > maxModulB)
            maxModulB = magBValues[i];

        if (magBValues[i] < minModulB)
            minModulB = magBValues[i];
    }

    for(int i = 0; i < W * H; i++)
    {
        magBValues[i] = (magBValues[i] - minModulB)*255/(maxModulB - minModulB); //skalowanie wartości modułu
        magnitudeBPixels[i] = qRgb(magBValues[i], magBValues[i], magBValues[i]);
    }

    delete[] magBValues;
    zmianaCw(&magnitudeBImage);
    fftw_free(inB);
    fftw_free(outB);
    iwFazaBlue->setImage(phaseBImage);
    iwModulBlue->setImage(magnitudeBImage);
}


void FourierTransformVisualisation::zmianaCw(QImage *image)

{

    int W = image->width();
    int H = image->height();
    int srodekX = W / 2 + ((W % 2) == 1 ? 1 : 0);
    int srodekY = H / 2 + ((H % 2) == 1 ? 1 : 0);

    for(int i = 0; i < H / 2; i++)
    {
        QRgb* pixels1 = (QRgb*)image->scanLine(i);
        QRgb* pixels2 = (QRgb*)image->scanLine(i + srodekY);

        for(int j = 0; j < W /2; j++)
        {
            std::swap(pixels1[j], pixels2[j + srodekX]);
        }
    }

    for(int i = 0; i < H / 2; i++)

    {
        QRgb* pixels1 = (QRgb*)image->scanLine(i);
        QRgb* pixels2 = (QRgb*)image->scanLine(i + srodekY);

        for(int j = 0; j < W /2; j++)
        {
            std::swap(pixels1[j + srodekX], pixels2[j]);
        }
    }
}

