#ifndef COMMONVALUES_H
#define COMMONVALUES_H
#include <QColor>
#include <QHash>
enum Condition{EQ,GRT_EQ,LES_EQ,NEQ,GRT,LES};
extern const int EditWidgetWidth;// = 300;
extern const int EditWidgetHeight;// = 600;

extern const QColor LoopAreaBKG;// = QColor("#c1e4fb");
extern const QColor EditWidgetBKG;// = QColor(255,250,240);
extern const QColor BlockDefaultColor;// = QColor("#FFF0F5");
extern const QColor BlockListColor;// = QColor("#EEEED1");
extern const QColor VariableColor;// = QColor("#c5f5b3");
extern const QColor VariableListCOlor;// = QColor("#ecb5f2");
extern const QColor EditRegionBeingChosen;// = QColor("#fedcdc");
extern const QColor ImportBlockWidgetColor;// = QColor("#b6dcac");
extern const QColor SpecifyCompilorWidgetColor;

extern bool CompileSuccess;

extern QHash<QString,QString> KitName_ExePath;
extern const QString OutputFilePath;// = "./output.txt";
extern QString GppDirectory;

extern const QString ComposeCPPDirectory;
extern const QString TargetDirectory;
extern const QString TargetExeFile;


#endif // COMMONVALUES_H
