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
#include <QLabel>


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
    enum PhaseType
    {
        DEAL,
        EXCHANGE,
        DECLARATION,
        TRICK
    };

public:
    Scene(int x, int y, int width, int height);
    Scene(Scene&);
    ~Scene(void);

    void         Initialize(void);

    QPointF      GetCenterPos(void);

    void         SetTitle(const QString& newTitle);
    void         SetText(const QString& newText);

protected:
    void         mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void         mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

private:
    void         ConnectSignals(void);

public slots:
    void         CreateDialog(Dialog::DialogType dialogType);
    void         SetUI(PhaseType phase);

signals:
    void         SignalCardSelectionsChanged(Card*);
    void         ExecuteDeal(void);

private:
    QPushButton* primaryAction;
    QPushButton* secondaryAction;
    QLabel*      title;
    QLabel*      text;
    Dialog*      dialog;
    int          xPos;
    int          yPos;
    int          width;
    int          height;
};

#endif // SCENE_H
