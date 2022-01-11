#include "otiledbg.h"
#include "qpainter.h"
#include "qdebug.h"

OTiledBg::OTiledBg(QWidget *parent) : QWidget(parent)
{
    color1 = QColor(255, 255, 255);
    color2 = QColor(220, 220, 220);
    bgPix = QPixmap(64, 64);
    drawBg();
}

void OTiledBg::drawBg()
{
    bgPix.fill(color1);
    QPainter painter(&bgPix);
    painter.fillRect(0, 0, 32, 32, color2);
    painter.fillRect(32, 32, 32, 32, color2);
    painter.end();
    update();
}

void OTiledBg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawTiledPixmap(this->rect(), bgPix);
}

QColor OTiledBg::getColor1() const
{
    return this->color1;
}

QColor OTiledBg::getColor2() const
{
    return this->color2;
}

QPixmap OTiledBg::getBgPix() const
{
    return this->bgPix;
}

QSize OTiledBg::sizeHint() const
{
    return QSize(100,100);
}

QSize OTiledBg::minimumSizeHint() const
{
    return QSize(20,20);
}

void OTiledBg::setColor1(const QColor &color1)
{
    if (this->color1 != color1) {
        this->color1 = color1;
        drawBg();
    }
}

void OTiledBg::setColor2(const QColor &color2)
{
    if (this->color2 != color2) {
        this->color2 = color2;
        drawBg();
    }
}

void OTiledBg::setBgPix(const QPixmap &bgPix)
{
    this->bgPix = bgPix;
    update();
}

