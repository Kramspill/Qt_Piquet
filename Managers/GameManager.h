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
#include <QApplication>
#include <QDesktopWidget>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Scene/Scene.h"
#include "View/View.h"
#include "Players/AI.h"
#include "Players/Player.h"
#include "CardManager.h"
#include "StateManager.h"
#include "ScoreManager.h"
#include "State/GlobalStateInfo.h"

// TEST //
#include "Scene/Dialog.h"
// ==== //


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
    /* OLD CODE
    void          RequestCardTransfer(CardArray::CardArrayType src,
                                      CardArray::CardArrayType dest,
                                      int  numOfCards,
                                      bool transferSelectedCards);
    void          RequestACardTransfer(CardArray::CardArrayType src,
                                       CardArray::CardArrayType dest,
                                       Card*card);
    void          DeclareSelection(CardArray::SelectionType phase);
    void          SelectAIAction(AI::AIAction action);
    void          UpdateAI(void);

    void          SetUI(Scene::PhaseType phase);

    void          DeclarePoint(void);
    void          DeclareSequence(void);
    void          DeclareSet(void);
    void          SkipDeclaration(void); // TODO;
    void          SkipPoint(void);
    void          SkipSequence(void);
    void          SkipSet(void);
    */

    // NEW CODE //
    void          ExecuteDeal(void);
    void          ExecuteExchange(void);
    void          AnnounceDeclaration(State phase, PlayerNum player);
    void          DeclareSelection(State phase, PlayerNum player);
    void          ResolveResponse(State phase, PlayerNum player);
    void          PlayTrick(PlayerNum player);

    void          RequestCardTransfer(CardArray::CardArrayType src,
                                      CardArray::CardArrayType dest,
                                      int numCards);
    void          UpdateAI(PlayerNum player);







    /*void          BeginExchange(int player);
    void          MakeDeclaration(CardArray::SelectionType phase,
                                  PlayerNum                player);
    void          ProcessDeclaration(CardArray::SelectionType phase,
                                     PlayerNum                player);
    void          UpdateAI(PlayerNum player);

    void          TransferComplete(void);

    void          SetUI(Scene::PhaseType phase);*/
    //

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
