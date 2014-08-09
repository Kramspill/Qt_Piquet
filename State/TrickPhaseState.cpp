#include "TrickPhaseState.h"

// Constructor.
TrickPhaseState::TrickPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
TrickPhaseState::TrickPhaseState(TrickPhaseState&) :
    QState()
{
}

// Destructor.
TrickPhaseState::~TrickPhaseState(void)
{
}

void TrickPhaseState::onEntry(QEvent*)
{

}

void TrickPhaseState::onExit(QEvent*)
{

}
