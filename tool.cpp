#include "tool.h"
#include<QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPalette>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
void Print(const QString& s)
{
#ifdef BLOCK_DEBUG
    qDebug() << s;
#endif
}



void TurnOnShadowEffect(QWidget *w)
{
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 0);//设置阴影距离
    effect->setColor(QColor(0,0,0,90));//设置阴影颜色
    effect->setBlurRadius(15);//设置阴影圆角
    w->setGraphicsEffect(effect);
}

void TurnOffShadowEffect(QWidget *w)
{
    w->setGraphicsEffect(nullptr);
}

QColor ChangeBKG(QWidget *w, QColor c)
{
    QPalette p = w->palette();
    QColor oColor = p.color(QPalette::Window);
    p.setColor(QPalette::Window,c);
    w->setAutoFillBackground(true);
    w->setPalette(p);
    return oColor;
}
QString verification_error = "";
bool VerifyValue(const QString &s)
{
    //Print("(tool.h)need to finish: check validity of a value");
    if(s.length() == 0){
        verification_error = "variable's name cannot be empty";
    }
    QString pattern("^[a-zA-Z][a-zA-Z0-9_]*$");
    QRegularExpression rExp(pattern);
    QRegularExpressionMatch match = rExp.match(s);
    if(match.hasMatch()){
        return true;
    }
    else{
        verification_error = "invalid variable name";
        return false;
    }
}
