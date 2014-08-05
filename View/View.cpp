#include "View.h"

View::View(QGraphicsScene* scene) :
    QGraphicsView(scene)
{
}

void View::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
