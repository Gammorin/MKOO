#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QImage>
#include "imagewidget.h"
#include "gamma.h"
#include "histogram.h"
#include "cmyk.h"
#include "hsl.h"
#include "xyz.h"
#include "lab.h"
#include "liniowe.h"
#include "nieliniowe.h"
#include "gauss.h"
#include "unsharpmask.h"
#include "fft.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow *ui;

    imagewidget *widget;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

public slots:
    void otworz();
    void zamknijPlik();
    void jasnkongamma();
    void histr();
    void rgb_to_cmyk();
    void rgb_to_hsl();
    void cie_xyz();
    void lab();
    void filtry_liniowe();
    void filtry_nieliniowe();
    void filtrGaussa();
    void umask();
    void furier();

};

#endif // MAINWINDOW_H
