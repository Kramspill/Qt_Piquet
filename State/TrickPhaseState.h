//------------------------------------------------------------------------------
// Filename: TrickPhaseState.h
// Description: Header file for TrickPhaseState.
//------------------------------------------------------------------------------

#ifndef TRICKPHASESTATE_H
#define TRICKPHASESTATE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QEvent>


//------------------------------------------------------------------------------
// Class: DealPhase
//------------------------------------------------------------------------------
class TrickPhaseState : public QState
{
public:
    TrickPhaseState(QState* parent = 0);
    TrickPhaseState(TrickPhaseState&);
    ~TrickPhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // TRICKPHASESTATE_H
