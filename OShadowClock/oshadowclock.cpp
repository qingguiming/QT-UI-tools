#include "oshadowclock.h"
#include <QTimer>
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QTime>


OShadowClock::OShadowClock(QWidget *parent) :
    QWidget(parent)
{
    radiusWidth = 3;
    shadowWidth = 5;

    textColor = Qt::blue;
    shadowColor = Qt::cyan;

    QTimer* timer = new QTimer();
    timer->setInterval(1000);

    connect(timer,&QTimer::timeout,this,[=](){
        update();
    });

    timer->start();


}

OShadowClock::~OShadowClock()
{

}

void OShadowClock::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int w = this->width() / 2;
    int h = this->height() / 2;

    int radius = qMin(w,h);

    painter.translate(w,h);

    QTime time = QTime::currentTime();
    //秒
    drawArc(&painter,radius,time.second() * 6);

    drawArc(&painter,radius - 20,time.minute() * 6);


    drawArc(&painter,radius - 10,time.hour() * 15);

    drawText(&painter);

}

void OShadowClock::drawArc(QPainter *painter, int radius, qreal angle)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int smallradius = radius - radiusWidth;
    int maxRaidus = radius + shadowWidth;
    int minRadius = smallradius - shadowWidth;

    //采用圆形渐变,形成光晕效果
    QRadialGradient radialGradient(QPointF(0, 0), maxRaidus);
    QColor color = shadowColor;
    QColor lightColor = shadowColor.lighter(100);

    color.setAlphaF(0);
    radialGradient.setColorAt(0, color);
    radialGradient.setColorAt(minRadius * 1.0 / maxRaidus, color);
    color.setAlphaF(0.5);
    radialGradient.setColorAt(smallradius * 1.0 / maxRaidus, color);

    radialGradient.setColorAt((smallradius + 1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt((radius - 1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt(radius * 1.0 / maxRaidus, color);
    color.setAlphaF(0);
    radialGradient.setColorAt(1, color);

    painter->setBrush(radialGradient);
    painter->drawPie(-maxRaidus, -maxRaidus, maxRaidus * 2, maxRaidus * 2, 90 * 16, -angle * 16);
    painter->restore();
}

void OShadowClock::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    painter->setFont(font);

    QDateTime now = QDateTime::currentDateTime();
    QFontMetricsF fm(font);
    QStringList textList;
    textList << now.toString("MM-dd-yyyy") << now.toString("hh:mm:ss.zzz");

    //绘制文本路径
    QPainterPath textPath;

//    qDebug()<<"fm.width(textList.at(0))"<<fm.width(textList.at(0))<<fm.lineSpacing();
//    qDebug()<<"fm.width(textList.at(0))"<<fm.width(textList.at(1))<<fm.lineSpacing();

    int centerX = this->width()/2;
    int centerY = this->height()/2;

    textPath.addText( - fm.width(textList.at(0)) / 2.0, -fm.lineSpacing() / 2.0, font, textList.at(0));
    textPath.addText( -fm.width(textList.at(1)) / 2.0, fm.lineSpacing() / 2.0, font, textList.at(1));

//    textPath.addText(30, 20, font, textList.at(0));
//    textPath.addText(30, 50, font, textList.at(1));

    QColor strokeColor = textColor.light(80);
    strokeColor.setAlphaF(0.2);
    painter->strokePath(textPath, QPen(strokeColor, shadowWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(textColor);
    painter->drawPath(textPath);

    painter->restore();
}

int OShadowClock::getRadiusWidth() const
{
   return radiusWidth;
}

int OShadowClock::getShadowWidth() const
{
    return shadowWidth;
}

QColor OShadowClock::getTextColor() const
{
    return textColor;
}

QColor OShadowClock::getShadowColor() const
{
    return shadowColor;
}



void OShadowClock::setRadiusWidth(int radiusWidth)
{
    this->radiusWidth = radiusWidth;
}

void OShadowClock::setShadowWidth(int shadowWidth)
{
    this->shadowWidth = shadowWidth;

}

void OShadowClock::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OShadowClock::setShadowColor(const QColor &shadowColor)
{
    this->shadowColor = shadowColor;

}
