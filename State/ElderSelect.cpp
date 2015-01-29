//------------------------------------------------------------------------------
// Filename: ElderSelect.cpp
// Description: The elder is selected based on random numbers.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "ElderSelect.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ElderSelect::ElderSelect(QState *parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
ElderSelect::ElderSelect(ElderSelect&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
ElderSelect::~ElderSelect(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void ElderSelect::Initialize(void)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    awaitingSignal = new QState(stateMachine);
    finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(awaitingSignal);

    // Setup the transitions from the awaitingSignal state.
    awaitingSignal->addTransition(this,
                                  SIGNAL(ElderSelectComplete()),
                                  finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void ElderSelect::Destroy(void)
{
    delete awaitingSignal;  awaitingSignal = 0;
    delete finalState;      finalState     = 0;
    delete stateMachine;    stateMachine   = 0;
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void ElderSelect::onEntry(QEvent*)
{
    currentPhase = ELDERSELECT;

    if ( !restarting )
    {
        stateMachine->start();
        emit ExecuteElderSelect();
    }
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void ElderSelect::onExit(QEvent*)
{
    if ( stateMachine->isRunning() )
        stateMachine->stop();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void ElderSelect::ConnectSignals(void)
{
    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(ElderSelectFinished()));
}
