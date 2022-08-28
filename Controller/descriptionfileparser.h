#ifndef DESCRIPTIONFILEPARSER_H
#define DESCRIPTIONFILEPARSER_H

#include <QObject>
class BlockKitDescription;
class DescriptionFileParser : public QObject
{
    Q_OBJECT
public:
    static BlockKitDescription *Parse(const QString& file_name);
signals:

};

#endif // DESCRIPTIONFILEPARSER_H
