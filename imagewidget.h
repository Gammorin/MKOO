#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include <QtGui>
#include <QFileDialog>
#include <QString>
#include <QImage>


class imagewidget : public QWidget
{

        public:
                QImage image;
                imagewidget();
                void setImage(QImage);
                void removeImage();
                QImage* getImage() { return &image; }


        protected:
                void paintEvent(QPaintEvent*);
};

#endif // IMAGEW_H
