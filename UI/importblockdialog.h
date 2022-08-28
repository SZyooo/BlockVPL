#ifndef IMPORTBLOCKDIALOG_H
#define IMPORTBLOCKDIALOG_H

#include <QDialog>
#include "tool.h"
#include "CommonValues.h"
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class ImportBlockDialog : public QDialog
{
    Q_OBJECT
public:
    ImportBlockDialog();
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent*);
    QString FetchExeFilePath() const;
    QString FetchDesFilePath() const;
signals:
    void Done();
private slots:
    void SelectDesFile();
    void SelectExeFile();
    void WhenComfirm();

private:
    QPushButton* _select_des_file,*_select_exe_file,*_comfirm;
    QLabel * _des_label,* _exe_label;
    QVBoxLayout* _vbl;
    QHBoxLayout* _hbl1,*_hbl2;
    enum{WIDGET_HEIGHT = 100,WIDGET_WIDTH = 400};
    enum{LABLE_RATIO = 8,BUTTON_RATIO = 2};
    QString _exe_file,_des_file;
};

#endif // IMPORTBLOCKDIALOG_H
