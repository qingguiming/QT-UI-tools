#include "omovewidget.h"
#include "qevent.h"
#include "qdebug.h"
#include "omoveobject.h"

OMoveWidget::OMoveWidget(QWidget *parent) : QPushButton(parent)
{
    OMoveObject* o = new OMoveObject();
    o->setWidget(static_cast<QWidget*>(this));
}


