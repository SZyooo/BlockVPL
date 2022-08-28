#ifndef VARIABLEWIDGET_H
#define VARIABLEWIDGET_H

#include <QWidget>
#include <set>
#include "CommonValues.h"

class QLabel;
class QLineEdit;
class VariableWidget : public QWidget
{
    Q_OBJECT
public:
    VariableWidget(const QString& name,const QString& val,QColor color = VariableColor);
    QString FetchValue() const;
    QString FetchName()const;
signals:
    void Resize();
protected slots:
    void TypeValue();
    void UpdateSize();

private:
    QLabel* _name_label;
    QLineEdit * _value;

    enum{FONTSIZE = 10,EDGE = 2, SPACING = 3,EXTRA_SPACE_IN_LINEEDIT = 5,EMPTY_WIDTH = 10};
};

#endif // VARIABLEWIDGET_H
