#ifndef FILTRY_NIELINIOWE_H
#define FILTRY_NIELINIOWE_H

#include <QWidget>

namespace Ui {
class Filtry_Nieliniowe;
}

class Filtry_Nieliniowe : public QWidget
{
    Q_OBJECT
    
public:
    explicit Filtry_Nieliniowe(QWidget *parent = 0);
    ~Filtry_Nieliniowe();
     void setImage(QImage*);
    
private:
    Ui::Filtry_Nieliniowe *ui;
    QImage *image,tmpImage,tmpImage2;

public slots:
    void cancel();
    void maximum();
    void minimum();
    void mediana();

signals:
    void sigUpdateImage();
};

#endif // FILTRY_NIELINIOWE_H
