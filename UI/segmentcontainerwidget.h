#ifndef SEGMENTCONTAINERWIDGET_H
#define SEGMENTCONTAINERWIDGET_H

#include <QWidget>
#include <vector>

class LoopSegmentScrollarea;
class AdjustWidget;
class QPushButton;
class ProgramNode;
class SegmentContainerWidget : public QWidget
{
    Q_OBJECT
public:
    SegmentContainerWidget();
    ProgramNode* GetProgramNode(const std::unordered_map<QString, QString> &gvs)const;

    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
protected slots:
    void WhenAddALoop();
    void WhenDelALoop();
    void WhenSwitchUpward();
    void WhenSwitchDownward();
protected:
    void AddLoop();
    void DelLoop(size_t idx);
    void SwitchUpward(int idx);
    void SwitchDownward(int idx);
    void UpdateView();
    void ShowAdjBtnsAt(int idx);
    void HideAdjBtns();
signals:
    void WindowResize();
private:
    enum{BUTTON_SIZE = 50,SPACING_BETWEEN_ADDBTN_LOOP = 10,SPACING_BETWEEN_LOOP_ADJUST,EDGE = 2,
        SPACING_BETWEEN_LOOP_LOOP = 2};
    std::vector<LoopSegmentScrollarea*> _loop_areas;
    AdjustWidget* _adjust_widget;
    QPushButton* _add_btn;
    int _hovering_idx;
};

#endif // SEGMENTCONTAINERWIDGET_H
