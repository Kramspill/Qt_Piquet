//------------------------------------------------------------------------------
// Filename: StateManager.cpp
// Description: Manager for the various states in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "StateManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
StateManager::StateManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
StateManager::StateManager(StateManager&)
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
StateManager::~StateManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the phases that represent the states of the game.
//------------------------------------------------------------------------------
void StateManager::Initialize(QPushButton* button)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhaseState = new DealPhaseState(stateMachine);
    dealPhaseState->Initialize(button);

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
    dealPhaseState->addTransition(dealPhaseState, SIGNAL(DealPhaseFinished()),
                                  exchangePhaseState);
    exchangePhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                      declarationPhaseState);
    declarationPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                         trickPhaseState);
    trickPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                   playSummaryState);
    */

    stateMachine->setInitialState(dealPhaseState);

    stateMachine->start();
}


//------------------------------------------------------------------------------
// GetDealPhaseState - Accessor for StateManager's dealPhaseState member
//                     variable.
//------------------------------------------------------------------------------
DealPhaseState* StateManager::GetDealPhaseState(void)
{
    return dealPhaseState;
}


//------------------------------------------------------------------------------
// GetExchangePhaseState - Accessor for StateManager's exchangePhaseState member
//                         variable.
//------------------------------------------------------------------------------
ExchangePhaseState* StateManager::GetExchangePhaseState(void)
{
    return exchangePhaseState;
}


//------------------------------------------------------------------------------
// GetDeclarationPhaseState - Accessor for StateManager's declarationPhaseState
//                            member variable.
//------------------------------------------------------------------------------
DeclarationPhaseState* StateManager::GetDeclarationPhaseState(void)
{
    return declarationPhaseState;
}


//------------------------------------------------------------------------------
// GetTrickPhaseState - Accessor for StateManager's declarationPhaseState member
//                      variable.
//------------------------------------------------------------------------------
TrickPhaseState* StateManager::GetTrickPhaseState(void)
{
    return trickPhaseState;
}
