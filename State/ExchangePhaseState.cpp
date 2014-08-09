#include "ExchangePhaseState.h"

// Constructor.
ExchangePhaseState::ExchangePhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
ExchangePhaseState::ExchangePhaseState(ExchangePhaseState&) :
    QState()
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
