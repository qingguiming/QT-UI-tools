#include "oscantantan.h"
#include <QPainter>
#include <QDebug>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMouseEvent>

OScanTanTan::OScanTanTan(QWidget *parent):QWidget(parent)
{
//    setMouseTracking(true);
    isPressed = false;
    imageRadius  = 40;
    scanDeg = 0;
    QPropertyAnimation *anim1 = new QPropertyAnimation(this, "");
    anim1->setStartValue(40);
    anim1->setEndValue(50);
    anim1->setDuration(300);
    QPropertyAnimation *anim2 = new QPropertyAnimation(this, "");
    anim2->setStartValue(50);
    anim2->setEndValue(30);
    anim2->setDuration(300);
    QPropertyAnimation *anim3 = new QPropertyAnimation(this, "");
    anim3->setStartValue(30);
    anim3->setEndValue(40);
    anim3->setDuration(300);

    animationGroup = new QSequentialAnimationGroup() ;
    animationGroup->addAnimation(anim1);
    animationGroup->addAnimation(anim2);
    animationGroup->addAnimation(anim3);

    connect(anim1, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    connect(anim2, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    connect(anim3, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    _timer = NULL;
    _timer = new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(changeScan()));
//    qDebug("_timer %p",_timer);
    _timer->setInterval(40);
//    qDebug("_timer end");


    _timer->start();

}

void OScanTanTan::mousePressEvent(QMouseEvent *event)
{

    qDebug()<<"mousePressEvent";
    if(!isPressed)
    {
        QPoint pressedPoint =  event->pos();
        QPointF realPos = pressedPoint - rect().center();

        QMatrix qMatrix;

        QRegion mEllipse = QRegion(-imageRadius, -imageRadius, imageRadius * 2, imageRadius * 2, QRegion::Ellipse);
        mEllipse = qMatrix.map(mEllipse);
        if( mEllipse.contains(realPos.toPoint()))
        {

            isPressed = true;
            RingData ring;
            ring.radius = imageRadius;
            ring.alpha = 255;
            ring.width = 3;
            rings.push_back(ring);
            //centerRingR = 40;
            animationGroup->start();
            update();


        }



    }
    QWidget::mousePressEvent(event);

}

void OScanTanTan::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"mouseReleaseEvent";

    if(isPressed)
    {
        isPressed = false;
        //centerRingR = 50;
        animationGroup->stop();
        update();
    }
    QWidget::mouseReleaseEvent(event);


}



void OScanTanTan::paintEvent(QPaintEvent *e)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.translate(width / 2, height / 2);
//    //painter.scale(side / 200.0, side / 200.0);

    //绘制扫描线
    drawScan(&painter);
    //绘制扩散圈
    drawRing(&painter);
    //绘制中间图片
    drawImage(&painter);

    QWidget::paintEvent(e);
}

void OScanTanTan::drawScan(QPainter *painter)
{
    painter->save();

    //锥形渐变颜色,通过透明度控制形成扫描效果
    QConicalGradient conicalGradient(0, 0, scanDeg);
    QColor color = scanColor;
    color.setAlpha(50);
    conicalGradient.setColorAt(0, color);
    color.setAlpha(0);
    conicalGradient.setColorAt(1, color);

    //设置画笔画刷
    QPen pen;
    pen.setWidth(scanWidth);
    pen.setBrush(conicalGradient);
    painter->setPen(pen);
    painter->setBrush(conicalGradient);

    //绘制饼圆
    QRect rect(-scanRadius, -scanRadius, scanRadius * 2, scanRadius * 2);
    painter->drawPie(rect, scanDeg * 16, 360 * 16);

    painter->restore();
}

void OScanTanTan::drawRing(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制所有扩散圈,扩散圈其实就是个没有背景颜色的圆形
    for (int i = 0; i < rings.count(); i++)
    {
        RingData ring = rings.at(i);
        int radius = ring.radius;
        float width = ring.width;
        int alpha = 255 - ring.alpha;
        QColor color = ringColor;
        color.setAlpha(50);

        QPen pen;
        pen.setWidthF(width);
        pen.setColor(color);
        painter->setPen(pen);
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    }

    painter->restore();
}

void OScanTanTan::drawImage(QPainter *painter)
{
    painter->save();

    //设置圆形遮罩路径,产生圆形头像效果
    QPainterPath path;
    path.addEllipse(QPoint(0, 0), imageRadius, imageRadius);
    painter->setClipPath(path);

    //绘制图片
    QRect rect(-imageRadius, -imageRadius, imageRadius * 2, imageRadius * 2);
    painter->drawPixmap(rect, image);

    //绘制图片边缘圆形
    QPen pen;
    pen.setWidth(imageBorderWidth);
    pen.setColor(imageBorderColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    //以下两种方法二选一,其实绘制360度的圆弧=绘制无背景的圆形
    //painter->drawArc(rect, 0, 360 * 16);
    painter->drawEllipse(rect);

    painter->restore();
}

void OScanTanTan::changeScan()
{
    changeRing();

    scanDeg += scanStep;
    if(scanDeg >= 360)
    {
        scanDeg = scanDeg - 360;
    }
    update();
}

void OScanTanTan::changeRing()
{

    for (int i = 0; i < rings.count(); i++)
    {
        rings[i].radius += ringStep;
    }

    for(QList<RingData>::iterator i = rings.begin();i != rings.end();i++)
    {
        if((*i).radius >= scanRadius)
        {
            rings.erase(i);
        }
    }
}


void OScanTanTan::updateImage(const QVariant &value)
{
    int currentValue = value.toInt();
    imageRadius = currentValue;
    update();
}

double OScanTanTan::twoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    return 0.0;
}

QPixmap OScanTanTan::getImage() const
{
    return image;

}

int OScanTanTan::getImageBorderWidth() const
{
    return imageBorderWidth;
}

QColor OScanTanTan::getImageBorderColor() const
{
    return imageBorderColor;
}

int OScanTanTan::getScanRadius() const
{
    return scanRadius;
}

int OScanTanTan::getScanWidth() const
{
    return scanWidth;
}

int OScanTanTan::getRingWidth() const
{
    return ringWidth;
}

int OScanTanTan::getScanStep() const
{
    return scanStep;
}

int OScanTanTan::getRingStep() const
{
    return ringStep;
}

QColor OScanTanTan::getScanColor() const
{
    return scanColor;
}

QColor OScanTanTan::getRingColor() const
{
    return ringColor;
}

QSize OScanTanTan::sizeHint() const
{
    return size();
}

QSize OScanTanTan::minimumSizeHint() const
{
    return minimumSize();
}

void OScanTanTan::setImage(const QPixmap &image)
{
    this->image = image;
}

void OScanTanTan::setImageBorderWidth(int imageBorderWidth)
{
    this->imageBorderWidth = imageBorderWidth;
}

void OScanTanTan::setImageBorderColor(const QColor &imageBorderColor)
{
    this->imageBorderColor = imageBorderColor;

}

void OScanTanTan::setScanRadius(int scanRadius)
{
    this->scanRadius = scanRadius;

}

void OScanTanTan::setScanWidth(int scanWidth)
{
    this->scanWidth = scanWidth;

}

void OScanTanTan::setRingWidth(int ringWidth)
{
    this->ringWidth = ringWidth;

}

void OScanTanTan::setScanStep(int scanStep)
{
    this->scanStep = scanStep;
}

void OScanTanTan::setRingStep(int ringStep)
{
    this->ringStep = ringStep;

}

void OScanTanTan::setScanColor(const QColor &scanColor)
{
    this->scanColor = scanColor;

}

void OScanTanTan::setRingColor(const QColor &ringColor)
{
    this->ringColor = ringColor;

}


