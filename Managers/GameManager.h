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
#include "AI/AI.h"
#include "CardManager.h"
#include "StateManager.h"
#include "ScoreManager.h"

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
    void          RequestCardTransfer(CardArray::CardArrayType src,
                                      CardArray::CardArrayType dest,
                                      int  numOfCards,
                                      bool transferSelectedCards);
    void          DeclareSelection(CardArray::SelectionType phase);
    void          SelectAIAction(AI::AIAction action);
    void          UpdateAI(void);

    void          SetUI(Scene::PhaseType phase);

private:
    Scene*        scene;
    View*         view;
    AI*           ai;
    CardManager*  cardManager;
    StateManager* stateManager;
    ScoreManager* scoreManager;
};

#endif // GAMEMANAGER_H
