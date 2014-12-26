//------------------------------------------------------------------------------
// Filename: View.h
// Description: Header file for View.
//------------------------------------------------------------------------------

#ifndef VIEW_H
#define VIEW_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsView>


//------------------------------------------------------------------------------
// Class: View
//------------------------------------------------------------------------------
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QGraphicsScene* scene);
    View(View&);
    ~View(void);

protected:
    void resizeEvent(QResizeEvent* event);

signals:
    void RepositionObjects(void);
};

#endif // VIEW_H
