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
#include <QEvent>


//------------------------------------------------------------------------------
// Class: TrickPhase
//------------------------------------------------------------------------------
class TrickPhase : public QState
{
public:
    TrickPhase(QState* parent = 0);
    TrickPhase(TrickPhase&);
    ~TrickPhase(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // TRICKPHASE_H
