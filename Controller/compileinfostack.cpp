#include "compileinfostack.h"



void CompileInfoStack::PushWarning(QString s)
{
    _warning_stack.push(s);
}

void CompileInfoStack::PopWarning()
{
    _warning_stack.pop();
}

QString CompileInfoStack::TopWarning() const
{
    return _warning_stack.top();
}

void CompileInfoStack::ResetWarning()
{
    std::stack<QString> e;
    _warning_stack.swap(e);
}

bool CompileInfoStack::IsWarningEmpty() const
{
    return _warning_stack.empty();
}

void CompileInfoStack::PushError(QString s)
{
    _error_stack.push(s);
}

void CompileInfoStack::PopError()
{
    _error_stack.pop();
}

QString CompileInfoStack::TopError() const
{
    return _error_stack.top();
}

void CompileInfoStack::ResetError()
{
    std::stack<QString> e;
    _error_stack.swap(e);
}

bool CompileInfoStack::IsErrorEmpty() const
{
    return _error_stack.empty();
}

void CompileInfoStack::PushMsg(QString s)
{
    _normal_msg_stack.push(s);
}

void CompileInfoStack::PopMsg()
{
    _normal_msg_stack.pop();
}

QString CompileInfoStack::TopMsg() const
{
    return _normal_msg_stack.top();
}

void CompileInfoStack::ResetMsg()
{
    std::stack<QString> empty;
    _normal_msg_stack.swap(empty);
}

bool CompileInfoStack::IsMsgEmpty() const
{
    return _normal_msg_stack.empty();
}

CompileInfoStack *CompileInfoStack::GetInstance()
{
    return Instance;
}
CompileInfoStack* CompileInfoStack::Instance = new CompileInfoStack;
