//------------------------------------------------------------------------------
// Filename: Scene.h
// Description: Header file for Scene.
//------------------------------------------------------------------------------

#ifndef SCENE_H
#define SCENE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: Scene
//------------------------------------------------------------------------------
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int x, int y, int width, int height);

    void addItem(Card* card);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

signals:
    void SignalCardSelectionsChanged(Card*);
};

#endif // SCENE_H
