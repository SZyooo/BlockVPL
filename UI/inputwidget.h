#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QComboBox>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <vector>
class InputWidget : public QComboBox
{
    Q_OBJECT
public:

    InputWidget(const std::vector<QString> &variables);
    //不给出variable列表的话，无参数的构造函数会调用FetchVariables去取
    InputWidget();
    void UpdateVariables(const std::vector<QString> &variables);
    bool IsLiteral() const;
    QString FetchValue() const;
    void SetPlaceHolderValue(const QString& placeholder);
protected:
    //s是输入框的字符串
    void UpdateSize(QString s);
    //从controller中取出variables并且更新
    void FetchVariables();
protected slots:
    void SelectAItem(int idx);
    void InputValue(const QString& s);
signals:
    void WindowReisze();
private:
    QLineEdit* _input;
    bool _is_literal;
    enum{FONTSIZE = 15,DROP_ICON_SIZE = 20,MINIMUM_INPUT_WIDTH = 25};
    int _current_width;//当前输入框的最大长度
};

#endif // INPUTWIDGET_H
