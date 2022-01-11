#include "ocombobox.h"

#include "qlistview.h"
#include "qdebug.h"

OCombobox::OCombobox(QWidget *parent) : QComboBox(parent)
{
    itemWidth = 5;
    itemHeight = 20;
    autoWidth = true;
    this->setView(new QListView());
}

void OCombobox::showEvent(QShowEvent *)
{
    if (autoWidth)
    {
        //自动计算所有元素,找到最长的元素
        QFontMetrics fm = this->fontMetrics();
        int count = this->count();
        for (int i = 0; i < count; i++) {
            int textWidth = fm.width(this->itemText(i));
            itemWidth = textWidth > itemWidth ? textWidth : itemWidth;
        }

        //宽度增加像素,因为有边距
        this->view()->setFixedWidth(itemWidth + 20);
    }
}

int OCombobox::getItemWidth() const
{
    return this->itemWidth;
}

int OCombobox::getItemHeight() const
{
    return this->itemHeight;
}

bool OCombobox::getAutoWidth() const
{
    return this->autoWidth;
}

void OCombobox::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        if (!autoWidth) {
            this->view()->setFixedWidth(itemWidth);
        }
    }
}

void OCombobox::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        this->setStyleSheet(QString("QComboBox QAbstractItemView::item{min-height:%1px;}").arg(itemHeight));
    }
}

void OCombobox::setAutoWidth(bool autoWidth)
{
    if (this->autoWidth != autoWidth) {
        this->autoWidth = autoWidth;
    }
}





