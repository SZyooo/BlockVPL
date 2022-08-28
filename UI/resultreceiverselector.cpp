#include "resultreceiverselector.h"
#include <QFont>
#include <QFontMetrics>
#include "tool.h"
#include "variablelistwidget.h"
ResultReceiverSelector::ResultReceiverSelector(const std::vector<QString> &variables)
{
    QFont font;
    font.setPointSize(FONT_SIZE);
    setFont(font);
    UpdateView(variables);
    connect(this,&ResultReceiverSelector::activated,this,&ResultReceiverSelector::Select);
}

ResultReceiverSelector::ResultReceiverSelector()
{
    UpdateVariables();
    connect(this,&ResultReceiverSelector::activated,this,&ResultReceiverSelector::Select);
}

void ResultReceiverSelector::UpdateVariables()
{
    //刷新变量列表
    //Print("ResultReceiverSelector::UpdateVariables needs to finish");
    //UpdateVariables();
    UpdateView(VariableListWidget::FetchAllVariablesNames());

}

QString ResultReceiverSelector::FetchCurrentVariable() const
{
    if(currentIndex() == 0 || currentIndex() == 1){
        return "";
    }
    return currentText();
}

void ResultReceiverSelector::UpdateView(const std::vector<QString> &variables)
{
    QString s1 = "(Discard)";
    QString s2 = "(Update)";
    clear();
    addItem(s1);
    addItem(s2);
    QFontMetrics fm(font());
    QSize size = fm.tightBoundingRect(s1).size();
    for(int i=0;i<variables.size();i++){
        QString s = variables[i];
        QSize sz = fm.tightBoundingRect(s).size();
        if(sz.width() > size.width()){
            size.setWidth(sz.width());
        }
        if(sz.height() > size.height()){
            size.setHeight(sz.height());
        }
        addItem(s);
    }
    size.setWidth(size.width() + EDGE + DROP_ICON_SPACE);
    size.setHeight(size.height() + 2* EDGE);
    resize(size);
}

void ResultReceiverSelector::Select(int idx)
{
    if(idx == 1){
        setCurrentIndex(0);
        UpdateVariables();
    }
}
