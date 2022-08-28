#ifndef EDITSCROLLAREA_H
#define EDITSCROLLAREA_H

#include <QScrollArea>

class EditWidget;
class BranchNode;
//将EditWidget作为主Widget的scrollarea
class EditScrollarea : public QScrollArea
{
    Q_OBJECT
public:
    EditScrollarea();
    BranchNode* GetBranchNode(int idx) const;
private:
    EditWidget* _edit_widget;
};

#endif // EDITSCROLLAREA_H
