#include "olightpoint.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

OLightPoint::OLightPoint(QWidget *parent) : QWidget(parent)
{
    step = 10;
    interval = 100;
    bgColor = QColor(255, 0, 0);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    offset = 0;
    add = true;
}

OLightPoint::~OLightPoint()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void OLightPoint::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
}

void OLightPoint::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();

    QRadialGradient g(QPoint(0, 0), radius);

    (offset < 70 && add) ? (offset += step) : (add = false);
    (offset > 0 && !add) ? (offset -= step) : (add = true);

    bgColor.setAlpha(255);
    g.setColorAt(0.1, bgColor);
    bgColor.setAlpha(100 + offset);
    g.setColorAt(0.3, bgColor);
    bgColor.setAlpha(50 + offset);
    g.setColorAt(0.6, bgColor);
    bgColor.setAlpha(0);
    g.setColorAt(1.0, bgColor);

    painter->setPen(Qt::NoPen);
    painter->setBrush(g);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

int OLightPoint::getStep() const
{
    return this->step;
}

int OLightPoint::getInterval() const
{
    return this->interval;
}

QColor OLightPoint::getBgColor() const
{
    return this->bgColor;
}

QSize OLightPoint::sizeHint() const
{
    return QSize(100, 100);
}

QSize OLightPoint::minimumSizeHint() const
{
    return QSize(5, 5);
}

void OLightPoint::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void OLightPoint::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(interval);
        update();
    }
}

void OLightPoint::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}


