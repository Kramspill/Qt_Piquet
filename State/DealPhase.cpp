//------------------------------------------------------------------------------
// Filename: DealPhase.cpp
// Description: Represents the deal phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "DealPhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
DealPhase::DealPhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
DealPhase::DealPhase(DealPhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
DealPhase::~DealPhase(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void DealPhase::Initialize(void)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    awaitingSignal = new QState(stateMachine);
    finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(awaitingSignal);

    // Setup the transitions from the awaitingSignal state.
    awaitingSignal->addTransition(this, SIGNAL(DealComplete()), finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void DealPhase::Destroy(void)
{
    delete awaitingSignal;  awaitingSignal = 0;
    delete finalState;      finalState     = 0;
    delete stateMachine;    stateMachine   = 0;
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DealPhase::onEntry(QEvent*)
{
    currentPhase = DEAL;

    stateMachine->start();
    emit ExecuteDeal();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void DealPhase::onExit(QEvent*)
{
    if ( stateMachine->isRunning() )
        stateMachine->stop();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void DealPhase::ConnectSignals(void)
{
    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(DealPhaseFinished()));
}
