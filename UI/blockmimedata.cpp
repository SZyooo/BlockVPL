#include "blockmimedata.h"

BlockMimeData::BlockMimeData(const QString &kit_name, const QString &block_name, const std::vector<QString> &params, bool has_return)
    :_kit_name(kit_name),_block_name(block_name),_params(params),_has_return(has_return)
{

}

QString BlockMimeData::GetKitName() const
{
    return this->_kit_name;
}

QString BlockMimeData::GetBlockName() const
{
    return this->_block_name;
}

std::vector<QString> BlockMimeData::GetParams() const
{
    return this->_params;
}

bool BlockMimeData::GetHasReturn() const
{
    return this->_has_return;
}

