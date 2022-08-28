#include "variablewidget.h"

#include "QLabel"
#include <QLineEdit>
#include <QFont>
#include <QFontMetrics>
#include "tool.h"
VariableWidget::VariableWidget(const QString &name, const QString &val, QColor color)
    :_name_label(new QLabel(this)),_value(new QLineEdit(this))
{
    _name_label->setText(name);
    _value->setPlaceholderText(val);
    ChangeBKG(this,color);
    connect(_value,&QLineEdit::editingFinished,this,&VariableWidget::TypeValue);
    setMouseTracking(true);
    UpdateSize();
}

void VariableWidget::TypeValue()
{
    UpdateSize();
}

void VariableWidget::UpdateSize()
{
    QFont font;
    font.setPointSize(FONTSIZE);
    QString v = _value->text();
    v = v.length() > 0 ? v : _value->placeholderText();
    if(v.length() == 0) v = "1";
    _name_label->setFont(font);
    _name_label->adjustSize();
    int lb = EMPTY_WIDTH;
    QSize size = QFontMetrics(font).boundingRect(v).size();
    size.setWidth(qMax(size.width(),lb) + EXTRA_SPACE_IN_LINEEDIT);

    _value->resize(size);
    int mh = qMax(_value->height(),_name_label->height()) + 2*EDGE;
    _name_label->move(EDGE,mh/2 - _name_label->height()/2);
    _value->move(_name_label->x() + _name_label->width() + SPACING, mh/2 - _value->height()/2);
    int w = _value->x() + _value->width() + EDGE;
    resize(w,mh);
    emit Resize();
}

QString VariableWidget::FetchValue() const
{
    QString v = _value->text();
    if(v.length() == 0){
        return _value->placeholderText();
    }
    else{
        return v;
    }
}

QString VariableWidget::FetchName() const
{
    return _name_label->text();
}


