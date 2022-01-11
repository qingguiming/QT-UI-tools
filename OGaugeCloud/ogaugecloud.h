#ifndef OGAUGECLOUD_H
#define OGAUGECLOUD_H

/**
 * 云台仪表盘控件
 * 1:可设置背景颜色
 * 2:可设置基准颜色
 * 3:可设置边框颜色
 * 4:可设置文本颜色
 * 5:可识别每个角度+中间 鼠标按下并发出信号
 * 6:可设置八个角的图标和中间图标,随便换
 * 7:内置4种云台风格 黑色+白色+蓝色+紫色
 * 8:支持拓展鼠标进入离开时的切换
 */

#include <QWidget>


#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OGaugeCloud : public QWidget
{
    Q_OBJECT
    Q_ENUMS(CloudStyle)
    Q_PROPERTY(QColor baseColor READ getBaseColor WRITE setBaseColor)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor arcColor READ getArcColor WRITE setArcColor)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor pressColor READ getPressColor WRITE setPressColor)
    Q_PROPERTY(QString iconText READ getIconText WRITE setIconText)
    Q_PROPERTY(QString centerText READ getCenterText WRITE setCenterText)
    Q_PROPERTY(CloudStyle cloudStyle READ getCloudStyle WRITE setCloudStyle)
public:
    enum CloudStyle {
        CloudStyle_Black = 0,   //黑色风格
        CloudStyle_White = 1,   //白色风格
        CloudStyle_Blue = 2,    //蓝色风格
        CloudStyle_Purple = 3   //紫色风格
    };

    explicit OGaugeCloud(QWidget *parent = 0);
    ~OGaugeCloud();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawCircle(QPainter *painter, int radius, const QBrush &brush);
    void drawArc(QPainter *painter);
    void drawText(QPainter *painter);

private:
    QColor bgColor;                 //背景颜色
    QColor baseColor;               //基准颜色
    QColor arcColor;                //圆弧颜色
    QColor borderColor;             //边框颜色
    QColor textColor;               //文字颜色
    QColor pressColor;              //按下文字颜色

    QString iconText;               //八个角图标
    QString centerText;             //中间图标
    CloudStyle cloudStyle;          //云台样式

    bool enter;                     //鼠标是否进入
    bool pressed;                   //鼠标是否按下
    QPoint lastPoint;               //鼠标按下处的坐标
    QRectF centerRect;              //中间区域
    QRectF leftRect;                //左侧图标区域
    QRectF topRect;                 //上侧图标区域
    QRectF rightRect;               //右侧图标区域
    QRectF bottomRect;              //下侧图标区域
    QRectF leftTopRect;             //左上角图标区域
    QRectF rightTopRect;            //右上角图标区域
    QRectF leftBottomRect;          //左下角图标区域
    QRectF rightBottomRect;         //右下角图标区域

    QFont iconFont;                 //图形字体

public:
    QColor getBgColor()             const;
    QColor getBaseColor()           const;
    QColor getArcColor()            const;
    QColor getBorderColor()         const;
    QColor getTextColor()           const;
    QColor getPressColor()          const;

    QString getIconText()           const;
    QString getCenterText()         const;
    CloudStyle getCloudStyle()      const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置背景颜色
    void setBgColor(const QColor &bgColor);
    //设置基准颜色
    void setBaseColor(const QColor &baseColor);
    //设置圆弧颜色
    void setArcColor(const QColor &arcColor);
    //设置边框颜色
    void setBorderColor(const QColor &borderColor);
    //设置文本颜色
    void setTextColor(const QColor &textColor);
    //设置按下文本颜色
    void setPressColor(const QColor &pressColor);

    //设置八个角图标
    void setIconText(const QString &iconText);
    //设置中间图标
    void setCenterText(const QString centerText);
    //设置云台样式
    void setCloudStyle(const CloudStyle &cloudStyle);

Q_SIGNALS:
    //鼠标按下的区域,共9个,从0-8依次表示底部/左下角/左侧/左上角/顶部/右上角/右侧/右下角/中间
    void mousePressed(int position);
};

#endif //GAUGECLOUD_H

