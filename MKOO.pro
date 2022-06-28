TARGET = MKOO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagewidget.cpp \
    histogram.cpp \
    lab.cpp \
    unsharpmask.cpp \
    gamma.cpp \
    xyz.cpp \
    gauss.cpp \
    liniowe.cpp \
    nieliniowe.cpp \
    cmyk.cpp \
    hsl.cpp \
    fft.cpp

HEADERS  += mainwindow.h \
    imagewidget.h \
    histogram.h \
    lab.h \
    unsharpmask.h \
    gamma.h \
    xyz.h \
    gauss.h \
    liniowe.h \
    nieliniowe.h \
    cmyk.h \
    hsl.h \
    fft.h

FORMS    += mainwindow.ui \
    histogram.ui \
    lab.ui \
    unsharpmask.ui \
    gamma.ui \
    xyz.ui \
    gauss.ui \
    liniowe.ui \
    nieliniowe.ui \
    cmyk.ui \
    hsl.ui \
    fft.ui

LIBS += -L/usr/lib -lfftw3
INCLUDEPATH += -I/usr/include/





































