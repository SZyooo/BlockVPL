#include "legowidget.h"
#include "inputwidget.h"
#include "tool.h"
#include "resultreceiverselector.h"
#include "Controller/compileinfostack.h"
#include "VRE/Node.h"
#include "CommonValues.h"
LegoWidget::LegoWidget(const QString &kit_name, const QString &lego_name, const std::vector<QString> &params,bool has_return, QColor color)
    :_kit_name(kit_name),_lego_name_label(new QLabel(lego_name,this)),_param_names(params)
{
    for(int i=0;i<params.size();i++){
        InputWidget* iw = new InputWidget;
        iw->SetPlaceHolderValue(_param_names[i]);
        this->_param_input_widgets.push_back(iw);
        connect(iw,&InputWidget::WindowReisze,this,&LegoWidget::UpdateSize);
        iw->setParent(this);
    }
    if(has_return){
        _receiver = new ResultReceiverSelector;
        _receiver->setParent(this);
        _return_label = new QLabel("Return",this);
    }
    else{
        _receiver = nullptr;
        _return_label = nullptr;
    }
    setMouseTracking(true);
    //TurnOnShadowEffect(this);
    UpdateSize();
    ChangeBKG(this,color);
}

QString LegoWidget::FetchParamsValue(const QString &param_name, bool &is_literal)
{
    int idx = -1;
    for(int i=0;i<_param_names.size();i++){
        if(_param_names[i] == param_name){
            idx = i;
            break;
        }
    }
    if(idx == -1){
        throw "no such param";
    }
    else{
        is_literal = _param_input_widgets[idx]->IsLiteral();
        return _param_input_widgets[idx]->FetchValue();
    }
}

QString LegoWidget::FetchParamsValue(int idx,bool& is_literal)
{
    if(idx < 0 || idx >= _param_input_widgets.size()){
        throw "param's index is out of bound";
    }
    else{
        is_literal = _param_input_widgets[idx]->IsLiteral();
        return _param_input_widgets[idx]->FetchValue();
    }
}

bool LegoWidget::FetchResult(QString &res)
{
    if(_receiver == nullptr){
        return false;
    }
    else{
        res = _receiver->FetchCurrentVariable();
        return true;
    }
}

QString LegoWidget::KitName() const
{
    return _kit_name;
}


BlockNode *LegoWidget::GetBlockNode(int idx) const
{
    vector<pair<string,bool>> params;
    for(int i=0;i<_param_input_widgets.size();i++){
        QString str = _param_input_widgets[i]->FetchValue();
        bool is_literal = _param_input_widgets[i]->IsLiteral();
        params.push_back({str.toStdString(),is_literal});
        if(str.length() == 0){
            QString warning;
            warning += "A" + _lego_name_label->text() + "has an empty parameter";
            CompileInfoStack::GetInstance()->PushWarning(warning);
        }
    }
    QString block_name = _lego_name_label->text();
    if(KitName_ExePath.contains(_kit_name) == false){
        QString error;
        error += "A" + _lego_name_label->text() + "cannot find .exe file";
        CompileInfoStack::GetInstance()->PushError(error);
        return nullptr;
    }
    QString exe = KitName_ExePath[_kit_name];
    QString res;
    if(_receiver == nullptr){
        res = "";
    }else{
        res = _receiver->FetchCurrentVariable();
    }
    return new BlockNode(params,block_name.toStdString(),idx,exe.toStdString(),
                         OutputFilePath.toStdString(),res.toStdString());
}

void LegoWidget::UpdateSize()
{
    QFont font;
    font.setPointSize(FONTSIZE);
    _lego_name_label->setFont(font);
    QSize size = QFontMetrics(font).tightBoundingRect(_lego_name_label->text()).size();
    _lego_name_label->setGeometry(EDGE,EDGE,size.width()+2,size.height()+2);
    int x = _lego_name_label->x() + _lego_name_label->width() + SPACING;
    int p_height = 0;
    //设置params
    for(int i=0;i<_param_input_widgets.size();i++){
        _param_input_widgets[i]->move(x,EDGE);
        p_height = _param_input_widgets[i]->height();
        x = _param_input_widgets[i]->x() + _param_input_widgets[i]->width() + SPACING;
    }
    //设置接收
    if(_receiver){
        x = x - SPACING + SPACING_BETWEEN_PARAM_RETURN;
        _return_label->setFont(font);
        //QSize return_size = QFontMetrics(font).tightBoundingRect("Return").size();
        //_return_label->resize(return_size);
        _return_label->adjustSize();
        _return_label->move(x,EDGE);
        if(p_height < _return_label->height()){
            p_height = _return_label->height();
        }
        x = _return_label->x() + _return_label->width() + SPACING;
        _receiver->move(x,EDGE);
        if(p_height < _receiver->height()){
            p_height = _receiver->height();
        }
        x = _receiver->x() + _receiver->width();
    }
    int wid = x + EDGE;
    int hei = size.height() > p_height?size.height() : p_height;
    hei += 2*EDGE;
    resize(wid,hei);
    emit ResizeWindow();
}
