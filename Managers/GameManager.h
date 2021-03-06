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


//------------------------------------------------------------------------------
// System Header Files
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>


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
    void          Destroy(void);

private:
    void          InitGlobalState(void);
    void          DestroyGlobalState(void);
    void          ConnectSignals(void);
    void          ResetGame(bool newGame = false);
    void          ConnectPlayer(void);

private slots:
    void          ExecuteElderSelect(void);
    void          ExecuteDeal(void);
    void          ExecuteExchange(void);
    void          AnnounceDeclaration(State phase, PlayerNum player);
    void          DeclareSelection(State phase, PlayerNum player);
    void          ResolveResponse(State phase, PlayerNum player);
    void          PlayTrick(PlayerNum player);
    void          ExecuteSummary(void);
    void          NewGame(void);
    void          TestAi(void);

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
