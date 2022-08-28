#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QWidget>
#include <CommonValues.h>
class InputWidget;
class QComboBox;
class ConditionWidget : public QWidget
{
    Q_OBJECT
public:
    ConditionWidget();
    QString GetLeftValue(bool& is_literal) const;
    QString GetRightValue(bool& is_literal) const;
    Condition GetCondition() const;
protected slots:
    void UpdateSize();
signals:
    void WidgetResize();
private:
    InputWidget* _left,*_right;
    QComboBox* _combobox;
    enum{FONTSIZE = 15,SPACING = 2,EDGE = 2};
};

#endif // CONDITIONWIDGET_H
