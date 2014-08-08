#include "ExchangePhaseState.h"

// Constructor.
ExchangePhaseState::ExchangePhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
ExchangePhaseState::ExchangePhaseState(ExchangePhaseState& other) :
    QState(other)
{
}

// Destructor.
ExchangePhaseState::~ExchangePhaseState(void)
{
}

void ExchangePhaseState::onEntry(QEvent*)
{

}

void ExchangePhaseState::onExit(QEvent*)
{

}
