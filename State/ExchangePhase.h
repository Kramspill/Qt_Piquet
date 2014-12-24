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


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"


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

private:
    void           ConnectSignals(void);

signals:
    void           ExecuteExchange(void);
    void           ExchangeComplete(void);
    void           ExchangePhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        awaitingSignal;
    QFinalState*   finalState;
};

#endif // EXCHANGEPHASE_H
