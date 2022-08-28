#ifndef LOOPSEGMENTWIDGET_H
#define LOOPSEGMENTWIDGET_H

#include <QWidget>
#include <vector>
class EditWidgetSwitchButtonSet;
class EditScrollarea;
class ConditionWidget;
class QPushButton;
class LoopNode;
class LoopSegmentWidget : public QWidget
{
    Q_OBJECT
public:
    LoopSegmentWidget();
    LoopNode* GetLoopNode(int idx)const;

    void mouseMoveEvent(QMouseEvent *event);
signals:
    void WindowResize();
protected:
    void HideBtnSet();
    void ShowBtnSetAt(int idx);
    void RemoveEditArea(int idx);
    void UpdateView();
    void SwitchLeft(int idx);
    void SwitchRight(int idx);
protected slots:
    void AddEditArea();
    void WhenClickLeft();
    void WhenClickRight();
    void WhenClickRemove();
private:
    std::vector<EditScrollarea*> _edit_areas;
    EditWidgetSwitchButtonSet* _btn_set;
    ConditionWidget* _condition_widget;
    QPushButton* _add_btn;
    enum{
      SPACING_BETWEEN_EDIT_AREAS = 2,
      SPACING_BETWEEN_EDIT_AREA_AND_BTNSET = 3,
      EDGE = 3,
      ADD_BTN_SIZE = 15,
      SPACING_BETWEEN_CONDITION_ADDBTN = 2,
      ADD_BTN_FONT = 10
    };
    int _hovering_idx;
};

#endif // LOOPSEGMENTWIDGET_H
