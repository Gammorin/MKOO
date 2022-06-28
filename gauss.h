#ifndef FILTR_GAUSSA_H
#define FILTR_GAUSSA_H

#include <QtGui/QWidget>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

#include <iostream>
using namespace std;


namespace Ui {
    class Filtr_Gaussa;
}

class Filtr_Gaussa : public QWidget {
    Q_OBJECT
public:
    Filtr_Gaussa(QWidget *parent = 0);
    ~Filtr_Gaussa();
    void setImage(QImage*);
     QColor ustawKolor(int, QColor**, int**, int);

private:
    Ui::Filtr_Gaussa *ui;
    QImage *obrazek,tmpObrazek,tmpObrazek2;
    QString str;

public slots:
    void zresetuj();
    void oblicz();

signals:
    void sigUpdateImage();
};
#endif // FILTR_GAUSSA_H
