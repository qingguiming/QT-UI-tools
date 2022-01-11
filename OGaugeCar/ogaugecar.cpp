#include "ogaugecar.h"
#include <QtMath>
#include <QPainter>

OGaugeCar::OGaugeCar(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;
    scaleMajor = 5;
    scaleMinor = 4;
    startAngle = 60;
    endAngle = 300;

    animation = false;
    animationStep = 1;
    outerCircleColor = Qt::black;
    innerCircleColor = Qt::cyan;

    pieColorStart = Qt::green;
    pieColorMid = Qt::blue;
    pieColorEnd = Qt::red;

    coverCircleColor = Qt::darkRed;
    scaleColor = Qt::white;
    pointerColor = Qt::gray;
    centerCircleColor = Qt::darkGreen;
    textColor = Qt::white;

    showOverlay = false;
    overlayColor = Qt::lightGray;

    pieStyle = PieStyle_Three;
    pointerStyle = PointerStyle_Indicator;
    currentValue = 0;


}
void OGaugeCar::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外圆
    drawOuterCircle(&painter);
    //绘制内圆
    drawInnerCircle(&painter);
    //绘制饼圆
    drawColorPie(&painter);
    //绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);

    //根据指示器形状绘制指示器
    if (pointerStyle == PointerStyle_Circle) {
        drawPointerCircle(&painter);
    } else if (pointerStyle == PointerStyle_Indicator) {
        drawPointerIndicator(&painter);
    } else if (pointerStyle == PointerStyle_IndicatorR) {
        drawPointerIndicatorR(&painter);
    } else if (pointerStyle == PointerStyle_Triangle) {
        drawPointerTriangle(&painter);
    }

    //绘制指针中心圆外边框
    drawRoundCircle(&painter);
    //绘制指针中心圆
    drawCenterCircle(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制遮罩层
    drawOverlay(&painter);
}

void OGaugeCar::drawOuterCircle(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCar::drawInnerCircle(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCar::drawColorPie(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    if (pieStyle == PieStyle_Three) {
        //计算总范围角度,根据占比例自动计算三色圆环范围角度
        //可以更改比例
        double angleAll = endAngle - startAngle ;
        double angleStart = angleAll * 0.7;
        double angleMid = angleAll * 0.15;
        double angleEnd = angleAll * 0.15;

        //增加偏移量使得看起来没有脱节
        int offset = 3;

        //绘制开始饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleStart) * 16, angleStart * 16);

        //绘制中间饼圆
        painter->setBrush(pieColorMid);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid) * 16 + offset, angleMid * 16);

        //绘制结束饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid - angleEnd) * 16 + offset * 2, angleEnd * 16);
    } else if (pieStyle == PieStyle_Current) {
        //计算总范围角度,当前值范围角度,剩余值范围角度
        double angleAll = endAngle - startAngle;
        double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
        double angleOther = angleAll - angleCurrent;

        //绘制当前值饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

        //绘制剩余值饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);
    }

    painter->restore();
}

void OGaugeCar::drawCoverCircle(QPainter *painter)
{
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(coverCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCar::drawScale(QPainter *painter)
{
    int radius = 72;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (endAngle - startAngle ) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void OGaugeCar::drawScaleNum(QPainter *painter)
{
    int radius = 82;
    painter->save();
    painter->setPen(scaleColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (endAngle - startAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void OGaugeCar::drawPointerCircle(QPainter *painter)
{
    int radius = 6;
    int offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void OGaugeCar::drawPointerIndicator(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void OGaugeCar::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(1.0);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(pointerColor);
    painter->setPen(pen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void OGaugeCar::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 38;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void OGaugeCar::drawRoundCircle(QPainter *painter)
{
    int radius = 18;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCar::drawCenterCircle(QPainter *painter)
{
    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCar::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(18);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void OGaugeCar::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void OGaugeCar::updateValue()
{

}

double OGaugeCar::getMinValue() const
{
    return minValue;
}

double OGaugeCar::getMaxValue() const
{
    return maxValue;
}

double OGaugeCar::getValue() const
{
    return value;
}

int OGaugeCar::getPrecision() const
{
    return precision;
}

int OGaugeCar::getScaleMajor() const
{
    return scaleMajor;
}

int OGaugeCar::getScaleMinor() const
{
    return scaleMinor;
}

int OGaugeCar::getStartAngle() const
{
    return startAngle;
}

int OGaugeCar::getEndAngle() const
{
    return endAngle;

}

bool OGaugeCar::getAnimation() const
{
    return animation;
}

double OGaugeCar::getAnimationStep() const
{
    return animationStep;
}

QColor OGaugeCar::getOuterCircleColor() const
{
    return outerCircleColor;
}

QColor OGaugeCar::getInnerCircleColor() const
{
    return innerCircleColor;
}

QColor OGaugeCar::getPieColorStart() const
{
    return pieColorStart;
}

QColor OGaugeCar::getPieColorMid() const
{
    return pieColorMid;
}

QColor OGaugeCar::getPieColorEnd() const
{
    return pieColorEnd;
}

QColor OGaugeCar::getCoverCircleColor() const
{
    return coverCircleColor;
}

QColor OGaugeCar::getScaleColor() const
{
    return scaleColor;
}

QColor OGaugeCar::getPointerColor() const
{
    return pointerColor;
}

QColor OGaugeCar::getCenterCircleColor() const
{
    return centerCircleColor;
}

QColor OGaugeCar::getTextColor() const
{
    return textColor;
}

bool OGaugeCar::getShowOverlay() const
{
    return showOverlay;
}

QColor OGaugeCar::getOverlayColor() const
{
    return overlayColor;
}

OGaugeCar::PieStyle OGaugeCar::getPieStyle() const
{
    return pieStyle;
}

OGaugeCar::PointerStyle OGaugeCar::getPointerStyle() const
{
    return pointerStyle;
}

void OGaugeCar::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugeCar::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OGaugeCar::setMinValue(double minValue)
{
    this->minValue = minValue;
}

void OGaugeCar::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OGaugeCar::setValue(double value)
{
    if(value > maxValue) this->value = maxValue;
    if(value < minValue) this->value = minValue;

    this->value = value;
    this->currentValue = value;

    update();

}

void OGaugeCar::setValue(int value)
{
    if(value > maxValue) this->value = maxValue;
    if(value < minValue) this->value = minValue;

    this->value = value;
    this->currentValue = value;

    update();

}

void OGaugeCar::setPrecision(int precision)
{
    this->precision = precision;

}

void OGaugeCar::setScaleMajor(int scaleMajor)
{
    this->scaleMajor = scaleMajor;

}

void OGaugeCar::setScaleMinor(int scaleMinor)
{
    this->scaleMinor = scaleMinor;

}

void OGaugeCar::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OGaugeCar::setEndAngle(int endAngle)
{
    this->endAngle = endAngle;

}

void OGaugeCar::setAnimation(bool animation)
{
    this->animation = animation;

}

void OGaugeCar::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OGaugeCar::setOuterCircleColor(const QColor &outerCircleColor)
{
    this->outerCircleColor = outerCircleColor;

}

void OGaugeCar::setInnerCircleColor(const QColor &innerCircleColor)
{
    this->innerCircleColor = innerCircleColor;

}

void OGaugeCar::setPieColorStart(const QColor &pieColorStart)
{
    this->pieColorStart = pieColorStart;

}

void OGaugeCar::setPieColorMid(const QColor &pieColorMid)
{
    this->pieColorMid = pieColorMid;

}

void OGaugeCar::setPieColorEnd(const QColor &pieColorEnd)
{
    this->pieColorEnd = pieColorEnd;

}

void OGaugeCar::setCoverCircleColor(const QColor &coverCircleColor)
{
    this->coverCircleColor = coverCircleColor;

}

void OGaugeCar::setScaleColor(const QColor &scaleColor)
{
    this->scaleColor = scaleColor;

}

void OGaugeCar::setPointerColor(const QColor &pointerColor)
{
    this->pointerColor = pointerColor;

}

void OGaugeCar::setCenterCircleColor(const QColor &centerCircleColor)
{
    this->centerCircleColor = centerCircleColor;

}

void OGaugeCar::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OGaugeCar::setShowOverlay(bool showOverlay)
{
    this->showOverlay = showOverlay;

}

void OGaugeCar::setOverlayColor(const QColor &overlayColor)
{
    this->overlayColor = overlayColor;

}

void OGaugeCar::setPieStyle(const OGaugeCar::PieStyle &pieStyle)
{
    this->pieStyle = pieStyle;

}

void OGaugeCar::setPointerStyle(const OGaugeCar::PointerStyle &pointerStyle)
{
    this->pointerStyle = pointerStyle;

}
