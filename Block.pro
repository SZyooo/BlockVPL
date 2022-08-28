QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Use Precompiled headers (PCH)
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
# HEADERS += stable.h #这句话是可有可无的，建议加上



SOURCES += \
    CommonValues.cpp \
    Controller/blockdescription.cpp \
    Controller/blockkitdescription.cpp \
    Controller/compileinfostack.cpp \
    Controller/controller.cpp \
    Controller/descriptionfileparser.cpp \
    UI/addvariabledialog.cpp \
    UI/adjustwidget.cpp \
    UI/blockbox.cpp \
    UI/blocklistscrollarea.cpp \
    UI/blocklistwidget.cpp \
    UI/blockmimedata.cpp \
    UI/blockwidget.cpp \
    UI/conditionwidget.cpp \
    UI/editorwindow.cpp \
    UI/editscrollarea.cpp \
    UI/editwidget.cpp \
    UI/editwidgetswitchbuttonset.cpp \
    UI/importblockdialog.cpp \
    UI/inputwidget.cpp \
    UI/legowidget.cpp \
    UI/loopsegmentscrollarea.cpp \
    UI/loopsegmentwidget.cpp \
    UI/resultreceiverselector.cpp \
    UI/segmentcontainerscrollarea.cpp \
    UI/segmentcontainerwidget.cpp \
    UI/specifycompilordirwidget.cpp \
    UI/variablelistscrollarea.cpp \
    UI/variablelistwidget.cpp \
    UI/variablewidget.cpp \
    VRE/Node.cpp \
    main.cpp \
    mainwindow.cpp \
    tool.cpp

HEADERS += \
    CommonValues.h \
    Controller/blockdescription.h \
    Controller/blockkitdescription.h \
    Controller/compileinfostack.h \
    Controller/controller.h \
    Controller/descriptionfileparser.h \
    UI/addvariabledialog.h \
    UI/adjustwidget.h \
    UI/blockbox.h \
    UI/blocklistscrollarea.h \
    UI/blocklistwidget.h \
    UI/blockmimedata.h \
    UI/blockwidget.h \
    UI/conditionwidget.h \
    UI/editorwindow.h \
    UI/editscrollarea.h \
    UI/editwidget.h \
    UI/editwidgetswitchbuttonset.h \
    UI/importblockdialog.h \
    UI/inputwidget.h \
    UI/legowidget.h \
    UI/loopsegmentscrollarea.h \
    UI/loopsegmentwidget.h \
    UI/resultreceiverselector.h \
    UI/segmentcontainerscrollarea.h \
    UI/segmentcontainerwidget.h \
    UI/specifycompilordirwidget.h \
    UI/variablelistscrollarea.h \
    UI/variablelistwidget.h \
    UI/variablewidget.h \
    VRE/Node.h \
    mainwindow.h \
    stable.h \
    tool.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
