#include "editwidgetswitchbuttonset.h"

#include <QPushButton>
EditWidgetSwitchButtonSet::EditWidgetSwitchButtonSet()
    :_left(new QPushButton("←",this)),_right(new QPushButton("→",this)),_remove(new QPushButton("x",this))
{
    _left->setGeometry(EDGE,EDGE,BUTTON_SIZE,BUTTON_SIZE);
    _right->setGeometry(EDGE*2+BUTTON_SIZE,EDGE,BUTTON_SIZE,BUTTON_SIZE);
    _remove->setGeometry(EDGE*3+ BUTTON_SIZE*2,EDGE,BUTTON_SIZE,BUTTON_SIZE);
    resize(4*EDGE + 3*BUTTON_SIZE,2*EDGE + BUTTON_SIZE);
    connect(_left,&QPushButton::clicked,this,&EditWidgetSwitchButtonSet::ClickLeft);
    connect(_right,&QPushButton::clicked,this,&EditWidgetSwitchButtonSet::ClickRight);
    connect(_remove,&QPushButton::clicked,this,&EditWidgetSwitchButtonSet::ClickRemove);
}

void EditWidgetSwitchButtonSet::ClickLeft()
{
    emit Left();
}

void EditWidgetSwitchButtonSet::ClickRight()
{
    emit Right();
}

void EditWidgetSwitchButtonSet::ClickRemove()
{
    emit Delete();
}
