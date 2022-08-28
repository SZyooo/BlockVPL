#include "addvariabledialog.h"

AddVariableDialog::AddVariableDialog()
{

    _var_name.setPlaceholderText("variable name");
    _var_value.setPlaceholderText("variable value");
    _confirm.setText("Confirm");
    _cancel.setText("Cancel");
    _layout.addWidget(&_var_name);
    _layout.addWidget(&_var_value);
    _layout.addWidget(&_confirm);
    _layout.addWidget(&_cancel);
    setLayout(&_layout);
    setModal(true);
    connect(&_confirm,&QPushButton::clicked,this,&AddVariableDialog::Confirm);
    connect(&_cancel,&QPushButton::clicked,this,&AddVariableDialog::Cancel);
}

AddVariableDialog::~AddVariableDialog()
{
    _var_name.setParent(nullptr);
    _var_value.setParent(nullptr);
    _confirm.setParent(nullptr);
    _cancel.setParent(nullptr);
}

QString AddVariableDialog::GetName() const
{
    return _name;
}

QString AddVariableDialog::GetValue() const
{
    return _value;
}

bool AddVariableDialog::Accept() const
{
   return _code == QDialog::Accepted;
}


void AddVariableDialog::Confirm()
{
    _name = _var_name.text();
    _value = _var_value.text();
    _code = QDialog::Accepted;
    _var_name.setText("");
    _var_value.setText("");
    emit Done();
}

void AddVariableDialog::Cancel()
{
    _var_name.setText("");
    _var_value.setText("");
    _code = QDialog::Rejected;
    close();
}
