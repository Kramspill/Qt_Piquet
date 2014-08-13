//------------------------------------------------------------------------------
// Filename: DeclarationPhaseState.h
// Description: Header file for DeclarationPhaseState.
//------------------------------------------------------------------------------

#ifndef DECLARATIONPHASESTATE_H
#define DECLARATIONPHASESTATE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QEvent>


//------------------------------------------------------------------------------
// Class: DeclarationPhaseState
//------------------------------------------------------------------------------
class DeclarationPhaseState : public QState
{
public:
    DeclarationPhaseState(QState* parent = 0);
    DeclarationPhaseState(DeclarationPhaseState&);
    ~DeclarationPhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // DECLARATIONPHASESTATE_H
