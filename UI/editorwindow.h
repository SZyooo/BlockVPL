#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QHBoxLayout;
class BlockBox;
class VariableListScrollarea;
class SegmentContainerScrollarea;
class ImportBlockDialog;
class SpecifyCompilorDirWidget;
class QTextEdit;
class EditorWindow : public QMainWindow
{
    Q_OBJECT
public:
    EditorWindow();
private:
    QWidget* _central_widget;
    enum{BLOCKBOX = 2,EDIT_REGION = 6,VARIABLE_LIST = 2};
    BlockBox* _block_box;
    SegmentContainerScrollarea* _edit_region;
    VariableListScrollarea* _variable_list;
    ImportBlockDialog* _import_dialog;
    QHBoxLayout* _layout;
    SpecifyCompilorDirWidget* _specify_compiler_dir_widget;

    //编译运行之后信息输出窗口
    QTextEdit* _print_window;

private slots:
    void WhenClickBuild(bool checked);
    void WhenClickImport(bool checked);
    void WhenFileChosen();
    void WhenSpecifyCompilerDir(bool checked);
signals:

};

#endif // EDITORWINDOW_H
