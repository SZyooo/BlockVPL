#include "blockbox.h"
#include "blocklistscrollarea.h"
BlockBox::BlockBox()
{
    setMouseTracking(true);
}

QString BlockBox::AddKit(const QString &kit_name, const QString &kit_des, const std::vector<QString> &block_names, const std::vector<QString> &block_deses, const std::vector<std::vector<QString> > &params,
                         const std::vector<bool> has_returns, const std::vector<QColor> &colors)
{
    setToolTip(kit_des);
    QString kitname = "";
    if(_kitname_index.find(kit_name)!=_kitname_index.end()){
        int suffix = 1;
        QString new_name = "";
        while(true){
            new_name = kit_name + QString("(") + QString::number(suffix) + QString(")");
            if(_kitname_index.find(new_name)==_kitname_index.end()){
                break;
            }
        }
        kitname = new_name;
    }
    else{
        kitname = kit_name;
    }
    BlockListScrollarea* bls = new BlockListScrollarea(kitname,block_names,block_deses,params,has_returns,colors);
    int idx = addItem(bls,kitname);
    _kitname_index.insert({kitname,idx});
    return kitname;
}
