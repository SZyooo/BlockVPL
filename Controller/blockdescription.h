#ifndef BLOCKDESCRIPTION_H
#define BLOCKDESCRIPTION_H

#include <QString>
#include <vector>
struct BlockDes
{
    QString kit,name,des;
    std::vector<QString> params;
    bool has_return;
};

#endif // BLOCKDESCRIPTION_H
