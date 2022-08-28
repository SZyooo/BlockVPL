#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include <vector>
#include "CommonValues.h"
class QLabel;
//在block list中的block
class BlockWidget : public QWidget
{
    Q_OBJECT
public:
    BlockWidget(const QString& kit_name,
                const QString& block_name,
                const QString& des,
                const std::vector<QString>& params,
                bool has_return,
                const QColor& bkg = BlockDefaultColor);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    enum{FONTSIZE = 10,EDGE = 5,SPACING = 2,SPACING_BETWEEN_NAME_PARAM = 5,DRAG_THRESHOLD = 10};
    QString _kit,_name,_des;
    QColor _bkg;
    bool _has_return;
    std::vector<QString> _params;
    std::vector<QLabel*> _param_labels;

    bool _left_pressed;
    QPoint _last_press_pos;
};

#endif // BLOCKWIDGET_H
