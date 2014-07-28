#include "StateManager.h"

// Constructor.
StateManager::StateManager(void)
{
}

// Copy Constructor.
StateManager::StateManager(StateManager&)
{
}

// Destructor.
StateManager::~StateManager(void)
{
}

// Accessor for StateManager's currentPhase member.
Phase* StateManager::GetCurrentPhase(void)
{
    return currentPhase;
}

// Accessor for StateManager's dealPhase member.
Phase* StateManager::GetDealPhase(void)
{
    return dealPhase;
}

// Accessor for StateManager's exchangePhase member.
Phase* StateManager::GetExchangePhase(void)
{
    return exchangePhase;
}

// Accessor for StateManager's declarationPhase member.
Phase* StateManager::GetDeclarationPhase(void)
{
    return declarationPhase;
}

// Accessor for StateManager's trickPhase member.
Phase* StateManager::GetTrickPhase(void)
{
    return trickPhase;
}

// Mutator for StateManager's currentPhase member.
// Changes currentPhase to the next phase in the game.
void StateManager::CycleCurrentPhase(void)
{
    //currentPhase = currentPhase->next();
}
