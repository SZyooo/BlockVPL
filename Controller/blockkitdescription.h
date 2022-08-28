#ifndef BLOCKKITDESCRIPTION_H
#define BLOCKKITDESCRIPTION_H

#include <QObject>
#include <vector>
struct BlockDes;
class BlockKitDescription : public QObject
{
    Q_OBJECT
public:
    BlockKitDescription(const QString& kitname,const QString& kit_des,std::vector<QString>& block_names,
                        const std::vector<QString>& block_deses,const std::vector<std::vector<QString>>& block_params,
                        const std::vector<bool>& block_has_returns);
    inline const std::vector<struct BlockDes*> GetBlockDeses() const;
    QString GetKitName()const;
    QString GetKitDescription() const;
    std::vector<QString> GetBlockNameSet()const;
    std::vector<QString> GetBlockDesSet()const;
    std::vector<std::vector<QString>> getBlockParamSet() const;
    std::vector<bool> GetBlockReturnSet()const;
    ~BlockKitDescription();

private:
    QString _kit_name;
    QString _des;
    std::vector<QString> _block_names;
    std::vector<QString> _block_deses;
    std::vector<std::vector<QString>> _block_params;
    std::vector<bool> _block_has_returns;
    std::vector<struct BlockDes*> _blocks;
};

#endif // BLOCKKITDESCRIPTION_H
