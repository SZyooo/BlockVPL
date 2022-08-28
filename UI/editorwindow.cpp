#include "editorwindow.h"
#include "blockbox.h"
#include "segmentcontainerscrollarea.h"
#include "variablelistscrollarea.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include "tool.h"
#include "Controller/controller.h"
#include "Controller/blockkitdescription.h"
#include <QFileDialog>
#include <vector>
#include <Controller/blockdescription.h>
#include "importblockdialog.h"
#include "CommonValues.h"
#include <fstream>
#include "VRE/Node.h"
#include "specifycompilordirwidget.h"
#include <QProcess>
#include <QStringList>
#include "Controller/compileinfostack.h"
QHash<QString,QString> KitName_ExePath;

EditorWindow::EditorWindow()
    :_block_box(new BlockBox),
      _edit_region(new SegmentContainerScrollarea),
      _variable_list(new VariableListScrollarea),
      _central_widget(new QWidget),
      _layout(new QHBoxLayout),
      _import_dialog(new ImportBlockDialog),
      _specify_compiler_dir_widget(new SpecifyCompilorDirWidget),
      _print_window(new QTextEdit)

{
    setCentralWidget(_central_widget);
    _central_widget->setLayout(_layout);
    _layout->addWidget(_block_box,BLOCKBOX);
    _layout->addWidget(_edit_region,EDIT_REGION);
    _layout->addWidget(_variable_list,VARIABLE_LIST);

    _import_dialog->setParent(this);
    connect(_import_dialog,&ImportBlockDialog::Done,this,&EditorWindow::WhenFileChosen);
    _import_dialog->close();

    _print_window->close();

    _specify_compiler_dir_widget->setParent(this);
    _specify_compiler_dir_widget->close();
    int x = width()/2 - _specify_compiler_dir_widget->width()/2;
    int y = height()/2 - _specify_compiler_dir_widget->height()/2;
    _specify_compiler_dir_widget->move(x,y);

    _block_box->show();
    _edit_region->show();
    _variable_list->show();

    QMenuBar* menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    QMenu* compile = new QMenu("Build",menuBar);
    QMenu* import = new QMenu("Blocks",menuBar);
    QAction* build = new QAction("build");
    //QAction* specify_compiler_dir = new QAction("Compiler Directory");
    QAction* impt= new QAction("import block kit");
    compile->addAction(build);
    //compile->addAction(specify_compiler_dir);
    import->addAction(impt);


    connect(build,&QAction::triggered,this,&EditorWindow::WhenClickBuild);
    connect(impt,&QAction::triggered,this,&EditorWindow::WhenClickImport);
    //connect(specify_compiler_dir,&QAction::triggered,this,&EditorWindow::WhenSpecifyCompilerDir);

    menuBar->addMenu(compile);
    menuBar->addMenu(import);
}

void EditorWindow::WhenClickBuild(bool checked)
{
//    if(GppDirectory.isEmpty()){
//        QMessageBox::information(this,"no compiler","please first select your compiler",QMessageBox::Yes);
//        return;
//    }
    //Print("wait to finish: EditorWindow::WhenClickBuild");
    PageNode* writer = new PageNode(_edit_region->GetProgramNode(_variable_list->FetchAllVariableNamesAndValues()));
    std::ofstream f(ComposeCPPDirectory.toStdString().c_str());
    writer->PrintToCPPFile(f);
    delete writer;
    QString target = TargetDirectory + "/result.exe";
    QProcess program;
    //g++.exe E:/BlockShell/CppFilePrint/result.cpp -o E:/BlockShell/CppFilePrint/result
    QString compiler = "g++.exe";
    QStringList args;
    args.append("-o");
    args.append(target);
    args.append(ComposeCPPDirectory);

#ifdef BLOCK_DEBUG
    QString cmd = compiler+" " + args[0] + " " + args[1] + " " + args[2];
    Print(cmd);
#endif
    bool success = true;
    while(true){
        int res = program.execute(compiler,args);
        if(res == -1 || res == -2){
            int reply = QMessageBox::warning(this,"fail","compiliation fail",QMessageBox::Cancel|QMessageBox::Retry);
            if(reply != QMessageBox::Retry){
                success = false;
                break;
            }
        }else{
            success = true;
            break;
        }
    }
    if(success){
//        QString output_program = target;
//        QStringList args;
//        QProcess exe;
//        exe.start(output_program,args);
        //运行程序
        QString file = "file:///" + target;
        QDesktopServices::openUrl(QUrl(file, QUrl::TolerantMode));
        //高亮显示程序
        QStringList param;
        param<<QLatin1String("/select,");
        param<<QDir::toNativeSeparators(file);
        QProcess::startDetached("explorer",param);
        _print_window->setText("");
        CompileInfoStack* info_stack = CompileInfoStack::GetInstance();
        while(info_stack->IsMsgEmpty()==false){
            _print_window->append(info_stack->TopMsg());
            info_stack->PopMsg();
        }
        _print_window->setTextColor(QColor("#faf20f"));
        while(info_stack->IsWarningEmpty()==false){
            _print_window->append(info_stack->TopWarning());
            info_stack->PopWarning();
        }
        _print_window->setTextColor(QColor("#ee3f55"));
        while(info_stack->IsErrorEmpty()==false){
            _print_window->append(info_stack->TopError());
            info_stack->PopError();
        }
        _print_window->setTextColor(Qt::black);
        _print_window->show();
    }
}

void EditorWindow::WhenClickImport(bool checked)
{
    int x = width()/2 - _import_dialog->width()/2;
    int y = height()/2 - _import_dialog->height()/2;
    _import_dialog->move(x,y);
    _import_dialog->exec();
}

void EditorWindow::WhenFileChosen()
{
    QString exe = _import_dialog->FetchExeFilePath();
    QString des = _import_dialog->FetchDesFilePath();
    Print(exe + " " + des);
    BlockKitDescription* bd = Controller::GetInstance()->LoadBlock(des);
    if(bd == nullptr){
        QMessageBox::warning(this,"fail","fail to load block",QMessageBox::Ok);
        return;
    }
    //const std::vector<struct BlockDes*> blocks = bd->GetBlockDeses();
    QString kit_name = bd->GetKitName();
    QString kit_des = bd->GetKitDescription();
    QString _new_kit_name =
            _block_box->AddKit(kit_name,kit_des,bd->GetBlockNameSet(),
                               bd->GetBlockDesSet(),bd->getBlockParamSet(),
                               bd->GetBlockReturnSet());
    //QString msg("wait to do: tackle new kit name");
    //Print(msg);
    KitName_ExePath.insert(_new_kit_name,exe);
    delete bd;
    bd = nullptr;
}

void EditorWindow::WhenSpecifyCompilerDir(bool checked)
{
    Print("specifying");
    _specify_compiler_dir_widget->show();
}
