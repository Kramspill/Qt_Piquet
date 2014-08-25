//------------------------------------------------------------------------------
// Filename: GameManager.h
// Description: Header file for GameManager.
//------------------------------------------------------------------------------

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>
#include <QPushButton>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Scene/Scene.h"
#include "View/View.h"
#include "AI/AI.h"
#include "CardManager.h"
#include "StateManager.h"
#include "ScoreManager.h"


//------------------------------------------------------------------------------
// Class: GameManager
//------------------------------------------------------------------------------
class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(void);
    GameManager(GameManager&);
    ~GameManager(void);

    void          Initialize(void);

private:
    void          ConnectSignals(void);

private slots:
    void          UpdateAI(void);

private:
    Scene*        scene;
    View*         view;
    AI*           ai;
    CardManager*  cardManager;
    StateManager* stateManager;
    ScoreManager* scoreManager;
};

#endif // GAMEMANAGER_H
