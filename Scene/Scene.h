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
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsGridLayout>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/Card.h"
#include "Layouts/CardLayout.h"
#include "Layouts/InputDialog.h"
#include "Layouts/ScoreDialog.h"
#include "Dialog.h"


//------------------------------------------------------------------------------
// Class: Scene
//------------------------------------------------------------------------------
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Layout
    {
        MAIN,
        PLAYER,
        CPU,
        TALON,
        PLAYING,
        INPUT,
        SCORE
    };

public:
    Scene(void);
    Scene(Scene&);
    ~Scene(void);

    void                 Initialize(void);

    void                 AddLayout(Layout layout, CardLayout* cardLayout,
                                   int row, int column);
    QGraphicsGridLayout* GetLayout(Layout layout);

protected:
    void                 mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void                 mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

private:
    void                 PositionLayouts(void);
    void                 ConnectSignals(void);

public slots:
    void                 CreateDialog(Dialog::DialogType dialogType);

signals:
    void                 SignalCardSelectionsChanged(Card*);
    void                 ExecuteDeal(void);
    void                 ExecutePlayerDiscard(void);

private:
    QGraphicsWidget*     container;
    QGraphicsGridLayout* mainLayout;
    QGraphicsGridLayout* playerCardArea;
    QGraphicsGridLayout* cpuCardArea;
    QGraphicsGridLayout* talonArea;
    QGraphicsGridLayout* playingArea;
    InputDialog*         inputDialog;
    ScoreDialog*         scoreDialog;

    Dialog*              dialog;
};

#endif // SCENE_H
