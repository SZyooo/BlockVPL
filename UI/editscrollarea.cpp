#include "editscrollarea.h"
#include "CommonValues.h"
#include "UI/editwidget.h"
#include "tool.h"
EditScrollarea::EditScrollarea()
    :_edit_widget(new EditWidget)
{
    setWidget(_edit_widget);
    //_edit_widget->setGeometry(0,0,EditWidgetWidth,EditWidgetHeight);
    ChangeBKG(this,EditWidgetBKG);
    TurnOnShadowEffect(_edit_widget);
    setFixedSize(EditWidgetWidth,EditWidgetHeight);
    setMouseTracking(true);
}

BranchNode *EditScrollarea::GetBranchNode(int idx) const
{
    return _edit_widget->GetBranchNode(idx);
}
