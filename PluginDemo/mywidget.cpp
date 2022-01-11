#include "mywidget.h"
#include <QDebug>
#include <QMouseEvent>
MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

}

void MyWidget::mousePressEvent(QMouseEvent *)
{
    qDebug()<<"MyWidget::mousePressEvent";
}
