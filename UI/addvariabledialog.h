#ifndef ADDVARIABLEDIALOG_H
#define ADDVARIABLEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class AddVariableDialog : public QDialog
{
    Q_OBJECT
public:
    AddVariableDialog();
    ~AddVariableDialog();
    QString GetName() const;
    QString GetValue() const;
    bool Accept() const;
public:
    void Confirm();
    void Cancel();
signals:
    void Done();
private:
    QLineEdit _var_name,_var_value;
    QPushButton _confirm,_cancel;
    QVBoxLayout _layout;
    QString _name,_value;
    int _code;
};

#endif // ADDVARIABLEDIALOG_H
