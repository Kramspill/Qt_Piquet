//------------------------------------------------------------------------------
// Filename: DealPhase.h
// Description: Header file for DealPhase.
//------------------------------------------------------------------------------

#ifndef DEALPHASE_H
#define DEALPHASE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QFinalState>
#include <QStateMachine>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"
#include "Scene/Scene.h"


//------------------------------------------------------------------------------
// Class: DealPhase
//------------------------------------------------------------------------------
class DealPhase : public QState
{
    Q_OBJECT
public:
    DealPhase(QState* parent = 0);
    DealPhase(DealPhase&);
    ~DealPhase(void);

    void           Initialize(void);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ResetDealCounter(void);
    void           ConnectSignals(void);

private slots:
    void           DealToPlayer1(void);
    void           DealToPlayer2(void);
    void           DealToTalon(void);

signals:
    void           ExecuteDeal(void);
    void           BeginDealTalon(void);
    void           DealPhaseFinished(void);

    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType,
                                       int, bool);
    void           TransferComplete(void);

    void           SetUI(Scene::PhaseType);

private:
    QStateMachine* stateMachine;
    QState*        awaitingSignal;
    QState*        dealToPlayer1;
    QState*        dealToPlayer2;
    QState*        dealToTalon;
    QFinalState*   finalState;
    int            dealCounter;
};

#endif // DEALPHASE_H
