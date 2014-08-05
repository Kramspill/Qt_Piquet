#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene* scene);

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // VIEW_H
