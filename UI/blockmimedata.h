#ifndef BLOCKMIMEDATA_H
#define BLOCKMIMEDATA_H

#include <QMimeData>
#include <vector>
class BlockMimeData : public QMimeData
{
    Q_OBJECT
public:
    BlockMimeData(const QString& kit_name,const QString& block_name,const std::vector<QString>& params,bool has_return);
    QString GetKitName() const;
    QString GetBlockName() const;
    std::vector<QString> GetParams()const;
    bool GetHasReturn()const;
private:
    QString _kit_name;
    QString _block_name;
    std::vector<QString> _params;
    bool _has_return;
};

#endif // BLOCKMIMEDATA_H
