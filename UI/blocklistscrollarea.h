#ifndef BLOCKLISTSCROLLAREA_H
#define BLOCKLISTSCROLLAREA_H

#include <QScrollArea>

class BlockListWidget;
class BlockListScrollarea : public QScrollArea
{
    Q_OBJECT
public:
    BlockListScrollarea(const QString& kit_name,
                        const std::vector<QString>& block_names,
                        const std::vector<QString>& block_deses,
                        const std::vector<std::vector<QString>>& params,
                        const std::vector<bool>& has_returns,
                        const std::vector<QColor>& colors = {});
private:
    BlockListWidget* _inner_widget;
};

#endif // BLOCKLISTSCROLLAREA_H
