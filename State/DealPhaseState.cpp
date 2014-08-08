#include "DealPhaseState.h"

// Constructor.
DealPhaseState::DealPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
DealPhaseState::DealPhaseState(DealPhaseState& other) :
    QState(other)
{
}

// Destructor.
DealPhaseState::~DealPhaseState(void)
{
}

void DealPhaseState::onEntry(QEvent*)
{

}

void DealPhaseState::onExit(QEvent*)
{

}
