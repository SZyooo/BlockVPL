#include "segmentcontainerscrollarea.h"
#include <QResizeEvent>
#include "segmentcontainerwidget.h"


SegmentContainerScrollarea::SegmentContainerScrollarea()
    :_segment_widget(new SegmentContainerWidget)
{
    setWidget(_segment_widget);
    setMouseTracking(true);
    //AdjustInnerWidget();
    //connect(_segment_widget,&SegmentContainerWidget::WindowResize,this,&SegmentContainerScrollarea::AdjustInnerWidget);
}

ProgramNode *SegmentContainerScrollarea::GetProgramNode(const std::unordered_map<QString, QString>& gvs) const
{
    return _segment_widget->GetProgramNode(gvs);
}

void SegmentContainerScrollarea::resizeEvent(QResizeEvent *)
{
    AdjustInnerWidget();
}

void SegmentContainerScrollarea::AdjustInnerWidget()
{
    int w = _segment_widget->width();
    int h = _segment_widget->height();
    if(w < width()){
        w = width();
    }
    if(h < height()){
        h = height();
    }
    _segment_widget->resize(w,h);
}
