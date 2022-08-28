#include "editwidget.h"
#include "UI/conditionwidget.h"
#include "UI/legowidget.h"
#include "UI/adjustwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include "CommonValues.h"
#include "tool.h"
#include "blockmimedata.h"
#include "VRE/Node.h"
#include "Controller/compileinfostack.h"
#include "variablelistwidget.h"
EditWidget::EditWidget()
    :_condition_widget(new ConditionWidget),_adjust_widget(new AdjustWidget)
{
    _segment_rect = QRect(0,0,0,0);
    setGeometry(0,0,EditWidgetWidth,EditWidgetHeight);
    _condition_widget->setParent(this);
    _adjust_widget->setParent(this);
    ChangeBKG(_adjust_widget,QColor("#F5CAD0"));
    UpdateWidgetSize();
    _hovering_idx = -1;
    connect(_condition_widget,&ConditionWidget::WidgetResize,this,&EditWidget::UpdateWidgetWidth);
    connect(_adjust_widget,&AdjustWidget::Delete,this,&EditWidget::DeleteLego);
    connect(_adjust_widget,&AdjustWidget::Up,this,&EditWidget::AdjustLegoUpward);
    connect(_adjust_widget,&AdjustWidget::Down,this,&EditWidget::AdjustLegoDownward);
    setMouseTracking(true);
    setAcceptDrops(true);
    HideAdjustWidget();
}

void EditWidget::mouseMoveEvent(QMouseEvent * e)
{
    int x = static_cast<int>(e->position().x());
    int y = static_cast<int>(e->position().y());
    if(_segment_rect.contains(x,y)){
        int collider_idx = -1;
        for(int i=0;i<_segment.size();i++){
            QRect rect = _segment[i]->geometry();
            rect.setWidth(rect.width() + _adjust_widget->width() + 1);
            if(_segment[i]->geometry().contains(x,y)){
                collider_idx = i;
                break;
            }
        }
        if(collider_idx == -1){
            return;
        }
        _hovering_idx = collider_idx;
        ShowAdjustWidgetAt(collider_idx);
        UpdateWidgetWidth();
    }
    else{
        _hovering_idx = -1;
        HideAdjustWidget();
        UpdateWidgetWidth();
    }
}

void EditWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,2));//设置画笔形式
    int y = _condition_widget->y()+_condition_widget->height() + SPACING;
    painter.drawLine(SIDE_EDGE+5,y,width()-SIDE_EDGE-5,y);//画直线
}

void EditWidget::AddLego(const QString kit_name, const QString &lego_name, const std::vector<QString> &params, bool has_return, QColor color)
{
    LegoWidget* lw = new LegoWidget(kit_name,lego_name,params,has_return,color);
    lw->setParent(this);
    //TurnOnShadowEffect(lw);
    lw->show();
    _segment.push_back(lw);
    connect(lw,&LegoWidget::ResizeWindow,this,&EditWidget::UpdateWidgetWidth);
    UpdateWidgetSize();
}

void EditWidget::RemoveLego(int idx)
{
    if(idx < 0 || idx >= _segment.size()){
        return;
    }
    LegoWidget* lw = _segment[idx];
    lw->setParent(nullptr);
    delete lw;
    lw = nullptr;
    //如果删除的块是最后一个，这意味着删除之后鼠标不再悬浮到有效块上面了
    if(_segment.size() <= idx){
        _hovering_idx = -1;
        HideAdjustWidget();
    }
    _segment.erase(_segment.begin() + idx);
    UpdateWidgetSize();
}

BranchNode *EditWidget::GetBranchNode(int idx) const
{
    std::vector<BlockNode*> blocks;
    for(int i=0;i<_segment.size();i++){
        blocks.push_back(_segment[i]->GetBlockNode(i));
    }
    bool left_is_literal;
    QString left_name = _condition_widget->GetLeftValue(left_is_literal);
    bool right_is_literal;
    QString right_name = _condition_widget->GetRightValue(right_is_literal);
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
    if(left_name.length() == 0 && right_name.length() == 0){
        QString warning("There is a branch number ");
        warning += QString::number(idx+1) + " in its Loop will always be true as no value in condition";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    else if(left_is_literal && VariableListWidget::CheckNameIsVariable(left_name)){
        QString warning("literal ");
        warning += left_name + " has the same name with a variable, but will not be treated as a variable";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    else if(right_is_literal && VariableListWidget::CheckNameIsVariable(right_name)){
        QString warning("literal ");
        warning += right_name + " has the same name with a variable, but will not be treated as a variable";
        CompileInfoStack::GetInstance()->PushWarning(warning);
    }
    std::string left_name_std = left_name.toStdString();
    std::string right_name_std = right_name.toStdString();
    return new BranchNode(blocks,idx,left_name_std,right_name_std,left_is_literal,right_is_literal,op);
}


void EditWidget::dragEnterEvent(QDragEnterEvent *event)
{
    this->_original_color = ChangeBKG(this,EditRegionBeingChosen);
    TurnOnShadowEffect(this);
    event->acceptProposedAction();
}

void EditWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    ChangeBKG(this,_original_color);
    TurnOffShadowEffect(this);
}

void EditWidget::dropEvent(QDropEvent *event)
{
    const BlockMimeData * blockMimeData = dynamic_cast<const BlockMimeData*>(event->mimeData());
    if(blockMimeData!=nullptr){
        AddLego(blockMimeData->GetKitName(),blockMimeData->GetBlockName(),blockMimeData->GetParams(),blockMimeData->GetHasReturn());
        event->acceptProposedAction();
    }
    ChangeBKG(this,_original_color);
    TurnOffShadowEffect(this);
}

void EditWidget::ShowAdjustWidgetAt(int idx)
{
    if(idx < 0 || idx >= _segment.size()){
        return;
    }
    int x = _segment[idx]->x() + _segment[idx]->width() + ADJWGTSPACING;
    int y = _segment[idx]->y();
    _adjust_widget->setVisible(true);
    _adjust_widget->setEnabled(true);
    _adjust_widget->move(x,y);
    _hovering_idx = idx;
    UpdateWidgetWidth();
}

void EditWidget::HideAdjustWidget()
{
    _hovering_idx = -1;
    _adjust_widget->setVisible(false);
    _adjust_widget->setEnabled(false);
}


void EditWidget::UpdateWidgetSize()
{
    int x = SIDE_EDGE;
    int y = TOP_BOTTOM_EDGE + _condition_widget->height() + 2*SPACING;
    int rect_x = x, rect_y = y;
    int rect_w = 0, rect_h = 0;
    int win_w = EditWidgetWidth;
    for(int i=0;i<_segment.size();i++){
        //移动Lego
        _segment[i]->move(x,y);
        //先更新窗口大小
        int w = x + _segment[i]->width();
        //如果adjustwidget是显示状态，则应该把它也计算到宽度中去
        if(_hovering_idx != -1 && _hovering_idx == i){
            w += ADJWGTSPACING + _adjust_widget->width();
        }
        if((w + SIDE_EDGE) > win_w){
            win_w = w + SIDE_EDGE;
        }
        //更新rect大小
        //rect的宽度应该是
        //SIDE_EDGE + LEGO宽度 + ADJWGTSPACING + _adjustwidget宽度
        int rw = SIDE_EDGE + _segment[i]->width() + ADJWGTSPACING + _adjust_widget->width();
        if(rw > rect_w){
            rect_w = rw;
        }
        //更新y
        //最后的y是在最后一个Lego的底部
        y += _segment[i]->height() + SPACING_BETWEEN_LEGOS;
        //更新rect_y
        rect_h += _segment[i]->height();
    }
    //如果adjustwidget窗口可见则调整其位置
    if(_hovering_idx!=-1){
        ShowAdjustWidgetAt(_hovering_idx);
    }

    //保证能完整显示condition widget
    int pw = SIDE_EDGE * 2 + _condition_widget->width();
    win_w = qMax(win_w,pw);
    //更新窗口大小
    win_w = (win_w > EditWidgetWidth) ? win_w : EditWidgetWidth;
    int win_h = (y + TOP_BOTTOM_EDGE) > EditWidgetHeight ? (y + TOP_BOTTOM_EDGE) : EditWidgetHeight;
    resize(win_w,win_h);
    //更新Rect大小
    rect_h = y;
    _segment_rect = QRect(rect_x,rect_y,rect_w,rect_h);
    //然后将condition widget放上去
    int cx = width()/2 - _condition_widget->width()/2;
    _condition_widget->move(cx,TOP_BOTTOM_EDGE);
}

void EditWidget::UpdateWidgetWidth()
{
    int cw = SIDE_EDGE * 2 + _condition_widget->width();
    int mw = 0;
    for(int i=0;i<_segment.size();i++){
        int w = SIDE_EDGE * 2 + _segment[i]->width();
        if(i == _hovering_idx){
            w += ADJWGTSPACING + _adjust_widget->width();
        }
        if(w > mw){
            mw = w;
        }
    }
    if(mw < cw){
        if(cw < EditWidgetWidth){
            cw = EditWidgetWidth;
        }
        resize(cw,height());
    }
    else{
        if(mw < EditWidgetWidth){
            mw = EditWidgetWidth;
        }
        resize(mw,height());
    }
    int x = width()/2 - _condition_widget->width()/2;
    _condition_widget->move(x,TOP_BOTTOM_EDGE);
}

void EditWidget::DeleteLego()
{
    RemoveLego(_hovering_idx);
}

void EditWidget::AdjustLegoUpward()
{
    if(_hovering_idx < 0 || _hovering_idx >= _segment.size()){
        return;
    }
    if(_hovering_idx == 0){
        return;
    }
    LegoWidget* up = _segment[_hovering_idx-1];
    LegoWidget* cur = _segment[_hovering_idx];
    _segment[_hovering_idx - 1] = cur;
    _segment[_hovering_idx] = up;
    UpdateWidgetSize();
    ShowAdjustWidgetAt(_hovering_idx);
}

void EditWidget::AdjustLegoDownward()
{
    if(_hovering_idx < 0 || _hovering_idx >= _segment.size()){
        return;
    }
    if(_hovering_idx == _segment.size() - 1){
        return;
    }
    LegoWidget* down = _segment[_hovering_idx+1];
    LegoWidget* cur = _segment[_hovering_idx];
    _segment[_hovering_idx + 1] = cur;
    _segment[_hovering_idx] = down;
    UpdateWidgetSize();
    ShowAdjustWidgetAt(_hovering_idx);
}
