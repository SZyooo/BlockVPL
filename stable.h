
// #ifndef STABLE_H //Qt官方例子没有定义这个条件编译
// #define STABLE_H

// Add C includes here
#include <iostream>

#if defined __cplusplus
// Add C++ includes here
#include <vector>

// Qt includes
#include <QApplication>
// #include <QtCore> //请谨慎包含
// #include <QtGui>  //请谨慎包含
#include <QObject>
#include <qglobal.h>
#include <QDir>
#include <QIntValidator>
#include <QToolTip>
#include <QDebug>
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QThread>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneWheelEvent>

// Other

#endif //__cplusplus
// #endif // STABLE_H

