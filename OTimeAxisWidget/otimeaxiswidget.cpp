#include "otimeaxiswidget.h"
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include "mywidget.h"

OTimeAxisWidget::OTimeAxisWidget(QWidget *parent) :
    QScrollArea(parent)
{
    itemMargin = 2;
    itemHeight = 50;
    infoPadding = 3;
    infoHeight = 30;

    setBackgroundRole(QPalette::Dark);
    baseColor = QColor(Qt::yellow);       //基准颜色
    lineColor = QColor(Qt::darkBlue);       //线条颜色

    title = "title";

//    timeAxisWidget = new TimeAxisWidget(this);
//    timeAxisWidget->setFixedHeight(800);

    timeAxisWidget = new TimeAxisWidget(this);
    timeAxisWidget->setBackgroundRole(QPalette::Light);

    timeAxisWidget->setMinimumWidth(400);
    timeAxisWidget->setMinimumHeight(600);


//    MyWidget* w= new MyWidget(this);
//    w->setBackgroundRole(QPalette::ButtonText);

//    w->setMinimumWidth(400);
//    w->setMinimumHeight(400);

    setWidget(timeAxisWidget);

}

int OTimeAxisWidget::getItemMargin() const
{
    return itemMargin;
}

int OTimeAxisWidget::getItemHeight() const
{
    return itemHeight;
}

int OTimeAxisWidget::getInfoPadding() const
{
    return infoPadding;
}

int OTimeAxisWidget::getInfoHeight() const
{
    return infoHeight;
}

QColor OTimeAxisWidget::getBaseColor() const
{
    return baseColor;
}

QColor OTimeAxisWidget::getLineColor() const
{
    return lineColor;
}

QString OTimeAxisWidget::getTitle() const
{
    return title;
}

QString OTimeAxisWidget::getInfos() const
{
    return infos;
}

QSize OTimeAxisWidget::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OTimeAxisWidget::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();

}

TimeAxisWidget *OTimeAxisWidget::getWidget()
{
    return timeAxisWidget;

}

void OTimeAxisWidget::setItemMargin(int itemMargin)
{
    this->itemMargin = itemMargin;
    timeAxisWidget->setItemMargin(itemMargin);
}

void OTimeAxisWidget::setItemHeight(int itemHeight)
{

    this->itemHeight = itemHeight;
    timeAxisWidget->setItemHeight(itemHeight);

}

void OTimeAxisWidget::setInfoPadding(int infoPadding)
{

    this->infoPadding = infoPadding;
    timeAxisWidget->setInfoPadding(infoPadding);

}

void OTimeAxisWidget::setInfoHeight(int infoHeight)
{

    this->infoHeight = infoHeight;
    timeAxisWidget->setInfoHeight(infoHeight);

}

void OTimeAxisWidget::setBaseColor(const QColor &baseColor)
{

    this->baseColor = baseColor;
    timeAxisWidget->setBaseColor(baseColor);

}

void OTimeAxisWidget::setLineColor(const QColor &lineColor)
{

    this->lineColor = lineColor;
    timeAxisWidget->setLineColor(lineColor);

}

void OTimeAxisWidget::setTitle(const QString &title)
{

    this->title = title;
    timeAxisWidget->setTitle(title);


}

void OTimeAxisWidget::setInfos(const QString &infos)
{

    this->infos = infos;
    timeAxisWidget->setInfos(infos);

}


TimeAxisWidget::TimeAxisWidget(QWidget *parent):QWidget(parent)
{
    title = "title";
}

void TimeAxisWidget::paintEvent(QPaintEvent *)
{


//    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawTitle(&painter);

    drawLine(&painter);

    drawInfo(&painter);

}

void TimeAxisWidget::drawTitle(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    painter->setFont(font);

    painter->setPen(baseColor);


    painter->drawText(itemMargin, itemMargin, width() - 2 * itemMargin, 40, Qt::AlignCenter, title);

    painter->restore();

}

void TimeAxisWidget::drawLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 6));
    int startY = itemMargin + 50;
    int endY = startY + itemInfos.size() * itemHeight;
    painter->drawLine(width() / 2.0, startY, width() / 2.0, endY);
    painter->restore();

    //设置下固定高度
    this->setFixedHeight(endY + itemMargin);

}

void TimeAxisWidget::drawInfo(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QFont font;
    font.setPointSize(12);
    painter->setFont(font);

    int startY = itemMargin + 50;
    int centerX = this->width() / 2.0;
    int spacer = itemMargin + 10;

    //追个绘制时间轴信息集合,偶数行左侧绘制时间右侧绘制信息
    for (int i = 0; i < itemInfos.size(); i++) {
        painter->setBrush(Qt::white);
        painter->setPen(QPen(baseColor, 2));

        if (i % 2 == 0) {
            //绘制时间
            QRectF textRect(0, startY, centerX - spacer, itemHeight);
            painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(centerX + spacer, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoRight(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoRight(painter, infoRect.adjusted(infoPadding, infoPadding, -infoPadding, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(infoPadding, infoPadding, 0, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        } else {
            //绘制时间
            QRectF textRect(centerX + spacer, startY, centerX - spacer, itemHeight);
            painter->drawText(centerX + spacer, startY, centerX - spacer, itemHeight, Qt::AlignLeft | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(itemMargin + infoHeight / 2.0, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoLeft(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoLeft(painter, infoRect.adjusted(infoPadding, infoPadding, -infoPadding, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(0, infoPadding, -infoPadding, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        }

        //绘制垂直线对应的圆
        painter->setPen(Qt::NoPen);
        painter->setBrush(baseColor);
        painter->drawEllipse(centerX - 8, startY + itemHeight / 2.0 - 8, 16, 16);
        painter->setBrush(Qt::white);
        painter->drawEllipse(centerX - 4, startY + itemHeight / 2.0 - 4, 8, 8);

        //Y轴往下移一个高度
        startY += itemHeight;
    }

    painter->restore();

}

void TimeAxisWidget::drawInfoRight(QPainter *painter, const QRectF &infoRect, int infoHeight)
{
    painter->save();
    {
        double radius = (double)infoHeight / 2;

        int w = infoRect.width();
        int h = infoRect.height();

        int x = infoRect.x();
        int y = infoRect.y();

        QPainterPath painterpath;

        painterpath.moveTo(x + w - radius ,0 + y);
        painterpath.lineTo(0 + x,0 + y);
        painterpath.lineTo(0 + x,h + y);
        painterpath.lineTo(w + x - radius,h + y);

        QRectF rectangle(x + w - 2*radius, 0 + y, infoHeight, infoHeight);
        int startAngle = -90;
        int spanAngle = 180;
//        QPainter painter(this);
//        painter.setBrush(Qt::SolidPattern);
//        painter.setPen(Qt::darkGreen);

        painterpath.arcTo(rectangle,startAngle,spanAngle);
        painter->drawPath(painterpath);

    }

    painter->restore();


}

void TimeAxisWidget::drawInfoLeft(QPainter *painter, const QRectF &infoRect, int infoHeight)
{

    painter->save();
    {
        double radius = (double)infoHeight / 2;

        int w = infoRect.width();
        int h = infoRect.height();

        int x = infoRect.x();
        int y = infoRect.y();

        QPainterPath painterpath;

//        painterpath.moveTo(radius + x ,0 + y);
//        painterpath.lineTo(w  + x,0 + y);
//        painterpath.lineTo(w  + x,h + y);
//        painterpath.lineTo(radius+x,h+y);

        painterpath.moveTo(radius + x ,0 + h + y);
        painterpath.lineTo(w  + x,h + y);
        painterpath.lineTo(w  + x,0 + y);
        painterpath.lineTo(radius  + x,0 + y);



//        painterpath.lineTo(w  + x,0 + y);
//        painterpath.lineTo(w  + x,h + y);
//        painterpath.lineTo(radius+x,h+y);

        QRectF rectangle(0+x, 0+y, infoHeight, infoHeight);
        int startAngle = 90;
        int spanAngle = 180;
//        QPainter painter(this);
//        painter.setBrush(Qt::SolidPattern);
//        painter.setPen(Qt::darkGreen);

        painterpath.arcTo(rectangle,startAngle,spanAngle);
        painter->drawPath(painterpath);

    }

    painter->restore();
}

int TimeAxisWidget::getItemMargin() const
{
    return itemMargin;
}

int TimeAxisWidget::getItemHeight() const
{
    return itemHeight;
}

int TimeAxisWidget::getInfoPadding() const
{
    return infoPadding;
}

int TimeAxisWidget::getInfoHeight() const
{
    return infoHeight;
}

QColor TimeAxisWidget::getBaseColor() const
{
    return baseColor;
}

QColor TimeAxisWidget::getLineColor() const
{
    return lineColor;
}

QString TimeAxisWidget::getTitle() const
{
    return title;
}

QString TimeAxisWidget::getInfos() const
{
    return infos;
}

QSize TimeAxisWidget::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize TimeAxisWidget::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();

}

void TimeAxisWidget::setItemMargin(int itemMargin)
{
    this->itemMargin = itemMargin;
}

void TimeAxisWidget::setItemHeight(int itemHeight)
{
    this->itemHeight = itemHeight;

}

void TimeAxisWidget::setInfoPadding(int infoPadding)
{
    this->infoPadding = infoPadding;

}

void TimeAxisWidget::setInfoHeight(int infoHeight)
{
    this->infoHeight = infoHeight;

}

void TimeAxisWidget::setBaseColor(const QColor &baseColor)
{
    this->baseColor = baseColor;

}

void TimeAxisWidget::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;

}

void TimeAxisWidget::setTitle(const QString &title)
{
    this->title = title;

}

void TimeAxisWidget::setInfos(const QString &infos)
{
    this->infos = infos;

    QStringList list = infos.split(",");

    if(list.size() % 2 != 0) return;

    QList<TimeAxisWidget::TimeAxisInfo> infoLists;

    for(int i = 0; i < list.size();)
    {
           TimeAxisInfo info;
           info.time = list.at(i);
           info.info = list.at(i+1);
           infoLists.append(info);
           i += 2;
    }

    setItemInfos(infoLists);



}

void TimeAxisWidget::setItemInfos(const QList<TimeAxisWidget::TimeAxisInfo> &itemInfos)
{
    this->itemInfos = itemInfos;
    update();

}
