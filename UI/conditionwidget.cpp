#include "conditionwidget.h"
#include <QComboBox>
#include "UI/inputwidget.h"
#include <QFont>
#include <QFontMetrics>
ConditionWidget::ConditionWidget()
    :_left(new InputWidget),_right(new InputWidget),_combobox(new QComboBox)
{
    _left->setParent(this);
    _right->setParent(this);
    _combobox->setParent(this);
    _combobox->addItem("=");
    _combobox->addItem(">");
    _combobox->addItem("≥");
    _combobox->addItem("<");
    _combobox->addItem("≤");
    _combobox->addItem("≠");
    connect(_left,&InputWidget::WindowReisze,this,&ConditionWidget::UpdateSize);
    connect(_right,&InputWidget::WindowReisze,this,&ConditionWidget::UpdateSize);
    UpdateSize();
}

QString ConditionWidget::GetLeftValue(bool &is_literal) const
{
    is_literal = _left->IsLiteral();
    return _left->FetchValue();
}

QString ConditionWidget::GetRightValue(bool &is_literal) const
{
    is_literal = _right->IsLiteral();
    return _right->FetchValue();
}

Condition ConditionWidget::GetCondition() const
{
    Condition condition = EQ;
    switch (_combobox->currentIndex()) {
    case 0:
        condition = EQ;break;
    case 1:
        condition = GRT;break;
    case 2:
        condition = GRT_EQ;break;
    case 3:
        condition = LES;break;
    case 4:
        condition = LES_EQ;break;
    case 5:
        condition = NEQ;break;
    }
    return condition;
}

void ConditionWidget::UpdateSize()
{
    QFont font;
    font.setPointSize(FONTSIZE);
    QSize size = QFontMetrics(font).tightBoundingRect("≥").size();
    size.setWidth(size.width() + 50);
    size.setHeight(size.height() * 2);
    int x = EDGE;
    _left->move(x,EDGE);
    x = _left->x() + _left->width() + SPACING;
    int cbb_y = _left->y() + _left->height()/2 - size.height()/2;
    _combobox->setFont(font);
    _combobox->setGeometry(x,cbb_y,size.width(),size.height());
    x = _combobox->x() + _combobox->width() + SPACING;
    _right->move(x,EDGE);
    int hei = qMax(_combobox->height(),_left->height());
    resize(_right->x()+_right->width()+EDGE,hei);
    emit WidgetResize();
}
