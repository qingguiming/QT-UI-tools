#ifndef OMOVEOBJECT_H
#define OMOVEOBJECT_H

#include <QObject>
#include <QPoint>


class OMoveObject : public QObject
{
    Q_OBJECT
public:
    explicit OMoveObject(QObject *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QPoint lastPoint;   //最后按下的坐标
    bool pressed;       //鼠标是否按下
    bool leftButton;    //限定鼠标左键
    QWidget *widget;    //移动的控件

public Q_SLOTS:
    //设置是否限定鼠标左键
    void setLeftButton(bool leftButton);
    //设置要移动的控件
    void setWidget(QWidget *widget);
};

#endif // OMOVEOBJECT_H
