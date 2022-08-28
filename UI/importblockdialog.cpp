#include "importblockdialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
ImportBlockDialog::ImportBlockDialog()
    :_select_des_file(new QPushButton),_select_exe_file(new QPushButton),_comfirm(new QPushButton),
      _des_label(new QLabel),_exe_label(new QLabel),
      _vbl(new QVBoxLayout),_hbl1(new QHBoxLayout),_hbl2(new QHBoxLayout)
{
    _select_des_file->setText("Import .txt File");
    _select_exe_file->setText("Import .exe file");
    _hbl1->addWidget(_des_label,LABLE_RATIO);
    _hbl1->addWidget(_select_des_file,BUTTON_RATIO);
    _select_des_file->show();
    _hbl2->addWidget(_exe_label,LABLE_RATIO);
    _hbl2->addWidget(_select_exe_file,BUTTON_RATIO);
    _select_exe_file->show();
    _vbl->addLayout(_hbl1,1);
    _vbl->addLayout(_hbl2,1);
    _comfirm->setText("confirm");
    connect(_comfirm,&QPushButton::clicked,this,&ImportBlockDialog::WhenComfirm);
    connect(_select_des_file,&QPushButton::clicked,this,&ImportBlockDialog::SelectDesFile);
    connect(_select_exe_file,&QPushButton::clicked,this,&ImportBlockDialog::SelectExeFile);
    _vbl->addWidget(_comfirm,1);
    setLayout(_vbl);
    ChangeBKG(this,ImportBlockWidgetColor);
    ChangeBKG(_select_des_file,Qt::white);
    ChangeBKG(_select_exe_file,Qt::white);
    setFixedSize(WIDGET_WIDTH,WIDGET_HEIGHT);
    TurnOnShadowEffect(this);
}

void ImportBlockDialog::closeEvent(QCloseEvent *)
{

}
void ImportBlockDialog::showEvent(QShowEvent *){

}

void ImportBlockDialog::SelectDesFile()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("import a kit"),
            "C:/",
            tr("text files(*.txt)"));
    if(fileName.length() == 0){
        QMessageBox::warning(this,"fail","fail opening description file",QMessageBox::Cancel);
        _des_label->setText("");
    }
    else{
        _des_label->setText(fileName);
    }
}

void ImportBlockDialog::SelectExeFile()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("import a kit"),
            "C:/",
            tr("exe files(*.exe)"));
    if(fileName.length() == 0){
        QMessageBox::warning(this,"fail","fail opening .exe file",QMessageBox::Cancel);
        _exe_label->setText("");
    }
    else{
        _exe_label->setText(fileName);
    }
}

void ImportBlockDialog::WhenComfirm()
{
    QString msg = "";
    bool success = true;
    _des_file = _des_label->text();
    _exe_file = _exe_label->text();
    if(_exe_file.length() == 0){
        msg += "no .exe file is selected";
        success = false;
    }
    //Print(_exe_file);
    if(_des_file.length() == 0){
        msg += "no description file is selected";
        success = false;
    }
    if(success == false){
        int reply = QMessageBox::warning(this,"fail",msg,QMessageBox::Cancel | QMessageBox::Retry);
        if(reply != QMessageBox::Retry){
            close();
        }
    }
    else{
        emit Done();
        close();
    }
}

QString ImportBlockDialog::FetchExeFilePath() const
{
    return _exe_file;
}

QString ImportBlockDialog::FetchDesFilePath() const
{
    return _des_file;
}
