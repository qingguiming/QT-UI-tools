#include "mywidget.h"
#include <QPainter>
MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QLineF line1(50,50,250,50);
    QPainter painter(this);

    painter.setBrush(Qt::SolidPattern);
    painter.setPen(Qt::darkGreen);
    painter.drawLine(line1);

}
