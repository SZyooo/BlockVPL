#include "loopsegmentscrollarea.h"
#include "CommonValues.h"
#include "loopsegmentwidget.h"
#include "tool.h"
#include <QResizeEvent>
#include "VRE/Node.h"
LoopSegmentScrollarea::LoopSegmentScrollarea()
    :_loop_segment_widget(new LoopSegmentWidget)
{
    setFixedHeight(_loop_segment_widget->height());
    setMouseTracking(true);
    ChangeBKG(this,LoopAreaBKG);
    TurnOnShadowEffect(_loop_segment_widget);
    connect(_loop_segment_widget,&LoopSegmentWidget::WindowResize,this,&LoopSegmentScrollarea::AdjustInnerWidgetSize);
    AdjustInnerWidgetSize();
    setWidget(_loop_segment_widget);
}

LoopNode *LoopSegmentScrollarea::GetLoopNode(int idx) const
{
    return _loop_segment_widget->GetLoopNode(idx);
}

void LoopSegmentScrollarea::resizeEvent(QResizeEvent *)
{
    AdjustInnerWidgetSize();
}

void LoopSegmentScrollarea::AdjustInnerWidgetSize()
{
    int w = _loop_segment_widget->width();
    int h = _loop_segment_widget->height();
    if(w < width()){
        w = width();
    }
    if(h < height()){
        h = height();
    }
    _loop_segment_widget->resize(w,h);
}
