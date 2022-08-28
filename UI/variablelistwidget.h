#ifndef VARIABLELISTWIDGET_H
#define VARIABLELISTWIDGET_H

#include <QWidget>
#include <vector>
#include <set>
#include "addvariabledialog.h"
class VariableWidget;
class QPushButton;
class VariableListWidget : public QWidget
{
    Q_OBJECT
public:
    VariableListWidget();
    static bool CheckUnique(const QString& s);
    static std::vector<QString> FetchAllVariablesNames();
    std::unordered_map<QString, QString> FetchAllVariableNamesAndValues();
    static bool CheckNameIsVariable(const QString &name);
    void mouseMoveEvent(QMouseEvent *event);
protected slots:
    void showDialog();
    void WhenConfirm();
    void UpdateWidthWhenInput();
    void WhenClickDelVariable();
protected:
    void UpdateSize();
    void AddVariable(const QString& name,const QString& v);
    void DelVariable(const QString& name);
signals:
private:
    std::vector<VariableWidget*> _variables;
    QPushButton* _add_btn,*_del_btn;
    static std::set<QString> ExistedVariables;
    enum{BTN_SIZE = 20,LEFT_ALLIGH = 5,EDGE = 2,SPACING = 3};
    AddVariableDialog dialog;
    int _del_idx;
};

#endif // VARIABLELISTWIDGET_H
