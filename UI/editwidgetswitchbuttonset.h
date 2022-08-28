#ifndef EDITWIDGETSWITCHBUTTONSET_H
#define EDITWIDGETSWITCHBUTTONSET_H

#include <QWidget>

class QPushButton;
class EditWidgetSwitchButtonSet : public QWidget
{
    Q_OBJECT
public:
    EditWidgetSwitchButtonSet();
public slots:
    void ClickLeft();
    void ClickRight();
    void ClickRemove();
signals:
    void Left();
    void Right();
    void Delete();
private:
    QPushButton* _left, *_right, * _remove;
    enum{BUTTON_SIZE = 30,SPACING = 2,EDGE = 2};
};

#endif // EDITWIDGETSWITCHBUTTONSET_H
