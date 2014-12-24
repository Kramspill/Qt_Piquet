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
#include "State/GlobalStateInfo.h"


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

private:
    void           ConnectSignals(void);

signals:
    void           ExecuteDeal(void);
    void           DealComplete(void);
    void           DealPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        awaitingSignal;
    QFinalState*   finalState;
};

#endif // DEALPHASE_H
