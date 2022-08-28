#include "blocklistwidget.h"
#include "tool.h"
#include "blockwidget.h"
#include "CommonValues.h"
BlockListWidget::BlockListWidget(const QString &kit_name, const std::vector<QString> &block_names, const std::vector<QString> &block_deses, const std::vector<std::vector<QString> > &params, const std::vector<bool> &has_returns, const std::vector<QColor> &colors)
{
    int nl = block_names.size();
    int dl = block_deses.size();
    int pl = params.size();
    int rl = has_returns.size();
    bool len_equal = nl == dl && dl == pl && pl == rl;
    if(! len_equal){
        throw "number of block's names, number of block's descriptions and number of blocks' params are not equal to each other";
    }
    if(block_names.size() == 0){
        throw "number of blocks is zero, which is unwilling to happen";
    }
    int n = block_names.size();
    int y = EDGE;
    int w = 0;
    for(int i=0;i<n;i++){
        BlockWidget* bw = nullptr;
        if(i >= colors.size()){
            bw = new BlockWidget(kit_name,block_names[i],block_deses[i],params[i],has_returns[i]);
        }
        else{
            bw = new BlockWidget(kit_name,block_names[i],block_deses[i],params[i],has_returns[i],colors[i]);
        }
        TurnOnShadowEffect(bw);
        bw->setParent(this);
        int wid = bw->x() + bw->width() + EDGE;
        if(wid > w){
            w = bw->width();
        }
        bw->move(EDGE,y);
        bw->show();
        y = bw->y() + bw->height() + SPACING_BETWEEN_BLOCKS;
        _block_widgets.push_back(bw);
    }
    int h = y - SPACING_BETWEEN_BLOCKS + EDGE;
    resize(w,h);
}
