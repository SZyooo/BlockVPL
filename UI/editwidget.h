#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <vector>
#include <QSize>
#include <QWidget>
#include <QRect>
#include "CommonValues.h"
class LegoWidget;
class ConditionWidget;
class AdjustWidget;
class BranchNode;
class EditWidget : public QWidget
{
    Q_OBJECT
public:
    EditWidget();
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    void AddLego(const QString kit_name, const QString& lego_name, const std::vector<QString>& params, bool has_return,QColor color = BlockDefaultColor);
    void RemoveLego(int idx);

    BranchNode* GetBranchNode(int idx)const;

    void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent *event);
private:
    void ShowAdjustWidgetAt(int idx);
    void HideAdjustWidget();
private slots:
    //比较麻烦的更新大小
    void UpdateWidgetSize();
    //只调整窗口宽度
    void UpdateWidgetWidth();
    void DeleteLego();
    void AdjustLegoUpward();
    void AdjustLegoDownward();
signals:

private:
    enum{SIDE_EDGE = 5,TOP_BOTTOM_EDGE = 3,SPACING = 5,ADJWGTSPACING = 2,SPACING_BETWEEN_LEGOS = 2};
    ConditionWidget* _condition_widget;
    AdjustWidget* _adjust_widget;
    std::vector<LegoWidget*> _segment;
    //将所有block包起来的最小rect
    QRect _segment_rect;
    int _hovering_idx;
    //用来记录当这个窗口在拖拽的过程中被选中改变颜色时候的初始颜色
    QColor _original_color;
};

#endif // EDITWIDGET_H
