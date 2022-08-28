#include "variablelistwidget.h"

#include <QPushButton>
#include "variablewidget.h"
#include "tool.h"
#include <QMessageBox>
#include <unordered_map>
#include "Controller/compileinfostack.h"
VariableListWidget::VariableListWidget()
    :_add_btn(new QPushButton),_del_btn(new QPushButton),_del_idx(-1)
{
    _add_btn->setParent(this);
    _add_btn->resize(BTN_SIZE,BTN_SIZE);
    _add_btn->setText("+");
    _del_btn->setParent(this);
    _del_btn->resize(BTN_SIZE,BTN_SIZE);
    _del_btn->setText("x");
    _del_btn->setEnabled(false);
    _del_btn->setVisible(false);

    UpdateSize();
    dialog.close();
    connect(_add_btn,&QPushButton::clicked,this,&VariableListWidget::showDialog);
    connect(_del_btn,&QPushButton::clicked,this,&VariableListWidget::WhenClickDelVariable);
    connect(&dialog,&AddVariableDialog::Done,this,&VariableListWidget::WhenConfirm);
    setMouseTracking(true);
}

bool VariableListWidget::CheckUnique(const QString &s)
{
    return ExistedVariables.find(s) == ExistedVariables.end();
}

std::vector<QString> VariableListWidget::FetchAllVariablesNames()
{
    std::vector<QString> res(ExistedVariables.begin(),ExistedVariables.end());
    return res;
}

std::unordered_map<QString,QString> VariableListWidget::FetchAllVariableNamesAndValues()
{
    std::unordered_map<QString,QString> res;
    for(int i=0;i<_variables.size();i++){
        QString name = _variables[i]->FetchName();
        QString value = _variables[i]->FetchValue();
        if(value.length() == 0){
            QString warning("variable ");
            warning += name + " has empty value";
            CompileInfoStack::GetInstance()->PushWarning(warning);
        }
        res.insert({name,value});
    }
    return res;
}

bool VariableListWidget::CheckNameIsVariable(const QString& name)
{
    return ExistedVariables.find(name)!=ExistedVariables.end();
}

void VariableListWidget::mouseMoveEvent(QMouseEvent *event)
{
    int y = static_cast<int>(event->position().y());
    int idx = -1;
    int u,b;
    for(int i = 0; i< _variables.size();i++){
        u = _variables[i]->y();
        b = _variables[i]->y() + _variables[i]->height();
        if(y>=u && y <=b){
            idx = i;
            break;
        }
        if(u > y)break;
    }
    //Print(QString::number(idx));
    if(idx!=-1){
        int x = _variables[idx]->x() + _variables[idx]->width() + SPACING;
        _del_btn->move(x,u);
        _del_btn->setVisible(true);
        _del_btn->setEnabled(true);
    }else{
        _del_btn->setVisible(false);
        _del_btn->setEnabled(false);
    }
    _del_idx = idx;
}


void VariableListWidget::AddVariable(const QString &name, const QString &v)
{
    if(CheckUnique(name) && VerifyValue(name)){
        VariableWidget* vw = new VariableWidget(name,v);
        vw->setParent(this);
        _variables.push_back(vw);
        vw->show();
        ExistedVariables.insert(name);
        connect(vw,&VariableWidget::Resize,this,&VariableListWidget::UpdateWidthWhenInput);
        UpdateSize();
    }
}

void VariableListWidget::DelVariable(const QString &name)
{
    int idx = -1;
    for(int i=0;i<_variables.size();i++){
        if(_variables[i]->FetchName() == name){
            idx = i;
            break;
        }
    }
    if(idx == -1){
        throw "exception:no such variable, this should not happen";
    }
    else{
        _variables.erase(_variables.begin() + idx);
        ExistedVariables.erase(name);
        UpdateSize();
    }
}

void VariableListWidget::showDialog()
{
    dialog.show();
}

void VariableListWidget::WhenConfirm()
{
    QString name = dialog.GetName();
    QString val = dialog.GetValue();
    QString error = "";
    bool success = true;
    if(CheckUnique(name)==false){
        error ="Error","Duplicate Variable";
        success = false;
    }
    else if(VerifyValue(name) == false){
        error = verification_error;
        success = false;
    }
    if(!success){
        QMessageBox::StandardButton reply =
            QMessageBox::critical(this,"Error",error,QMessageBox::Abort | QMessageBox::Retry);
        if(reply == QMessageBox::Retry){
            return;
        }
        else{
            dialog.close();
        }
    }
    else{
        AddVariable(name,val);
        dialog.close();
    }
}

void VariableListWidget::UpdateWidthWhenInput()
{
    QWidget* w = focusWidget();
    int wid = LEFT_ALLIGH + w->width() + EDGE;
    if(wid > width()){
        resize(wid,height());
    }
    else{
        UpdateSize();
    }
}

void VariableListWidget::WhenClickDelVariable()
{
    if(_del_idx < 0 || _del_idx >= _variables.size()){
        Print("Critical Error: VariableListWidget::WhenClickDelVariable");
        return;
    }
    VariableWidget* variable_widget = _variables[_del_idx];
    _variables.erase(_variables.begin() + _del_idx);
    ExistedVariables.erase(variable_widget->FetchName());
    delete variable_widget;
    //如果是最后一个，那么删掉之后应该隐藏删除按钮
    if(_del_idx == _variables.size()){
        _del_idx = -1;
        _del_btn->setEnabled(false);
        _del_btn->setVisible(false);
    }
    else{
        _del_idx --;
    }
    UpdateSize();
}

void VariableListWidget::UpdateSize()
{
    int y = EDGE;
    int mw = 0;
    for(int i=0;i<_variables.size();i++){
        _variables[i]->move(LEFT_ALLIGH,y);
        y = _variables[i]->y() + _variables[i]->height() + SPACING;
        int w = EDGE * 2 + _variables[i]->width();
        if(w > mw){
            mw = w;
        }
    }
    _add_btn->move(EDGE,y);
    y = _add_btn->y() + _add_btn->height() + EDGE;
    int btn_w = _add_btn->x() + _add_btn->width() + EDGE;
    if(mw < btn_w){
        mw = btn_w;
    }
    mw += SPACING + BTN_SIZE;
    resize(mw,y);
}

std::set<QString> VariableListWidget::ExistedVariables = std::set<QString>();
