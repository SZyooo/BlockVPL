#include "descriptionfileparser.h"
#include <QFile>
#include "controller.h"
#include "blockkitdescription.h"
#include "tool.h"
BlockKitDescription* DescriptionFileParser::Parse(const QString &file_name)
{
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false){
        Controller::GetInstance()->Warning("description file cannot open!");
        return nullptr;
    }
    QString kit_name = QString(file.readLine());
    QString kit_des(file.readLine());
    std::vector<QString> block_names,block_deses;
    std::vector<std::vector<QString>> block_params;
    std::vector<bool> block_returns;
    bool success = true;
    QTextStream stream(&file);
    while(!stream.atEnd()){
        QString line = stream.readLine();
        Print(line);
        QStringList list = line.split(QLatin1Char(';'));
        if(list.size()!=4){
            Controller::GetInstance()->Warning("description file format is wrong!");
            success = false;
            break;
        }
        block_names.push_back(list.at(0));
        block_deses.push_back(list.at(1));
        QStringList params = list.at(2).split(QLatin1Char(','));
        std::vector<QString> v_param(params.begin(),params.end());
        block_params.push_back(v_param);
        bool has_return = list.at(3) == "YES";
        block_returns.push_back(has_return);
    }
    if(success){
        return new BlockKitDescription(kit_name,kit_des,block_names,block_deses,block_params,block_returns);
        file.close();
    }
    else{
        Controller::GetInstance()->Warning("load fail!");
        return nullptr;
    }
}
