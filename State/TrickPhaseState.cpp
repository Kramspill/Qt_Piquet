#include "TrickPhaseState.h"

// Constructor.
TrickPhaseState::TrickPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
TrickPhaseState::TrickPhaseState(TrickPhaseState& other) :
    QState(other)
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
