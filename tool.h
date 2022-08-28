#ifndef TOOL_H
#define TOOL_H

#define BLOCK_DEBUG
#include<QString>
#include <QWidget>
#include <QColor>
void Print(const QString &s);
void TurnOnShadowEffect(QWidget * w);
void TurnOffShadowEffect(QWidget* w);
QColor ChangeBKG(QWidget* w, QColor c);
bool VerifyValue(const QString& s);
extern QString verification_error;



#endif // TOOL_H
