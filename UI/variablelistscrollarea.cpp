#include "variablelistscrollarea.h"
#include "variablelistwidget.h"
#include "tool.h"
#include "CommonValues.h"
VariableListScrollarea::VariableListScrollarea()
    :_variable_list_widget(new VariableListWidget)
{
    setWidget(_variable_list_widget);
    ChangeBKG(this,VariableListCOlor);
}

std::unordered_map<QString, QString> VariableListScrollarea::FetchAllVariableNamesAndValues()
{
    return _variable_list_widget->FetchAllVariableNamesAndValues();
}
