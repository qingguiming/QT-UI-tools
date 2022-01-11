#include "ogaugeclock.h"
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QtGlobal>
#include <QDebug>
#include <QtMath>

OGaugeClock::OGaugeClock(QWidget *parent) :
    QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,[=](){

        QTime t = QTime::currentTime();
        hour = t.hour();
        min = t.minute();
        sec = t.second();
        update();

    });
    timer->start();
}

OGaugeClock::~OGaugeClock()
{

}

void OGaugeClock::paintEvent(QPaintEvent *)
{


    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框
    drawCrown(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制时钟指针
    drawHour(&painter);
    //绘制分钟指针
    drawMin(&painter);
    //绘制秒钟指针
    drawSec(&painter);
    //绘制中心盖板

}

void OGaugeClock::drawCrown(QPainter *painter)
{
    int radius = 99;
        painter->save();
        painter->setPen(Qt::NoPen);
        QLinearGradient crownGradient(0, -radius, 0, radius);
        crownGradient.setColorAt(0, crownColorStart);
        crownGradient.setColorAt(1, crownColorEnd);
        painter->setBrush(crownGradient);
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        painter->restore();

}

void OGaugeClock::drawBg(QPainter *painter)
{
    int radius = 92;
       painter->save();
       painter->setPen(Qt::NoPen);
       painter->setBrush(background);
       painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
       painter->restore();

}

void OGaugeClock::drawScale(QPainter *painter)
{
    int radius = 90;
        painter->save();

        QPen pen;
        pen.setColor(foreground);
        pen.setCapStyle(Qt::RoundCap);

        for (int i = 0; i <= 60; i++) {
            if (i % 5 == 0) {
                pen.setWidthF(1.5);
                painter->setPen(pen);
                painter->drawLine(0, radius - 10, 0, radius);
            } else {
                pen.setWidthF(0.5);
                painter->setPen(pen);
                painter->drawLine(0, radius - 5, 0, radius);
            }

            painter->rotate(6);
        }

        painter->restore();

}

void OGaugeClock::drawScaleNum(QPainter *painter)
{
    int radius = 70;
        painter->save();
        painter->setPen(foreground);

        double startRad = 60 * (M_PI / 180);
        double deltaRad = 30 * (M_PI / 180);

        for (int i = 0; i < 12; i++) {
            double sina = qSin(startRad - i * deltaRad);
            double cosa = qCos(startRad - i * deltaRad);
            QString strValue = QString("%1").arg(i + 1);

            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();
            int x = radius * cosa - textWidth / 2;
            int y = -radius * sina + textHeight / 4;
            painter->drawText(x, y, strValue);
        }

        painter->restore();

}

void OGaugeClock::drawHour(QPainter *painter)
{
    painter->save();

        //设置画笔平滑圆角
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pointerHourColor);
        painter->setBrush(pointerHourColor);

        QPolygon pts;
        pts.setPoints(4, -3, 8, 3, 8, 2, -40, -2, -40);

        painter->rotate(30.0 * ((hour + min / 60.0)));
        painter->drawConvexPolygon(pts);

        painter->restore();

}

void OGaugeClock::drawMin(QPainter *painter)
{
    painter->save();

        //设置画笔平滑圆角
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pointerMinColor);
        painter->setBrush(pointerMinColor);

        QPolygon pts;
        pts.setPoints(4, -2, 8, 2, 8, 1, -60, -1, -60);

        painter->rotate(6.0 * (min + sec / 60.0));
        painter->drawConvexPolygon(pts);

        painter->restore();

}

void OGaugeClock::drawSec(QPainter *painter)
{
    if (secondStyle == SecondStyle_Hide) {
            return;
        }

        painter->save();

        //设置画笔平滑圆角
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pointerSecColor);
        painter->setBrush(pointerSecColor);

        QPolygon pts;
        pts.setPoints(3, -1, 10, 1, 10, 0, -70);

        painter->rotate(6 * sec);
        painter->drawConvexPolygon(pts);

        painter->restore();




}

void OGaugeClock::drawDot(QPainter *painter)
{
    painter->save();
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, background);
    coneGradient.setColorAt(0.5, foreground);
    coneGradient.setColorAt(1.0, background);
    painter->setOpacity(0.9);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->restore();
}

void OGaugeClock::doAction()
{

}

void OGaugeClock::updateTime()
{

}

void OGaugeClock::updateSpring()
{

}

OGaugeClock::SecondStyle OGaugeClock::getSecondStyle() const
{
    return secondStyle;
}

QColor OGaugeClock::getCrownColorStart() const
{
    return crownColorStart;
}

QColor OGaugeClock::getCrownColorEnd() const
{
    return crownColorEnd;
}

QColor OGaugeClock::getForeground() const
{
    return foreground;
}

QColor OGaugeClock::getBackground() const
{
    return background;
}

QColor OGaugeClock::getPointerHourColor() const
{
    return pointerHourColor;
}

QColor OGaugeClock::getPointerMinColor() const
{
    return pointerMinColor;
}

QColor OGaugeClock::getPointerSecColor() const
{
    return pointerSecColor;
}

QSize OGaugeClock::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OGaugeClock::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();

}

void OGaugeClock::setSecondStyle(const OGaugeClock::SecondStyle &secondStyle)
{
    this->secondStyle = secondStyle;
}

void OGaugeClock::setSystemDateTime(const QString &year, const QString &month, const QString &day, const QString &hour, const QString &min, const QString &sec)
{
    //todo
}

void OGaugeClock::setCrownColorStart(const QColor &crownColorStart)
{
    this->crownColorStart = crownColorStart;

}

void OGaugeClock::setCrownColorEnd(const QColor &crownColorEnd)
{
    this->crownColorEnd = crownColorEnd;

}

void OGaugeClock::setForeground(const QColor &foreground)
{
    this->foreground = foreground;

}

void OGaugeClock::setBackground(const QColor &background)
{
    this->background = background;

}

void OGaugeClock::setPointerHourColor(const QColor &pointerHourColor)
{
    this->pointerHourColor = pointerHourColor;

}

void OGaugeClock::setPointerMinColor(const QColor &pointerMinColor)
{
    this->pointerMinColor = pointerMinColor;

}

void OGaugeClock::setPointerSecColor(const QColor &pointerSecColor)
{
    this->pointerSecColor = pointerSecColor;

}
