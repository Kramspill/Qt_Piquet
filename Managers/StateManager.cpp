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
void StateManager::Initialize(QPushButton* button, QPushButton* button2,
                              QPushButton* button3)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhase = new DealPhase(stateMachine);
    dealPhase->Initialize(button);

    exchangePhase = new ExchangePhase(stateMachine);
    exchangePhase->Initialize(button2);

    declarationPhase = new DeclarationPhase(stateMachine);
    declarationPhase->Initialize(button3);

    /*
    trickPhase = new TrickPhase();
    trickPhase->Initialize();
    */

    // Set the initial state for the state machine.
    stateMachine->setInitialState(dealPhase);

    // Setup the transitions between the states.
    dealPhase->addTransition(dealPhase, SIGNAL(DealPhaseFinished()),
                             exchangePhase);
    exchangePhase->addTransition(exchangePhase,
                                 SIGNAL(ExchangePhaseFinished()),
                                 declarationPhase);
    /*
    declarationPhase->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                    trickPhase);
    trickPhase->addTransition(SomeObject, SIGNAL(SomeSignal()),
                              playSummaryState);
    */

    // Connect the various signals.
    ConnectSignals();

    stateMachine->start();
}


//------------------------------------------------------------------------------
// GetDealPhase - Accessor for StateManager's dealPhase member
//                     variable.
//------------------------------------------------------------------------------
DealPhase* StateManager::GetDealPhase(void)
{
    return dealPhase;
}


//------------------------------------------------------------------------------
// GetExchangePhase - Accessor for StateManager's exchangePhase member
//                         variable.
//------------------------------------------------------------------------------
ExchangePhase* StateManager::GetExchangePhase(void)
{
    return exchangePhase;
}


//------------------------------------------------------------------------------
// GetDeclarationPhase - Accessor for StateManager's declarationPhase
//                            member variable.
//------------------------------------------------------------------------------
DeclarationPhase* StateManager::GetDeclarationPhase(void)
{
    return declarationPhase;
}


//------------------------------------------------------------------------------
// GetTrickPhase - Accessor for StateManager's declarationPhase member
//                      variable.
//------------------------------------------------------------------------------
TrickPhase* StateManager::GetTrickPhase(void)
{
    return trickPhase;
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void StateManager::ConnectSignals(void)
{
    // Connect signals to/from the deal phase state.
    QObject::connect(dealPhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SIGNAL(SignalCardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               int)));
    QObject::connect(this,
                     SIGNAL(SignalTransferComplete()),
                     dealPhase,
                     SLOT(CallTransferComplete()));

    // Connect signals to/fom the exchange phase state.
    QObject::connect(exchangePhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SIGNAL(SignalCardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               int)));
    QObject::connect(exchangePhase,
                     SIGNAL(RequestSelectedCardsTransfer(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)),
                     this,
                     SIGNAL(SignalTransferSelectedCards(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)));

    QObject::connect(exchangePhase,
                     SIGNAL(RequestCardsSelectable(bool)),
                     this,
                     SIGNAL(SignalSetCardsSelectable(bool)));
    QObject::connect(this,
                     SIGNAL(SignalTransferComplete()),
                     exchangePhase,
                     SLOT(CallTransferComplete()));
    QObject::connect(this,
                     SIGNAL(SignalNumOfCardsTransferred(int)),
                     exchangePhase,
                     SLOT(SetNumCardsTransferred(int)));
}
