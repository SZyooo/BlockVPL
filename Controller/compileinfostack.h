#ifndef COMPILEINFOSTACK_H
#define COMPILEINFOSTACK_H

#include <QString>
#include <stack>
class CompileInfoStack
{
public:
    void PushWarning(QString s);
    void PopWarning();
    QString TopWarning()const;
    void ResetWarning();
    bool IsWarningEmpty()const;

    void PushError(QString s);
    void PopError();
    QString TopError()const;
    void ResetError();
    bool IsErrorEmpty()const;

    void PushMsg(QString s);
    void PopMsg();
    QString TopMsg()const;
    void ResetMsg();
    bool IsMsgEmpty()const;

    static CompileInfoStack* GetInstance();
private:
    static CompileInfoStack* Instance;
    CompileInfoStack(){}
    std::stack<QString> _error_stack;
    std::stack<QString> _warning_stack;
    std::stack<QString> _normal_msg_stack;
};

#endif // COMPILEINFOSTACK_H
