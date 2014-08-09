#include "DealPhaseState.h"

// Constructor.
DealPhaseState::DealPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
DealPhaseState::DealPhaseState(DealPhaseState&) :
    QState()
{
}

// Destructor.
DealPhaseState::~DealPhaseState(void)
{
}

// Initialize and execute the internal state machine of
// the DealPhaseState.
void DealPhaseState::onEntry(QEvent*)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    QState*      initialState = new QState(stateMachine);
    QState*      dealToPlayer = new QState(stateMachine);
    QState*      dealToCpu    = new QState(stateMachine);
    QState*      dealTalon    = new QState(stateMachine);
    QFinalState* finalState   = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(initialState);

    /*
    // Setup the transitions from initialState.
    initialState->addTransition(SomeObject, SIGNAL(clicked()), dealToPlayer);
    initialState->addTransition(SomeObject, SIGNAL(clicked()), dealToCpu);

    // Setup the transitions from dealToPlayer.
    dealToPlayer->addTransition(SomeObject, SIGNAL(clicked()), dealToCpu);
    dealToPlayer->addTransition(SomeObject, SIGNAL(clicked()), dealTalon);

    // Setup the transitions from dealToCpu.
    dealToCpu->addTransition(SomeObject, SIGNAL(clicked()), dealToPlayer);
    dealToCpu->addTransition(SomeObject, SIGNAL(clicked()), dealTalon);

    // Setup the transitions from dealTalon.
    dealTalon->addTransition(SomeObject, SIGNAL(clicked()), finalState);
    */

    /*
    // Setup the work done in each state.
    connect(dealToPlayer, SIGNAL(entered()), this, SLOT(DealToPlayer()));
    connect(dealToCpu,    SIGNAL(entered()), this, SLOT(DealToCpu()));
    connect(dealTalon,    SIGNAL(entered()), this, SLOT(DealTalon()));
    */
}

void DealPhaseState::onExit(QEvent*)
{

}

void DealPhaseState::DealToPlayer(void)
{

}

void DealPhaseState::DealToCpu(void)
{

}

void DealPhaseState::DealTalon(void)
{

}
