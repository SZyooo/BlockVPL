#include "controller.h"
#include "tool.h"
#include "blockkitdescription.h"
#include "descriptionfileparser.h"
Controller *Controller::GetInstance()
{
    return Instance;
}

void Controller::Warning(const QString &s)
{
    Print(QString("Warning:") + s + "(ζεΎιε)");
}

BlockKitDescription *Controller::LoadBlock(const QString &des_file)
{
    return DescriptionFileParser::Parse(des_file);
}

Controller::Controller()
{

}
Controller* Controller::Instance = new Controller;
