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
StateManager::StateManager(StateManager&) :
    QObject()
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
void StateManager::Initialize(QPushButton* button, QPushButton* button2)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhaseState = new DealPhaseState(stateMachine);
    dealPhaseState->Initialize(button);

    exchangePhaseState = new ExchangePhaseState(stateMachine);
    exchangePhaseState->Initialize(button2);

    /*
    declarationPhase = new DeclarationPhase();
    declarationPhase->Initialize();

    trickPhase = new TrickPhase();
    trickPhase->Initialize();
    */

    // Set the initial state for the state machine.
    stateMachine->setInitialState(dealPhaseState);

    // Setup the transitions between the states.
    dealPhaseState->addTransition(dealPhaseState, SIGNAL(DealPhaseFinished()),
                                  exchangePhaseState);
    /*
    exchangePhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                      declarationPhaseState);
    declarationPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                         trickPhaseState);
    trickPhaseState->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                   playSummaryState);
    */

    // Connect the various signals.
    ConnectSignals();

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


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals.
//------------------------------------------------------------------------------
void StateManager::ConnectSignals(void)
{
    // Connect signals to/from the deal phase state.
    QObject::connect(dealPhaseState,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SIGNAL(SignalCardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               int)));
    QObject::connect(this,
                     SIGNAL(SignalTransferComplete()),
                     dealPhaseState,
                     SLOT(CallTransferComplete()));

    // Connect signals to/fom the exchange phase state.
    QObject::connect(exchangePhaseState,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SIGNAL(SignalCardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               int)));
    QObject::connect(exchangePhaseState,
                     SIGNAL(RequestSelectedCardsTransfer(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)),
                     this,
                     SIGNAL(SignalTransferSelectedCards(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)));
    QObject::connect(this,
                     SIGNAL(SignalTransferComplete()),
                     exchangePhaseState,
                     SLOT(CallTransferComplete()));
    QObject::connect(exchangePhaseState,
                     SIGNAL(RequestCardsSelectable(bool)),
                     this,
                     SIGNAL(SignalSetCardsSelectable(bool)));
}
