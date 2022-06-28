#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("MKOO");

    connect(ui->actionOtworz, SIGNAL(triggered()), this, SLOT(otworz()));
    connect(ui->actionZamknij, SIGNAL(triggered()), this, SLOT(zamknijPlik()));
    connect(ui->actionWyjscie,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionJasnosc_Kontrast_Gamma, SIGNAL(triggered()), this, SLOT(jasnkongamma()));
    connect(ui->actionHistogram, SIGNAL(triggered()), this, SLOT(histr()));
    connect(ui->actionRGB_CMYK, SIGNAL(triggered()),this, SLOT(rgb_to_cmyk()));
    connect(ui->actionRGB_HSL, SIGNAL(triggered()), this, SLOT(rgb_to_hsl()));
    connect(ui->actionCIE_XYZ, SIGNAL(triggered()), this, SLOT(cie_xyz()));
    connect(ui->actionLAB, SIGNAL(triggered()), this, SLOT(lab()));
    connect(ui->actionFiltry_liniowe_2, SIGNAL(triggered()), this, SLOT(filtry_liniowe()));
    connect(ui->actionFiltr_Gaussa_2, SIGNAL(triggered()), this, SLOT(filtrGaussa()));
    connect(ui->actionFiltry_nieliniowe_2, SIGNAL(triggered()), this, SLOT(filtry_nieliniowe()));
    connect(ui->actionUnsharpMask, SIGNAL(triggered()), this, SLOT(umask()));
    connect(ui->actionFourier, SIGNAL(triggered()), this, SLOT(furier()));

    ui->actionZamknij->setEnabled(false);
    ui->menuEdycja->setEnabled(false);
    ui->menuFiltry->setEnabled(false);
    ui->menuWizualizacja->setEnabled(false);

    widget = new imagewidget();
    setCentralWidget(widget);
   }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow:: otworz(){
    QString fname = QFileDialog::getOpenFileName(this, tr("Open image file"),"",tr("Images (*.png *.jpg *.xpm *.bmp);;All Files (*.*)"));
    if(!fname.isEmpty() && !fname.isNull())
    {
        QImage image = QImage(fname);

        if(!image.isNull())
        {
            widget->setImage(image);
            ui->menuEdycja->setEnabled(true);
            ui->menuFiltry->setEnabled(true);
            ui->menuWizualizacja->setEnabled(true);
            ui->actionZamknij->setEnabled(true);
        }
    }
}

void MainWindow::zamknijPlik()
{
    widget->removeImage();
    ui->actionZamknij->setEnabled(false);
    ui->menuEdycja->setEnabled(false);
    ui->menuWizualizacja->setEnabled(false);
    ui->menuFiltry->setEnabled(false);
}


void MainWindow:: jasnkongamma(){
    bcdkorekcja *ob = new bcdkorekcja();
    connect(ob, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    ob->setImage(widget->getImage());
    ob->show();

}
void MainWindow::histr(){
    histogram *obiekt = new histogram();
    connect(obiekt, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    obiekt->setImage(widget->getImage());
    obiekt->zczytaj(widget->getImage());
    obiekt->show();
}
void MainWindow::rgb_to_cmyk(){
    rgb_na_cmyk *obiekt3 = new rgb_na_cmyk();
    connect(obiekt3, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    obiekt3->setImage(widget->getImage());
    obiekt3->show();
}

void MainWindow::rgb_to_hsl(){
    rgb_na_hsl *ob_hsl = new rgb_na_hsl();
    connect(ob_hsl, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    ob_hsl->setImage(widget->getImage());
    ob_hsl->show();
}

void MainWindow::cie_xyz(){
    CIE *xyz = new CIE();
    connect(xyz, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    xyz->setImage(widget->getImage());
    xyz->show();
}

void MainWindow::lab(){
    Lab *la = new Lab();
    connect(la, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    la->setImage(widget->getImage());
    la->show();
}

void MainWindow::umask(){
    UnsharpMask *un = new UnsharpMask();
    connect(un, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    un->setImage(widget->getImage());
    un->show();
}

void MainWindow::filtry_liniowe(){
    Filtry_Liniowe *fi = new Filtry_Liniowe();
    connect(fi, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    fi->setImage(widget->getImage());
    fi->show();
}

void MainWindow::filtry_nieliniowe(){
    Filtry_Nieliniowe *fil = new Filtry_Nieliniowe();
    connect(fil, SIGNAL(sigUpdateImage()), widget, SLOT(update()));
    fil->setImage(widget->getImage());
    fil->show();
}

void MainWindow::filtrGaussa(){
    Filtr_Gaussa *g = new Filtr_Gaussa();
    connect(g,SIGNAL(sigUpdateImage()), widget , SLOT(update()));
    g->setImage(widget->getImage());
    g->show();
}
void MainWindow::furier(){
    FourierTransformVisualisation *ws = new FourierTransformVisualisation();
    ws->setImage(widget->getImage());
    ws->show();
    ws->updateTransformata();

}

