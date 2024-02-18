#include "util.h"

void myUtil::expandWindow(float ratio, QWidget *obj) {
    int new_width = obj->width();
    int new_height = obj->height();
    obj->setFixedSize(new_width, new_height);
    QPoint curPos = obj->pos();
    obj->move(curPos * ratio);
}
