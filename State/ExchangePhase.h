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
#include "Layouts/CardLayout.h"
#include "AI/AI.h"


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

    void           Initialize(void);

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
    void           RequestCardTransfer(CardLayout::Type,
                                       CardLayout::Type,
                                       int, bool);
    void           TransferComplete(int);

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
