#include "oimageanimation.h"
#include <QPropertyAnimation>
#include <QPainter>

OImageAnimation::OImageAnimation(QWidget *parent) :
    QWidget(parent)
{
    factor = 0.0;
    imageName1 = "";
    imageName2 = "";
    animationType = FlipRightToLeft;

    animation = new QPropertyAnimation(this,"ani");
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setDuration(2000);
    connect(animation,&QPropertyAnimation::valueChanged,this,&OImageAnimation::factorUpdate);

    //QPropertyAnimation *animation;  //动画属性
}

void OImageAnimation::paintEvent(QPaintEvent *)
{
    if (pixmap1.isNull() || pixmap2.isNull()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    switch (animationType) {
    case 0:
        fadeEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 1:
        blindsEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 2:
        flipRightToLeft(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 3:
        outsideToInside(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 4:
        moveLeftToRightEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 5:
        moveRightToLeftEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 6:
        moveBottomToUpEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 7:
        moveUpToBottomEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    case 8:
        moveBottomToLeftUpEffect(&painter, geometry(), factor, pixmap1, pixmap2);
        break;
    default:
        break;
    }
}

void OImageAnimation::fadeEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    int w = rect.width();
    int h = rect.height();
    int alpha = 255 * (1.0f - factor);

    QPixmap alphaPixmap(pixmap1.size());
    alphaPixmap.fill(Qt::transparent);

    QPainter p1(&alphaPixmap);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pixmap1);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(alphaPixmap.rect(), QColor(0, 0, 0, alpha));
    p1.end();

    int x = (w - pixmap1.width()) / 2;
    int y = (h - pixmap1.height()) / 2;
    painter->drawPixmap(x, y, alphaPixmap);

    alpha = 255 * (factor);
    alphaPixmap.fill(Qt::transparent);
    QPainter p2(&alphaPixmap);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0, 0, pixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(alphaPixmap.rect(), QColor(0, 0, 0, alpha));
    p2.end();

    painter->drawPixmap(x, y, alphaPixmap);
}

void OImageAnimation::blindsEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    int i, n, w, h, x1, y1, x2, y2, dh, ddh;

    w = rect.width();
    h = rect.height();
    x1 = (w - pixmap1.width()) / 2;
    y1 = (h - pixmap1.height()) / 2;
    x2 = (w - pixmap2.width()) / 2;
    y2 = (h - pixmap2.height()) / 2;

    painter->drawPixmap(x1, y1, pixmap1);

    n = 10;
    dh = pixmap2.height() / n;
    ddh = factor * dh;
    if (ddh < 1) {
        ddh = 1;
    }

    for(i = 0; i < n; i++) {
        painter->drawPixmap(x2, y2 + i * dh, pixmap2, 0, i * dh, pixmap2.width(), ddh);
    }
}

void OImageAnimation::flipRightToLeft(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    int x1, y1, x2, y2, w, h;
    float rot;
    QTransform trans;

    w = rect.width();
    h = rect.height();
    x1 = (w - pixmap1.width()) / 2;
    y1 = (h - pixmap1.height()) / 2;
    x2 = (w - pixmap2.width()) / 2;
    y2 = (h - pixmap2.height()) / 2;

    rot = factor * 90.0f;
    trans.translate(w * (1 - factor), h / 2);
    trans.rotate(rot, Qt::YAxis);
    trans.translate(-w, -h / 2);

    painter->setTransform(trans);
    painter->drawPixmap(x1, y1, pixmap1);
    painter->resetTransform();

    trans.reset();
    rot = 90 * (factor - 1);
    trans.translate(w * (1 - factor), h / 2);
    trans.rotate(rot, Qt::YAxis);
    trans.translate(0, -h / 2);

    painter->setTransform(trans);
    painter->drawPixmap(x2, y2, pixmap2);
    painter->resetTransform();
}

void OImageAnimation::outsideToInside(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    int   w, h, x1, y1, x2, y2, x3, y3, dh, ddh;

    w = rect.width();
    h = rect.height();
    x1 = (w - pixmap1.width()) / 2;
    y1 = (h - pixmap1.height()) / 2;
    painter->drawPixmap(x1, y1, pixmap1);

    dh = pixmap2.height() / 2;
    ddh = factor * dh;
    if (ddh < 1) {
        ddh = 1;
    }

    x2 = (w - pixmap2.width()) / 2;
    y2 = (h - pixmap2.height()) / 2;
    painter->drawPixmap(x2, y2, pixmap2, 0, 0, pixmap2.width(), ddh);

    x3 = (w - pixmap2.width()) / 2;
    y3 =  dh * (1.0f - factor) + h / 2;
    if(y3 != h / 2) {
        y3 += 1;
    }

    painter->drawPixmap(x3, y3, pixmap2, 0, pixmap2.height() - ddh, pixmap2.width(), ddh);
}

void OImageAnimation::moveLeftToRightEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    int x, y, w, h, x1, y1, x2, y2;

    w = rect.width();
    h = rect.height();
    x1 = (w - pixmap1.width()) / 2;
    y1 = (h - pixmap1.height()) / 2;
    x2 = (w - pixmap2.width()) / 2;
    y2 = (h - pixmap2.height()) / 2;

    x = x1 + w * factor;
    y = y1;
    painter->drawPixmap(x, y, pixmap1);

    x = x2 + w * (factor - 1);
    y = y2;
    painter->drawPixmap(x, y, pixmap2);
}

void OImageAnimation::moveRightToLeftEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{

}

void OImageAnimation::moveBottomToUpEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{

}

void OImageAnimation::moveUpToBottomEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{

}

void OImageAnimation::moveBottomToLeftUpEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
{

}

float OImageAnimation::getFactor() const
{
    return factor;
}

QString OImageAnimation::getImageName1() const
{
    return imageName1;
}

QString OImageAnimation::getImageName2() const
{
    return imageName2;
}

QPixmap OImageAnimation::getPixmap1() const
{
    return pixmap1;
}

QPixmap OImageAnimation::getPixmap2() const
{
    return pixmap2;

}

OImageAnimation::AnimationType OImageAnimation::getAnimationType() const
{
    return animationType;
}

QSize OImageAnimation::sizeHint() const
{
    return QSize(200,150);
}

QSize OImageAnimation::minimumSizeHint() const
{
    return QSize(200,150);

}

void OImageAnimation::factorUpdate(const QVariant &var)
{
    float temp = var.toFloat();
    this->factor = temp;
    update();

}

void OImageAnimation::setFactor(float factor)
{
    this->factor = factor;
}

void OImageAnimation::setImageName1(const QString &imageName1)
{
    this->imageName1 = imageName1;

}

void OImageAnimation::setImageName2(const QString &imageName2)
{
    this->imageName2 = imageName2;

}

void OImageAnimation::setPixmap1(const QPixmap &pixmap1)
{
    this->pixmap1 = pixmap1;

}

void OImageAnimation::setPixmap2(const QPixmap &pixmap2)
{
    this->pixmap2 = pixmap2;

}

void OImageAnimation::setAnimationType(const OImageAnimation::AnimationType &animationType)
{
    this->animationType = animationType;

}

void OImageAnimation::start()
{
    animation->start();
}

void OImageAnimation::stop()
{
    animation->stop();
}

