//------------------------------------------------------------------------------
// Filename: TrickPhase.cpp
// Description: Represents the trick phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "TrickPhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
TrickPhase::TrickPhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
TrickPhase::TrickPhase(TrickPhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
TrickPhase::~TrickPhase(void)
{
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void TrickPhase::onEntry(QEvent*)
{

}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void TrickPhase::onExit(QEvent*)
{

}