#include "specifycompilordirwidget.h"

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include "CommonValues.h"
#include "tool.h"
#include <QVBoxLayout>
SpecifyCompilorDirWidget::SpecifyCompilorDirWidget()
    :_dir_label(new QLabel),_open_dialog(new QPushButton),_close(new QPushButton),
      _hbl(new QHBoxLayout),_vbl(new QVBoxLayout)
{
    setWindowTitle("please specify your MinGW compiler directory");
    _dir_label->setText("");
    _open_dialog->setText("...");
    _close->setText("quit");
    _vbl->addWidget(_open_dialog,1);
    _vbl->addWidget(_close,1);
    _hbl->addWidget(_dir_label,LABEL_RATIO);
    _hbl->addLayout(_vbl,BUTTON_RATIO);
    _dir_label->show();
    _open_dialog->show();
    _close->show();
    setLayout(_hbl);
    ChangeBKG(this,SpecifyCompilorWidgetColor);
    TurnOnShadowEffect(this);
    connect(_open_dialog,&QPushButton::clicked,this,&SpecifyCompilorDirWidget::WhenClickOpenDialog);
    connect(_close,&QPushButton::clicked,[this](){close();});
    setFixedSize(WIDTH,HEIGHT);
}

void SpecifyCompilorDirWidget::WhenClickOpenDialog()
{
    QString directory = QFileDialog::getExistingDirectory(this,"select a dirctory","./");
    if(directory.isEmpty() == false){
        directory += "/";
        QFileInfo info(directory + "g++.exe");
        if(info.isFile() == false){
            int reply = QMessageBox::warning(this,"Error","cannot find g++ compiler here",QMessageBox::Cancel | QMessageBox::Retry);
            if(reply != QMessageBox::Retry){
                close();
                return;
            }
        }
        else{
            _dir_label->setText(directory);
            GppDirectory = directory;
        }
    }
}
