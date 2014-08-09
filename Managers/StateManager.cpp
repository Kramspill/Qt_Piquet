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
void StateManager::Initialize(CardArray* deck, QPushButton* button)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases
    // and initialize them.
    dealPhaseState = new DealPhaseState(stateMachine);

    /*
    exchangePhase = new ExchangePhase();
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase();
    declarationPhase->Initialize();

    trickPhase = new TrickPhase();
    trickPhase->Initialize();
    */

    /*
    // Setup the transitions between the states.
    dealPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()), exchangePhaseState);
    exchangePhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()), declarationPhaseState);
    declarationPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()), trickPhaseState);
    trickPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()), playSummaryState);
    */
}

// Accessor for StateManager's dealPhase member.
DealPhaseState* StateManager::GetDealPhase(void)
{
    return dealPhaseState;
}

// Accessor for StateManager's exchangePhase member.
ExchangePhaseState* StateManager::GetExchangePhase(void)
{
    return exchangePhaseState;
}

// Accessor for StateManager's declarationPhase member.
DeclarationPhaseState* StateManager::GetDeclarationPhase(void)
{
    return declarationPhaseState;
}

// Accessor for StateManager's trickPhase member.
TrickPhaseState* StateManager::GetTrickPhase(void)
{
    return trickPhaseState;
}
