//------------------------------------------------------------------------------
// Filename: ExchangePhase.h
// Description: Header file for ExchangePhase.
//------------------------------------------------------------------------------

#ifndef EXCHANGEPHASE_H
#define EXCHANGEPHASE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QFinalState>
#include <QStateMachine>
#include <QEvent>
#include <QPushButton>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"
#include "AI/AI.h"
#include "Scene/Scene.h"


//------------------------------------------------------------------------------
// Class: ExchangePhase
//------------------------------------------------------------------------------
class ExchangePhase : public QState
{
    Q_OBJECT
public:
    ExchangePhase(QState* parent = 0);
    ExchangePhase(ExchangePhase&);
    ~ExchangePhase(void);

    void           Initialize(QPushButton* button);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ConnectSignals(void);

private slots:
    void           SignalEnableCardsSelectable(void);
    void           SignalDisableCardsSelectable(void);

    void           InformTransferComplete(int numOfCardsTransferred);

    void           PlayerDiscard(void);
    void           PlayerDraw(void);
    void           CpuProcessing(void);
    void           CpuDiscard(void);
    void           CpuDraw(void);

signals:
    void           SetCardsSelectable(bool, int);
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType,
                                       int, bool);
    void           TransferComplete(int);
    void           SetUI(Scene::PhaseType);
    void           ExecuteExchange(void);

    void           TransitionState(void);

    void           UpdateAI(void);
    void           SignalAI(AI::AIAction);
    void           AIProcessingComplete(void);

    void           ExchangePhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        playerDiscard;
    QState*        playerDraw;
    QState*        cpuProcessing;
    QState*        cpuDiscard;
    QState*        cpuDraw;
    QFinalState*   finalState;
    QPushButton*   exchangeButton;
    int            cardsTransferred;
};

#endif // EXCHANGEPHASE_H
