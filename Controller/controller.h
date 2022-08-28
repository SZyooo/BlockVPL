#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class BlockKitDescription;
class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* GetInstance();
    void Warning(const QString& s);
    BlockKitDescription* LoadBlock(const QString& des_file);
private:
    Controller();
    static Controller* Instance;

signals:

};

#endif // CONTROLLER_H
