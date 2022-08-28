#include "blockwidget.h"
#include <QFont>
#include <QFontMetrics>
#include "tool.h"
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include "blockmimedata.h"
BlockWidget::BlockWidget(const QString &kit_name, const QString &block_name, const QString &des, const std::vector<QString> &params, bool has_return, const QColor &bkg)
    :_kit(kit_name),_name(block_name),_des(des),_params(params),_has_return(has_return),_bkg(bkg),_left_pressed(false)
{
    ChangeBKG(this,bkg);
    setMouseTracking(true);
    int wid = 0;
    QFont font;
    font.setPointSize(FONTSIZE);
    QLabel* name_label = new QLabel(this);
    name_label->setFont(font);
    name_label->setText(block_name);
    name_label->adjustSize();
    name_label->move(EDGE,EDGE);
    wid = name_label->x() + name_label->width() + EDGE;
    int x = name_label->width() + name_label->x() + SPACING_BETWEEN_NAME_PARAM;
    int mh = name_label->height();
    for(int i=0;i<params.size();i++){
        QLabel* pLabel = new QLabel(this);
        pLabel->setFont(font);
        pLabel->setText(params[i]);
        pLabel->adjustSize();
        pLabel->move(x,EDGE);
        if(mh < pLabel->height()){
            mh = pLabel->height();
        }
        _param_labels.push_back(pLabel);
        x = pLabel->x() + pLabel->width() + SPACING;
        wid = x;
    }
    wid = wid - SPACING + EDGE;
    mh += 2*EDGE;
    name_label->move(name_label->x(),mh/2 - name_label->height()/2);

    for(int i=0;i<_param_labels.size();i++){
        int x = _param_labels[i]->x();
        int y = mh/2 - _param_labels[i]->height()/2;
        _param_labels[i]->move(x,y);
    }
    resize(wid,mh);
    setToolTip(des + (has_return?QString("\nHas return"):QString("\nNo return")));
}

void BlockWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor("#778899"),1));//设置画笔形式
    for(int i=0;i<_param_labels.size();i++){
        int x = _param_labels[i]->x();
        int y = _param_labels[i]->y();
        int w = _param_labels[i]->width();
        int h = _param_labels[i]->height();
        painter.drawRect(x,y,w,h);//画矩形
    }
}

void BlockWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        _left_pressed = true;
        int x = static_cast<int>(event->position().x());
        int y = static_cast<int>(event->position().y());
        _last_press_pos = QPoint(x,y);
    }
    else{
        _left_pressed = false;
    }
}

void BlockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(_left_pressed){
        int x = static_cast<int>(event->position().x());
        int y = static_cast<int>(event->position().y());
        QPoint now_pos(x,y);
        float move_dis = (now_pos - _last_press_pos).manhattanLength();
        if(move_dis > DRAG_THRESHOLD){
            QDrag* drag = new QDrag(this);
            drag->setMimeData(new BlockMimeData(_kit,_name,_params,_has_return));
            drag->exec();
        }
    }
}

void BlockWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _left_pressed = true;
}
