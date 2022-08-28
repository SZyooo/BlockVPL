#ifndef BLOCKLISTWIDGET_H
#define BLOCKLISTWIDGET_H

#include <QWidget>
#include <vector>
class BlockWidget;
class BlockListWidget : public QWidget
{
    Q_OBJECT
public:
    BlockListWidget(const QString& kit_name,
                    const std::vector<QString>& block_names,
                    const std::vector<QString>& block_deses,
                    const std::vector<std::vector<QString>>& params,
                    const std::vector<bool>& has_returns,
                    const std::vector<QColor>& colors = {});

signals:
private:
    enum{EDGE = 2,SPACING_BETWEEN_BLOCKS = 3};
    std::vector<BlockWidget*> _block_widgets;
};

#endif // BLOCKLISTWIDGET_H
