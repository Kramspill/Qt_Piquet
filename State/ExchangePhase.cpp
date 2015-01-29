//------------------------------------------------------------------------------
// Filename: ExchangePhase.cpp
// Description: Represents the exchange phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "ExchangePhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ExchangePhase::ExchangePhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
ExchangePhase::ExchangePhase(ExchangePhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
ExchangePhase::~ExchangePhase(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void ExchangePhase::Initialize(void)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    awaitingSignal  = new QState(stateMachine);
    finalState      = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(awaitingSignal);

    // Setup the transitions from the awaitingSignal state.
    awaitingSignal->addTransition(this, SIGNAL(ExchangeComplete()), finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void ExchangePhase::Destroy(void)
{
    delete awaitingSignal;  awaitingSignal = 0;
    delete finalState;      finalState     = 0;
    delete stateMachine;    stateMachine   = 0;
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void ExchangePhase::onEntry(QEvent*)
{
    currentPhase = EXCHANGE;

    if ( !restarting )
    {
        stateMachine->start();
        emit ExecuteExchange();
    }
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void ExchangePhase::onExit(QEvent*)
{
    if ( stateMachine->isRunning() )
        stateMachine->stop();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void ExchangePhase::ConnectSignals(void)
{
    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(ExchangePhaseFinished()));
}
