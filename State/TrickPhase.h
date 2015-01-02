//------------------------------------------------------------------------------
// Filename: TrickPhase.h
// Description: Header file for TrickPhase.
//------------------------------------------------------------------------------

#ifndef TRICKPHASE_H
#define TRICKPHASE_H

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
// Class: TrickPhase
//------------------------------------------------------------------------------
class TrickPhase : public QState
{
    Q_OBJECT
public:
    TrickPhase(QState* parent = 0);
    TrickPhase(TrickPhase&);
    ~TrickPhase(void);

    void           Initialize(void);

protected:
    void           onEntry(QEvent*);

private:
    void           ConnectSignals(void);

private slots:
    void           PlayTricks(void);

signals:
    void           PlayTrick(PlayerNum, bool);
    void           TricksComplete(void);
    void           TrickPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        playTricks;
    QFinalState*   finalState;
};

#endif // TRICKPHASE_H
