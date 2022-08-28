#include "blockkitdescription.h"
#include "blockdescription.h"
#include "controller.h"
#include "CommonValues.h"

bool CompileSuccess = true;

BlockKitDescription::BlockKitDescription(const QString &kitname, const QString &kit_des, std::vector<QString> &block_names, const std::vector<QString> &block_deses, const std::vector<std::vector<QString> > &block_params, const std::vector<bool> &block_has_returns)
    :_kit_name(kitname),_des(kit_des),_block_names(block_names),_block_deses(block_deses),_block_params(block_params),_block_has_returns(block_has_returns)
{
    int nl = block_names.size();
    int dl = block_deses.size();
    int pl = block_params.size();
    int rl = block_has_returns.size();
    int equal = nl == dl && dl == pl && pl == rl;
    if(!equal){
        throw "init BlockKitDescription fails:critical";
    }
    else{
        for(int i= 0;i<nl;i++){
            BlockDes* bs = new BlockDes{kitname,block_names[i],block_deses[i],block_params[i],block_has_returns[i]};
            _blocks.push_back(bs);
        }
    }
}

const std::vector<BlockDes*> BlockKitDescription::GetBlockDeses() const
{
    return _blocks;
}

QString BlockKitDescription::GetKitName() const
{
    return _kit_name;
}

QString BlockKitDescription::GetKitDescription() const
{
    return _des;
}

std::vector<QString> BlockKitDescription::GetBlockNameSet() const
{
    return _block_names;
}

std::vector<QString> BlockKitDescription::GetBlockDesSet() const
{
    return _block_deses;
}

std::vector<std::vector<QString> > BlockKitDescription::getBlockParamSet() const
{
    return _block_params;
}

std::vector<bool> BlockKitDescription::GetBlockReturnSet() const
{
    return _block_has_returns;
}

BlockKitDescription::~BlockKitDescription()
{
    for(int i=0;i<_blocks.size();i++){
        delete _blocks[i];
    }
    _blocks.clear();
}
