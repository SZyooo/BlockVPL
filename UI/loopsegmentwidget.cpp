#include "loopsegmentwidget.h"
#include "editscrollarea.h"
#include "editwidgetswitchbuttonset.h"
#include "conditionwidget.h"
#include "CommonValues.h"
#include <QMouseEvent>
#include <QPushButton>
#include "tool.h"
#include <QFont>
#include "VRE/Node.h"
#include "Controller/compileinfostack.h"
#include "variablelistwidget.h"
LoopSegmentWidget::LoopSegmentWidget()
    :_btn_set(new EditWidgetSwitchButtonSet),_hovering_idx(-1),
      _condition_widget(new ConditionWidget),_add_btn(new QPushButton("+",this))
{
    _btn_set->setParent(this);
    _condition_widget->setParent(this);
    ChangeBKG(_btn_set,QColor("#AAABD0"));
    _add_btn->resize(ADD_BTN_SIZE,ADD_BTN_SIZE);
    QFont font = _add_btn->font();
    font.setPointSize(ADD_BTN_FONT);
    _add_btn->setFont(font);
    connect(_add_btn,&QPushButton::clicked,this,&LoopSegmentWidget::AddEditArea);
    connect(_btn_set,&EditWidgetSwitchButtonSet::Left,this,&LoopSegmentWidget::WhenClickLeft);
    connect(_btn_set,&EditWidgetSwitchButtonSet::Right,this,&LoopSegmentWidget::WhenClickRight);
    connect(_btn_set,&EditWidgetSwitchButtonSet::Delete,this,&LoopSegmentWidget::WhenClickRemove);
    setMouseTracking(true);
    UpdateView();
    HideBtnSet();
}

LoopNode *LoopSegmentWidget::GetLoopNode(int idx) const
{
    std::vector<BranchNode*> branches;
    for(int i=0;i<_edit_areas.size();i++){
        branches.push_back(_edit_areas[i]->GetBranchNode(i));
    }
    Condition condition =_condition_widget->GetCondition();
    OP op;
    switch(condition){
    case EQ:op = EQUAL;break;
    case LES:op = LESS;break;
    case GRT:op = GREATER;break;
    case LES_EQ:op = LESSEQUAL;break;
    case GRT_EQ:op = GREATEREQUAL;break;
    case NEQ:op = NONEQUAL;break;
    default:op = EQUAL;
    }
    bool left_is_literal,right_is_literal;
    QString left_val,right_val;
    left_val = _condition_widget->GetLeftValue(left_is_literal);
    right_val = _condition_widget->GetRightValue(right_is_literal);
    if(left_val.length() == 0 &&  right_val.length() == 0){
        QString warning("Loop number ");
        warning += QString::number(idx+1) + " will always run as no value in condition, so condition always returns true";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    if(left_val == right_val && left_is_literal && right_is_literal){
        QString warning("Loop number ");
        warning += QString::number(idx+1) + " will always run as condition is always true";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    if(left_is_literal && VariableListWidget::CheckNameIsVariable(left_val)){
        QString warning("Loop number ");
        warning += QString::number(idx+1) +
                " has a literal in its condition's left value, however it is the same as a"\
                " variable's name. Do you intend to use the variable?";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    return new LoopNode(branches,idx,left_val.toStdString(),right_val.toStdString(),
                        left_is_literal,right_is_literal,op);
}

void LoopSegmentWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = static_cast<int>(event->position().x());
    int y = static_cast<int>(event->position().y());
    bool collide =false;
    for(int i=0;i<_edit_areas.size();i++){
        int rx = _edit_areas[i]->x();
        int ry = _edit_areas[i]->y();
        int w = _edit_areas[i]->width();
        int h = _edit_areas[i]->height() + SPACING_BETWEEN_EDIT_AREA_AND_BTNSET + _btn_set->height();
        QRect rect(rx,ry,w,h);
        if(rect.contains(x,y)){
            ShowBtnSetAt(i);
            collide = true;
            break;
        }
    }
    if(collide == false && _hovering_idx!=-1){
        HideBtnSet();
    }
}

void LoopSegmentWidget::HideBtnSet()
{
    _hovering_idx = -1;
    _btn_set->setVisible(false);
    _btn_set->setEnabled(false);
}

void LoopSegmentWidget::ShowBtnSetAt(int idx)
{
    _hovering_idx = idx;
    _btn_set->setVisible(true);
    _btn_set->setEnabled(true);
    int x = _edit_areas[idx]->x() + _edit_areas[idx]->width()/2 - _btn_set->width()/2;
    int y = _edit_areas[idx]->y() + _edit_areas[idx]->height() + SPACING_BETWEEN_EDIT_AREA_AND_BTNSET;
    _btn_set->move(x,y);
}
void LoopSegmentWidget::AddEditArea()
{
    EditScrollarea* area = new EditScrollarea;
    _edit_areas.push_back(area);
    area->setParent(this);
    UpdateView();
}

void LoopSegmentWidget::RemoveEditArea(int idx)
{
    if(idx < 0 || idx >= _edit_areas.size()){
        return;
    }
    EditScrollarea* area = _edit_areas[idx];
    _edit_areas[idx] = nullptr;
    delete area;
    area = nullptr;
    _edit_areas.erase(_edit_areas.begin() + idx);
    if(idx == _hovering_idx){
        HideBtnSet();
    }
    UpdateView();
}

void LoopSegmentWidget::UpdateView()
{
    int x = EDGE,y = EDGE;
    for(int i=0;i<_edit_areas.size();i++){
        _edit_areas[i]->move(x,y);
        x += EditWidgetWidth + SPACING_BETWEEN_EDIT_AREAS;
        _edit_areas[i]->show();
    }
    //设置condition widget
    x += SPACING_BETWEEN_EDIT_AREAS;
    int h = EditWidgetHeight + 2 * EDGE + _btn_set->height() + SPACING_BETWEEN_EDIT_AREA_AND_BTNSET;
    _condition_widget->move(x,h/2 - _condition_widget->height()/2);
    _condition_widget->show();
    //设置+button的位置
    int btn_x = _condition_widget->x() + (_condition_widget->width()/2 - ADD_BTN_SIZE/2);
    int btn_y = _condition_widget->y() + _condition_widget->height() + SPACING_BETWEEN_CONDITION_ADDBTN;
    _add_btn->move(btn_x,btn_y);
    _add_btn->show();
    int w = _condition_widget->x() + _condition_widget->width() + EDGE;
    //QString s = QString::number(h) + QString(",") + QString::number(w);
    //Print(s);
    resize(w,h);
    emit WindowResize();
}

void LoopSegmentWidget::SwitchLeft(int idx)
{
    if(idx == 0){
        return;
    }
    EditScrollarea* lArea = _edit_areas[idx - 1];
    _edit_areas[idx - 1] = _edit_areas[idx];
    _edit_areas[idx] = lArea;
    UpdateView();
}

void LoopSegmentWidget::SwitchRight(int idx)
{
    if(idx == _edit_areas.size() - 1){
        return;
    }
    EditScrollarea* rArea = _edit_areas[idx + 1];
    _edit_areas[idx + 1] = _edit_areas[idx];
    _edit_areas[idx] = rArea;
    UpdateView();
}

void LoopSegmentWidget::WhenClickLeft()
{
    SwitchLeft(_hovering_idx);
}

void LoopSegmentWidget::WhenClickRight()
{
    SwitchRight(_hovering_idx);
}

void LoopSegmentWidget::WhenClickRemove()
{
    RemoveEditArea(_hovering_idx);
}
