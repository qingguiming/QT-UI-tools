#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

signals:

protected:
    void mousePressEvent(QMouseEvent *);

public slots:
};

#endif // MYWIDGET_H
