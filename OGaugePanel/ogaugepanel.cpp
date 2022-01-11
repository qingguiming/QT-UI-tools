#include "ogaugepanel.h"
#include <QPainter>
#include <QtMath>

OGaugePanel::OGaugePanel(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 20;
    precision = 0;
    scalePrecision = 0;
    scaleMajor = 5;
    scaleMinor = 4;
    startAngle = 60;
    endAngle = 300;

    animation -= false;
    animationStep = 0;

    ringWidth = 15;
    ringColor = Qt::black;

    scaleColor = Qt::cyan;
    pointerColor = Qt::blue;
    bgColor = Qt::gray;
    textColor = Qt::white;

    unit = "Hz";
    text = "Wave";
    reverse = false;
    currentValue = 20;


}
void OGaugePanel::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    if (bgColor != Qt::transparent) {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(), bgColor);
    }

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆环
    drawRing(&painter);

    //绘制刻度线
    drawScale(&painter);

    //绘制刻度值
    drawScaleNum(&painter);

    //绘制指示器
    drawPointer(&painter);

    //绘制当前值
    drawValue(&painter);
}

void OGaugePanel::drawRing(QPainter *painter)
{
    int radius = 70;
    painter->save();

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(ringWidth);
    pen.setColor(ringColor);
    painter->setPen(pen);

    radius = radius - ringWidth;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    double angleAll = endAngle - startAngle;
    painter->drawArc(rect, (270 - startAngle - angleAll) * 16, angleAll * 16);

    painter->restore();
}

void OGaugePanel::drawScale(QPainter *painter)
{
    int radius = 80;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (endAngle - startAngle) / steps;

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(scaleColor);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius + 5);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius - 3);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void OGaugePanel::drawScaleNum(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setPen(scaleColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (endAngle - startAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', scalePrecision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void OGaugePanel::drawPointer(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(4, -5, 0, 0, -8, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void OGaugePanel::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(15);
    painter->setFont(font);

    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    strValue = QString("%1 %2").arg(strValue).arg(unit);
    QRectF valueRect(-radius, radius / 3.5, radius * 2, radius / 3.5);
    painter->drawText(valueRect, Qt::AlignCenter, strValue);

    QRectF textRect(-radius, radius / 2.5, radius * 2, radius / 2.5);
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText(textRect, Qt::AlignCenter, text);

    painter->restore();
}

void OGaugePanel::updateValue()
{

}

double OGaugePanel::getMinValue() const
{
    return minValue;
}

double OGaugePanel::getMaxValue() const
{
    return maxValue;
}

double OGaugePanel::getValue() const
{
    return value;
}

int OGaugePanel::getPrecision() const
{
    return precision;
}

int OGaugePanel::getScalePrecision() const
{
    return scalePrecision;
}

int OGaugePanel::getScaleMajor() const
{
    return scaleMajor;
}

int OGaugePanel::getScaleMinor() const
{
    return scaleMinor;
}

int OGaugePanel::getStartAngle() const
{
    return startAngle;
}

int OGaugePanel::getEndAngle() const
{
    return endAngle;
}

bool OGaugePanel::getAnimation() const
{
    return animation;
}

double OGaugePanel::getAnimationStep() const
{
    return animationStep;
}

int OGaugePanel::getRingWidth() const
{
    return ringWidth;
}

QColor OGaugePanel::getRingColor() const
{
    return ringColor;
}

QColor OGaugePanel::getScaleColor() const
{
    return scaleColor;
}

QColor OGaugePanel::getPointerColor() const
{
    return pointerColor;
}

QColor OGaugePanel::getBgColor() const
{
    return bgColor;
}

QColor OGaugePanel::getTextColor() const
{
    return textColor;
}

QString OGaugePanel::getUnit() const
{
    return unit;
}

QString OGaugePanel::getText() const
{
    return text;
}

QSize OGaugePanel::sizeHint() const
{
    return QSize(150,150);
}

QSize OGaugePanel::minimumSizeHint() const
{
    return QSize(150,150);

}

void OGaugePanel::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugePanel::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OGaugePanel::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void OGaugePanel::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OGaugePanel::setValue(double value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;
    this->currentValue = value;
    this->value = value;

}

void OGaugePanel::setValue(int value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;
    this->currentValue = value;
    this->value = value;
}

void OGaugePanel::setPrecision(int precision)
{
    this->precision = precision;

}

void OGaugePanel::setScalePrecision(int scalePrecision)
{
    this->scalePrecision = scalePrecision;

}

void OGaugePanel::setScaleMajor(int scaleMajor)
{
    this->scaleMajor = scaleMajor;

}

void OGaugePanel::setScaleMinor(int scaleMinor)
{
    this->scaleMinor = scaleMinor;

}

void OGaugePanel::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OGaugePanel::setEndAngle(int endAngle)
{
    this->endAngle = endAngle;

}

void OGaugePanel::setAnimation(bool animation)
{
    this->animation = animation;

}

void OGaugePanel::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OGaugePanel::setRingWidth(int ringWidth)
{
    this->ringWidth = ringWidth;

}

void OGaugePanel::setRingColor(const QColor &ringColor)
{
    this->ringColor = ringColor;

}

void OGaugePanel::setScaleColor(const QColor &scaleColor)
{
    this->scaleColor = scaleColor;

}

void OGaugePanel::setPointerColor(const QColor &pointerColor)
{
    this->pointerColor = pointerColor;

}

void OGaugePanel::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;

}

void OGaugePanel::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OGaugePanel::setUnit(const QString &unit)
{
    this->unit = unit;

}

void OGaugePanel::setText(const QString &text)
{
    this->text = text;

}

