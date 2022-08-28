#ifndef ADJUSTWIDGET_H
#define ADJUSTWIDGET_H

#include <QWidget>

class QPushButton;
class AdjustWidget : public QWidget
{
    Q_OBJECT
public:
    AdjustWidget();
private slots:
    void PressUp();
    void PressDown();
    void PressDelete();
signals:
    void Up();
    void Down();
    void Delete();
private:
    enum{BTN_SIZE = 25,EDGE = 1};
    QPushButton *_up,*_down,*_remove;
};

#endif // ADJUSTWIDGET_H
