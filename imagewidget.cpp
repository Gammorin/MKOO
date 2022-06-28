#include "imagewidget.h"

imagewidget::imagewidget(){
    image = QImage();
}

void imagewidget::setImage(QImage im){
    image = im;
    update();
}

void imagewidget::removeImage(){
    image = QImage();
    update();
}

// chyba niepotrzebne na razie: ----------------------
void imagewidget::paintEvent(QPaintEvent*){
    QPainter paint(this);
    if(!image.isNull())
    paint.drawImage(0, 0, image);

//-------------------------------------------------
}
