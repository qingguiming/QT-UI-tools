#include "ogaugeedit.h"
#include <QPainter>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QEvent>
#include <QwheelEvent>

OGaugeEdit::OGaugeEdit(QWidget *parent) :
    QWidget(parent)
{
    qDebug("construct addr %p",this);
    installEventFilter(this);
    initStyle();
}

OGaugeEdit::~OGaugeEdit()
{

}

void OGaugeEdit::paintEvent(QPaintEvent *)
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
    //绘制当前进度
    drawProgress(&painter);
    //绘制中心圆
    drawCenterCircle(&painter);
    //绘制单位
    drawUnit(&painter);
}

void OGaugeEdit::drawOuterCircle(QPainter *painter)
{
    int radius = 91 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeEdit::drawInnerCircle(QPainter *painter)
{
    int radius = 80 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeEdit::drawProgress(QPainter *painter)
{
    int radius = 75 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = endAngle - startAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setBrush(usedColor);
    painter->drawPie(rect, (270 - endAngle + angleOther) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(freeColor);
    painter->drawPie(rect, (270 - endAngle) * 16, angleOther * 16);

    painter->restore();
}

void OGaugeEdit::drawCenterCircle(QPainter *painter)
{
    int radius = 60 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeEdit::drawUnit(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);

    int offsetY = 110;
    QRectF unitRect(-radius, -radius + offsetY, radius * 2, radius * 2 - offsetY);
    painter->drawText(unitRect, Qt::AlignCenter, unit);

    painter->restore();
}



bool OGaugeEdit::eventFilter(QObject *watched, QEvent *event)
{
    //qDebug()<<"eventFilter" << (int)event->type() << (int)QEvent::Wheel;
    //qDebug("QEvent addr %p",event);

    if(event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

        if(wheelEvent->delta() > 0)//delta为负就是向上滚动 delta为正就是向上滚动
        {
            setValue(currentValue + 1);
        }
        else
        {
            setValue(currentValue - 1);
        }


    }
    return QWidget::eventFilter(watched,event);
}

void OGaugeEdit::resizeEvent(QResizeEvent *)
{
    lineEdit->setFixedSize(this->width(),this->height());
}



void OGaugeEdit::initStyle()
{
    minValue = 0.0;
    maxValue = 100;
    value = 30;
    unit = "KG";

    startAngle = 180;
    endAngle = 0;
    animation = true;
    animationStep = 100;

    outerCircleColor = Qt::blue;
    innerCircleColor = Qt::darkCyan;
    centerCircleColor = Qt::red;
    usedColor = Qt::green;
    freeColor = Qt::white;
    textColor = Qt::white;
    reverse = true;
    currentValue = 10;
    offset = 0;

    lineEdit = new QLineEdit("",this);
    lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:rgb(255,0,0);");
    lineEdit->setAlignment(Qt::AlignHCenter);
    lineEdit->setFont(QFont( "Timers" , 30 ,  QFont::Bold) );

    QRegExp regx("[0-9]+$");
    QValidator* validator = new QRegExpValidator(regx, lineEdit);
    lineEdit->setValidator(validator);
    lineEdit->setText(QString::number(10));

    connect(lineEdit,&QLineEdit::textChanged,this,&OGaugeEdit::textChanged);



}

void OGaugeEdit::updateValue()
{

}

void OGaugeEdit::textChanged(const QString &value)
{

    int val = value.toInt();
    if(val < minValue) val = minValue;
    if(val > maxValue) val = maxValue;

    this->value = val;
    this->currentValue = val;
    lineEdit->setText(QString::number(val));
    update();
}

double OGaugeEdit::getMinValue() const
{
    return minValue;
}

double OGaugeEdit::getMaxValue() const
{
    return maxValue;
}

double OGaugeEdit::getValue() const
{
    return value;
}

QString OGaugeEdit::getUnit() const
{
    return unit;
}

int OGaugeEdit::getStartAngle() const
{
    return startAngle;
}

int OGaugeEdit::getEndAngle() const
{
    return endAngle;
}

bool OGaugeEdit::getAnimation() const
{
    return animation;
}

double OGaugeEdit::getAnimationStep() const
{
    return animationStep;
}

QColor OGaugeEdit::getOuterCircleColor() const
{
    return outerCircleColor;
}

QColor OGaugeEdit::getInnerCircleColor() const
{
    return innerCircleColor;
}

QColor OGaugeEdit::getCenterCircleColor() const
{
    return centerCircleColor;
}

QColor OGaugeEdit::getUsedColor() const
{
    return usedColor;
}

QColor OGaugeEdit::getFreeColor() const
{
    return freeColor;
}

QColor OGaugeEdit::getTextColor() const
{
    return textColor;
}

void OGaugeEdit::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugeEdit::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OGaugeEdit::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void OGaugeEdit::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OGaugeEdit::setValue(double val)
{
//    qDebug()<<"setValue" << val;


    if(val < minValue) val = minValue;
    if(val > maxValue) val = maxValue;

    this->value = val;
    this->currentValue = val;
    lineEdit->setText(QString::number(this->value));
    update();

}

void OGaugeEdit::setValue(int val)
{
//    qDebug()<<"setValue" << val;


    if(val < minValue) val = minValue;
    if(val > maxValue) val = maxValue;

    this->value = val;
    this->currentValue = val;
    lineEdit->setText(QString::number(this->value));

}

void OGaugeEdit::setUnit(const QString &unit)
{
    this->unit = unit;

}

void OGaugeEdit::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OGaugeEdit::setEndAngle(int endAngle)
{
    this->endAngle = endAngle;

}

void OGaugeEdit::setAnimation(bool animation)
{
    this->animation = animation;

}

void OGaugeEdit::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OGaugeEdit::setOuterCircleColor(const QColor &outerCircleColor)
{
    this->outerCircleColor = outerCircleColor;

}

void OGaugeEdit::setInnerCircleColor(const QColor &innerCircleColor)
{
    this->innerCircleColor = innerCircleColor;

}

void OGaugeEdit::setCenterCircleColor(const QColor &centerCircleColor)
{
    this->centerCircleColor = centerCircleColor;

}

void OGaugeEdit::setUsedColor(const QColor &usedColor)
{
    this->usedColor = usedColor;

    QString styleSheetStr = QString("background:transparent;border-width:0;border-style:outset;color:rgb(%1,%2,%3);")
            .arg(usedColor.red()).arg(usedColor.green()).arg(usedColor.blue());

    lineEdit->setStyleSheet(styleSheetStr);


}

void OGaugeEdit::setFreeColor(const QColor &freeColor)
{
    this->freeColor = freeColor;

}

void OGaugeEdit::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}


