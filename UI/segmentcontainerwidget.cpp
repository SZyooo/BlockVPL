#include "segmentcontainerwidget.h"

#include <QPushButton>
#include "loopsegmentscrollarea.h"
#include "adjustwidget.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include "VRE/Node.h"
#include "variablelistwidget.h"
SegmentContainerWidget::SegmentContainerWidget()
    :_adjust_widget(new AdjustWidget),_add_btn(new QPushButton("+",this)),
      _hovering_idx(-1)
{
    _adjust_widget->setParent(this);
    _add_btn->resize(BUTTON_SIZE,BUTTON_SIZE);
    setMouseTracking(true);
    connect(_adjust_widget,&AdjustWidget::Up,this,&SegmentContainerWidget::WhenSwitchUpward);
    connect(_adjust_widget,&AdjustWidget::Down,this,&SegmentContainerWidget::WhenSwitchDownward);
    connect(_adjust_widget,&AdjustWidget::Delete,this,&SegmentContainerWidget::WhenDelALoop);
    connect(_add_btn,&QPushButton::clicked,this,&SegmentContainerWidget::WhenAddALoop);
   //_adjust_widget->close();
    UpdateView();
    //HideAdjBtns();
}
ProgramNode *SegmentContainerWidget::GetProgramNode(const std::unordered_map<QString, QString>& gvs) const
{
    std::vector<LoopNode*> loops;
    for(int i=0;i<_loop_areas.size();i++){
        loops.push_back(_loop_areas[i]->GetLoopNode(i));
    }
    std::unordered_map<std::string,std::string> t_variables;
    for(auto it = gvs.begin();it!=gvs.end();it++){
        std::string name = it->first.toStdString();
        std::string value = it->second.toStdString();
        t_variables.insert({name,value});
    }
    return new ProgramNode(loops,t_variables);
}

void SegmentContainerWidget::resizeEvent(QResizeEvent *event)
{
    UpdateView();
}

void SegmentContainerWidget::mouseMoveEvent(QMouseEvent *event)
{
    bool found = false;
    int y = static_cast<int>(event->position().y());
    for(int i=0;i<_loop_areas.size();i++){
        int upper = _loop_areas[i]->y();
        int lower = upper + _loop_areas[i]->height();
        if(y > upper && y <= lower){
            found = true;
            _hovering_idx = i;
            break;
        }
    }
    if(found){
        ShowAdjBtnsAt(_hovering_idx);
    }
    else{
        HideAdjBtns();
    }
}

void SegmentContainerWidget::WhenAddALoop()
{
    AddLoop();
}

void SegmentContainerWidget::WhenDelALoop()
{
    DelLoop(_hovering_idx);
}

void SegmentContainerWidget::WhenSwitchUpward()
{
    SwitchUpward(_hovering_idx);
}

void SegmentContainerWidget::WhenSwitchDownward()
{
    SwitchDownward(_hovering_idx);
}

void SegmentContainerWidget::AddLoop()
{
    LoopSegmentScrollarea* lss = new LoopSegmentScrollarea;
    lss->setParent(this);
    _loop_areas.push_back(lss);
    lss->show();
    UpdateView();
}

void SegmentContainerWidget::DelLoop(size_t idx)
{
    if(idx < _loop_areas.size()){
        LoopSegmentScrollarea* lss = _loop_areas[idx];
        //删除的是最后一个
        if(idx == _hovering_idx && _hovering_idx == _loop_areas.size() - 1){
            _hovering_idx = -1;
            HideAdjBtns();
        }
        _loop_areas.erase(_loop_areas.begin()+idx);
        delete lss;
        UpdateView();
    }
}

void SegmentContainerWidget::SwitchUpward(int idx)
{
    if(idx == 0)
    {
        return;
    }
    LoopSegmentScrollarea* lss = _loop_areas[idx - 1];
    _loop_areas[idx - 1] = _loop_areas[idx];
    _loop_areas[idx] = lss;
    UpdateView();
}

void SegmentContainerWidget::SwitchDownward(int idx)
{
    if(idx == _loop_areas.size() - 1)
    {
        return;
    }
    LoopSegmentScrollarea* lss = _loop_areas[idx + 1];
    _loop_areas[idx + 1] = _loop_areas[idx];
    _loop_areas[idx] = lss;
    UpdateView();
}

void SegmentContainerWidget::UpdateView()
{
    //先排放Loop areas
    //右边界 adjust窗口的宽度 缝隙 左边界
    int w = width() - EDGE - _adjust_widget->width() - SPACING_BETWEEN_LOOP_ADJUST - EDGE;
    int x = EDGE,y = EDGE;
    for(int i=0;i<_loop_areas.size();i++){
        int h = _loop_areas[i]->height();
        _loop_areas[i]->setGeometry(x,y,w,h);
        y += h + SPACING_BETWEEN_LOOP_LOOP;
    }
    //安放添加按钮
    int btn_x = x;
    int btn_y = y;
    _add_btn->move(btn_x,btn_y);
    int ph = btn_y + _add_btn->height() + EDGE;
    int pw = qMax(qMax(btn_x + _add_btn->width(),_adjust_widget->width()),width());
    resize(pw,ph);
    //安放调整按钮
    ShowAdjBtnsAt(_hovering_idx);
    //emit WindowResize();
}

void SegmentContainerWidget::ShowAdjBtnsAt(int idx)
{
    if(_hovering_idx!=-1){
        _adjust_widget->setVisible(true);
        _adjust_widget->setEnabled(true);
        LoopSegmentScrollarea* loop = _loop_areas[_hovering_idx];
        int adj_x = loop->x() + loop->width() + SPACING_BETWEEN_LOOP_ADJUST;
        int adj_y = loop->y() + loop->height()/2 - _adjust_widget->height()/2;
        _adjust_widget->move(adj_x,adj_y);
    }
}

void SegmentContainerWidget::HideAdjBtns()
{
    _adjust_widget->setVisible(false);
    _adjust_widget->setEnabled(false);
}
