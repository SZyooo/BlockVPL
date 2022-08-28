#ifndef SPECIFYCOMPILORDIRWIDGET_H
#define SPECIFYCOMPILORDIRWIDGET_H

#include <QWidget>


class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class SpecifyCompilorDirWidget : public QWidget
{
    Q_OBJECT
public:
    SpecifyCompilorDirWidget();
signals:
private slots:
    void WhenClickOpenDialog();
private:
    QPushButton* _open_dialog,*_close;
    QLabel* _dir_label;
    QHBoxLayout* _hbl;
    QVBoxLayout*_vbl;
    enum{LABEL_RATIO = 9,BUTTON_RATIO = 2,WIDTH = 400,HEIGHT = 60};
};

#endif // SPECIFYCOMPILORDIRWIDGET_H
