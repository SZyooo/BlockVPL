#ifndef SEGMENTCONTAINERSCROLLAREA_H
#define SEGMENTCONTAINERSCROLLAREA_H

#include <QScrollArea>

class SegmentContainerWidget;
class ProgramNode;
class SegmentContainerScrollarea : public QScrollArea
{
    Q_OBJECT
public:
    SegmentContainerScrollarea();
    ProgramNode* GetProgramNode(const std::unordered_map<QString, QString> &gvs)const;
    void resizeEvent(QResizeEvent *);
private:
    SegmentContainerWidget* _segment_widget;
protected slots:
    void AdjustInnerWidget();
};

#endif // SEGMENTCONTAINERSCROLLAREA_H
