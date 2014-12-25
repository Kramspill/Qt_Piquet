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
#include <QApplication>
#include <QDesktopWidget>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"
#include "Scene/Scene.h"
#include "View/View.h"
#include "Players/Player.h"
#include "Players/AI.h"
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
    void          ExecuteDeal(void);
    void          ExecuteExchange(void);
    void          AnnounceDeclaration(State phase, PlayerNum player);
    void          DeclareSelection(State phase, PlayerNum player);
    void          ResolveResponse(State phase, PlayerNum player);
    void          PlayTrick(PlayerNum player);

    void          RequestCardTransfer(CardArray::Type src,
                                      CardArray::Type dest,
                                      int numCards);
    void          UpdateAI(PlayerNum player);

private:
    Scene*        scene;
    View*         view;
    Player*       player1;
    Player*       player2;
    CardManager*  cardManager;
    StateManager* stateManager;
    ScoreManager* scoreManager;
};

#endif // GAMEMANAGER_H
