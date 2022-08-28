#ifndef LEGOWIDGET_H
#define LEGOWIDGET_H

#include <QWidget>
#include <vector>
#include <QLabel>
#include "CommonValues.h"
class InputWidget;
class ResultReceiverSelector;
class BlockNode;
class LegoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegoWidget(const QString& kit_name, const QString& lego_name, const std::vector<QString>& params, bool has_return, QColor color = BlockDefaultColor);
    QString FetchParamsValue(const QString& param_name,bool& is_literal);
    QString FetchParamsValue(int idx, bool &is_literal);
    //如果没有接受值则返回false，res是无效值
    bool FetchResult(QString& res);
    QString KitName() const ;

    BlockNode* GetBlockNode(int idx) const;

protected slots:
    void UpdateSize();
signals:
    void ResizeWindow();
private:
    QString _kit_name;
    std::vector<QString> _param_names;
    std::vector<InputWidget*> _param_input_widgets;
    ResultReceiverSelector* _receiver;
    QLabel* _lego_name_label,*_return_label;
    enum{FONTSIZE = 8,EDGE = 1,SPACING = 1,SPACING_BETWEEN_PARAM_RETURN = 2};
};

#endif // LEGOWIDGET_H
