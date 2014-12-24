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
void StateManager::Initialize(void)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhase = new DealPhase(stateMachine);
    dealPhase->Initialize();

    exchangePhase = new ExchangePhase(stateMachine);
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase(stateMachine);
    declarationPhase->Initialize();

    trickPhase = new TrickPhase(stateMachine);
    trickPhase->Initialize();

    // Set the initial state for the state machine.
    stateMachine->setInitialState(dealPhase);

    // Setup the transitions between the states.
    dealPhase->addTransition(       dealPhase,
                                    SIGNAL(DealPhaseFinished()),
                                    exchangePhase);
    exchangePhase->addTransition(   exchangePhase,
                                    SIGNAL(ExchangePhaseFinished()),
                                    declarationPhase);
    declarationPhase->addTransition(declarationPhase,
                                    SIGNAL(DeclarationPhaseFinished()),
                                    trickPhase);
/*
    trickPhase->addTransition(      SomeObject,
                                    SIGNAL(SomeSignal()),
                                    playSummaryState);
*/

    // Connect the various signals.
    ConnectSignals();

    stateMachine->start();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void StateManager::ConnectSignals(void)
{
    // Connect signals to/from the deal phase state.
    QObject::connect(dealPhase,
                     SIGNAL(ExecuteDeal()),
                     this,
                     SIGNAL(ExecuteDeal()));
    QObject::connect(this,
                     SIGNAL(DealComplete()),
                     dealPhase,
                     SIGNAL(DealComplete()));

    // Connect signals to/from the exchange phase state.
    QObject::connect(exchangePhase,
                     SIGNAL(ExecuteExchange()),
                     this,
                     SIGNAL(ExecuteExchange()));
    QObject::connect(this,
                     SIGNAL(ExchangeComplete()),
                     exchangePhase,
                     SIGNAL(ExchangeComplete()));

    // Connect signals to/from the declaration phase state.
    QObject::connect(declarationPhase,
                     SIGNAL(AnnounceDeclaration(State, PlayerNum)),
                     this,
                     SIGNAL(AnnounceDeclaration(State, PlayerNum)));
    QObject::connect(declarationPhase,
                     SIGNAL(PlayTrick(PlayerNum)),
                     this,
                     SIGNAL(PlayTrick(PlayerNum)));
}
