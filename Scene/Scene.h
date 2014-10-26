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
#include "Dialog.h"


//------------------------------------------------------------------------------
// Class: Scene
//------------------------------------------------------------------------------
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int x, int y, int width, int height);
    Scene(Scene&);
    ~Scene(void);

    void    Initialize(void);
    void    addItem(Card* card);

protected:
    void    mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void    mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

public slots:
    void    CreateDialog(Dialog::DialogType dialogType);

signals:
    void    SignalCardSelectionsChanged(Card*);
    void    ExecuteDeal(void);

private:
    Dialog* dialog;
};

#endif // SCENE_H
