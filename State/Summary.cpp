//------------------------------------------------------------------------------
// Filename: Summary.cpp
// Description: Summary of the last partie/game played.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Summary.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Summary::Summary(QState *parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
Summary::Summary(Summary&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Summary::~Summary(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void Summary::Initialize(void)
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
                                  SIGNAL(SummaryComplete()),
                                  finalState);
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void Summary::onEntry(QEvent*)
{
    currentPhase = SUMMARY;

    stateMachine->start();
    emit ExecuteSummary();
    emit SummaryComplete();
    if ( partieResults->currentDeal == 0 )
        emit NewGame();
    else
        emit NextHand();
}
