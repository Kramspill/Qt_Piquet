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
#include <QEvent>
#include <QPushButton>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"


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

    void           Initialize(QPushButton* button);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ResetDealCounter(void);
    void           ConnectSignals(void);

private slots:
    void           DealToPlayer(void);
    void           DealToCpu(void);
    void           DealTalon(void);

signals:
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType,
                                       int, bool);
    void           TransferComplete(void);

    void           BeginDealTalon(void);

    void           DealPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        initialState;
    QState*        dealToPlayer;
    QState*        dealToCpu;
    QState*        dealTalon;
    QFinalState*   finalState;
    int            dealCounter;
};

#endif // DEALPHASE_H
