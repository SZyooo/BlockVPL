#ifndef VARIABLELISTSCROLLAREA_H
#define VARIABLELISTSCROLLAREA_H

#include <QScrollArea>
#include <unordered_map>
class VariableListWidget;
class VariableListScrollarea : public QScrollArea
{
    Q_OBJECT
public:
    VariableListScrollarea();
    std::unordered_map<QString, QString> FetchAllVariableNamesAndValues();
private:
    VariableListWidget* _variable_list_widget;
};

#endif // VARIABLELISTSCROLLAREA_H
