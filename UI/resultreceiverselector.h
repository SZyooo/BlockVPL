#ifndef RESULTRECEIVERSELECTOR_H
#define RESULTRECEIVERSELECTOR_H

#include <QComboBox>
#include <vector>

class ResultReceiverSelector : public QComboBox
{
    Q_OBJECT
public:
    ResultReceiverSelector(const std::vector<QString>& variables);
    ResultReceiverSelector();
    void UpdateVariables();
    QString FetchCurrentVariable() const;
protected:
    void UpdateView(const std::vector<QString> &variables);
protected slots:
    void Select(int idx);
private:
    enum{FONT_SIZE = 15,EDGE = 3,DROP_ICON_SPACE = 20};
signals:

};

#endif // RESULTRECEIVERSELECTOR_H
