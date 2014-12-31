//------------------------------------------------------------------------------
// Filename: View.cpp
// Description: Represents a view of the scene.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "View.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
View::View(QGraphicsScene* scene) :
    QGraphicsView(scene)
{
    setBackgroundBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));
    setMinimumSize(1280, 720);
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
View::View(View&) :
    QGraphicsView()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
View::~View(void)
{
}


//------------------------------------------------------------------------------
// resizeEvent - Override of QGraphicsView::resizeEvent.
//------------------------------------------------------------------------------
void View::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
