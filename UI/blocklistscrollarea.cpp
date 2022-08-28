#include "blocklistscrollarea.h"
#include "blocklistwidget.h"
#include "CommonValues.h"
#include "tool.h"
BlockListScrollarea::BlockListScrollarea(const QString &kit_name, const std::vector<QString> &block_names, const std::vector<QString> &block_deses, const std::vector<std::vector<QString> > &params, const std::vector<bool> &has_returns, const std::vector<QColor> &colors)
    :_inner_widget(new BlockListWidget(kit_name,block_names,block_deses,params,has_returns,colors))
{
    setWidget(_inner_widget);
    ChangeBKG(this,BlockListColor);
}
