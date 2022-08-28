#include "inputwidget.h"
#include <QFont>
#include <QFontMetrics>
#include <QSize>
#include <tool.h>
#include "variablelistwidget.h"

InputWidget::InputWidget(const std::vector<QString>& variables)
    :_input(new QLineEdit(this)),_is_literal(true),_current_width(MINIMUM_INPUT_WIDTH)
{
    UpdateVariables(variables);
    setMouseTracking(true);
    connect(this,&InputWidget::activated,this,&InputWidget::SelectAItem);
    connect(this->_input,&QLineEdit::textChanged,this,&InputWidget::InputValue);
    connect(this->_input,&QLineEdit::textEdited,this,&InputWidget::InputValue);
}

InputWidget::InputWidget()
    :_input(new QLineEdit(this)),_is_literal(true),_current_width(MINIMUM_INPUT_WIDTH)
{
    UpdateVariables({});
    FetchVariables();
    setMouseTracking(true);
    connect(this,&InputWidget::activated,this,&InputWidget::SelectAItem);
    connect(this->_input,&QLineEdit::textChanged,this,&InputWidget::InputValue);
    connect(this->_input,&QLineEdit::textEdited,this,&InputWidget::InputValue);
}

void InputWidget::UpdateVariables(const std::vector<QString>& variables)
{
    clear();
    QString longgest_str = QString("(Type in)");
    addItem("(Type in)");
    addItem("(Refresh)");
    for(int i=0;i<variables.size();i++){
        addItem(variables[i]);
        if(variables[i].length() > longgest_str.length()){
            longgest_str = variables[i];
        }
    }
    QFont font;
    font.setPointSize(FONTSIZE);
    QSize size = QFontMetrics(font).tightBoundingRect(longgest_str).size();
    int width = MINIMUM_INPUT_WIDTH>size.width()?MINIMUM_INPUT_WIDTH:size.width();
    int dropbox_width = width + DROP_ICON_SIZE;
    int input_width = width;
    int height = size.height();
    resize(dropbox_width,height);
    _input->resize(input_width,height);
    _input->move(0,0);
    setFont(font);
    _input->setFont(font);
    _current_width = width;
}

bool InputWidget::IsLiteral() const
{
    return this->_is_literal;
}

QString InputWidget::FetchValue() const
{
    return _input->text();
}

void InputWidget::SetPlaceHolderValue(const QString &placeholder)
{
    _input->setPlaceholderText(placeholder);
}

void InputWidget::UpdateSize(QString s)
{
    QFont font;
    font.setPointSize(FONTSIZE);
    QSize size= QFontMetrics(font).tightBoundingRect(s).size();
    if(size.width() > _current_width){
        resize(size.width() + DROP_ICON_SIZE,height());
        _input->resize(size.width() + 5,height());
        _input->move(0,0);
        emit WindowReisze();
    }
    else{
        resize(_current_width + DROP_ICON_SIZE,height());
        _input->resize(_current_width,height());
        _input->move(0,0);
        emit WindowReisze();
    }
}
void InputWidget::FetchVariables()
{
    //Print("(InputWidget)waiting to finish: InputWidget::FetchVariables");
    UpdateVariables(VariableListWidget::FetchAllVariablesNames());
    //从controller取出变量列表
    //UpdateVariables
}

void InputWidget::SelectAItem(int idx)
{
    if(idx == 0){
        //用户选择输入
        _input->setEnabled(true);
        if(this->_is_literal == false)
        {
            _input->setText("");
        }
        this->_is_literal = true;
    }
    else if(idx == 1){
        //更新变量
        FetchVariables();
    }
    else{
        _input->setText(itemText(idx));
        _input->setEnabled(false);
        this->_is_literal = false;
    }
}

void InputWidget::InputValue(const QString &s)
{
    UpdateSize(s);
}
