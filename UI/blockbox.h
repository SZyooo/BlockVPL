#ifndef BLOCKBOX_H
#define BLOCKBOX_H

#include <QToolBox>
#include <map>

class BlockBox : public QToolBox
{
    Q_OBJECT
public:
    BlockBox();
    //kit的名字有可能重复，因此会做必要的重新命名，返回新的名字
    QString AddKit(const QString& kit_name,
                   const QString& kit_des,
                   const std::vector<QString>& block_names,
                   const std::vector<QString>& block_deses,
                   const std::vector<std::vector<QString>>& params, const std::vector<bool> has_returns,
                   const std::vector<QColor>& colors = {});
    //void RemoveActivateKit();
private:
    std::map<QString,int> _kitname_index;
};

#endif // BLOCKBOX_H
