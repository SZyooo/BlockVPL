#ifndef LOOPSEGMENTSCROLLAREA_H
#define LOOPSEGMENTSCROLLAREA_H

#include <QScrollArea>

class LoopSegmentWidget;
class LoopNode;
class LoopSegmentScrollarea : public QScrollArea
{
    Q_OBJECT
public:
    LoopSegmentScrollarea();
    LoopNode* GetLoopNode(int idx)const;
    void resizeEvent(QResizeEvent *);
private slots:
    void AdjustInnerWidgetSize();
private:
    LoopSegmentWidget* _loop_segment_widget;
    enum{SPACING = 1};
};

#endif // LOOPSEGMENTSCROLLAREA_H
