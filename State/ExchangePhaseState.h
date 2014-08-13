//------------------------------------------------------------------------------
// Filename: ExchangePhaseState.h
// Description: Header file for ExchangePhaseState.
//------------------------------------------------------------------------------

#ifndef EXCHANGEPHASESTATE_H
#define EXCHANGEPHASESTATE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QEvent>


//------------------------------------------------------------------------------
// Class: ExchangePhaseState
//------------------------------------------------------------------------------
class ExchangePhaseState : public QState
{
public:
    ExchangePhaseState(QState* parent = 0);
    ExchangePhaseState(ExchangePhaseState&);
    ~ExchangePhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // EXCHANGEPHASESTATE_H
