#include "owidget.h"
#include <QDebug>
OWidget::OWidget(QWidget *parent) :
    QWidget(parent)
{
}

void OWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"OWidget::mousePressEvent";
    QWidget::mousePressEvent(e);
}

void OWidget::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"OWidget::mouseReleaseEvent";
    QWidget::mouseReleaseEvent(e);

}

void OWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

}
