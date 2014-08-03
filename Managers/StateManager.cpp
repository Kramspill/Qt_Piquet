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

// Initialize the phases that represent the
// states of the game.
void StateManager::Initialize(void)
{
    // Allocate memory to the phases
    // and initialize them.
    dealPhase = new DealPhase();
    dealPhase->Initialize();

    /* Progressively add these.
    exchangePhase = new ExchangePhase();
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase();
    declarationPhase->Initialize();

    trickPhase = new TrickPhase();
    trickPhase->Initialize();
    */

    // Set the current phase to be
    // the deal phase.
    currentPhase = new Phase();
    currentPhase = dealPhase;
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
