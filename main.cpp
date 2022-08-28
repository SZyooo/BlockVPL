#include "mainwindow.h"

#include <QApplication>
//#include <UI/inputwidget.h>
//#include <UI/legowidget.h>
#include "UI/editwidget.h"
#include "UI/loopsegmentwidget.h"
#include "UI/segmentcontainerwidget.h"
#include "UI/loopsegmentscrollarea.h"
#include "UI/segmentcontainerscrollarea.h"
#include "UI/variablelistscrollarea.h"
#include "UI/blocklistscrollarea.h"
#include "tool.h"
#include "UI/legowidget.h"
#include "UI/editorwindow.h"
#include "Controller/controller.h"
#include "Controller/blockkitdescription.h"
#include "Controller/blockdescription.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    EditorWindow ew;
    try{
        //SegmentContainerScrollarea* scs = new SegmentContainerScrollarea;
        //LoopSegmentScrollarea* lss = new LoopSegmentScrollarea;
        //lss->show();
        //    LoopSegmentWidget* lsw = new LoopSegmentWidget;
        //    lsw->show();
        //VariableListScrollarea* vls = new VariableListScrollarea;
//        std::vector<QString> name{"add","sub"};
//        std::vector<QString> des{"addition","subtraction"};
//        std::vector<QString> param1{"P1","Parameter2"};
//        std::vector<QString> param2{"P1","p2"};
//        std::vector<bool> has_returns{true,true};
//        std::vector<std::vector<QString>> params{param1,param2};
//        BlockListScrollarea* bls = new BlockListScrollarea("basic kit",name,des,params,has_returns);
        //LegoWidget* lw = new LegoWidget("basic","add",{"p1","p2"},true,QColor("#FAFAD2"));
        //lw->show();
//        EditWidget* ew = new EditWidget;
//        ew->AddLego("basic kit","add",{"p1","p2"},true);
//        ew->AddLego("basic kit","sub",{"p1","p2"},true);
//        w.setCentralWidget(ew);
//        w.show();
        ew.setWindowState(Qt::WindowMaximized);
        ew.show();
    }
    catch(const char* s){
        Print(s);
    }
    //lss->show();
    return a.exec();
}
