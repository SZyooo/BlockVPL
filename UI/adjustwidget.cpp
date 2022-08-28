#include "adjustwidget.h"
#include <QPushButton>

AdjustWidget::AdjustWidget()
    :_up(new QPushButton("↑",this)),_down(new QPushButton("↓",this)),_remove(new QPushButton("x",this))
{
    _up->setGeometry(EDGE,EDGE,BTN_SIZE,BTN_SIZE);
    _down->setGeometry(EDGE+BTN_SIZE,EDGE,BTN_SIZE,BTN_SIZE);
    _remove->setGeometry(EDGE+BTN_SIZE*2,EDGE,BTN_SIZE,BTN_SIZE);
    connect(_up,&QPushButton::clicked,this,&AdjustWidget::PressUp);
    connect(_down,&QPushButton::clicked,this,&AdjustWidget::PressDown);
    connect(_remove,&QPushButton::clicked,this,&AdjustWidget::Delete);
}

void AdjustWidget::PressUp()
{
    emit Up();
}

void AdjustWidget::PressDown()
{
    emit Down();
}

void AdjustWidget::PressDelete()
{
    emit Delete();
}
