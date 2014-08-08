#include "DealPhase.h"

// Constructor.
DealPhase::DealPhase(void)
{
}

// Copy Constructor.
DealPhase::DealPhase(DealPhase& other) : Phase(other)
{
}

// Destructor.
DealPhase::~DealPhase(void)
{
}

// Initialize the state machine.
void DealPhase::Initialize(void)
{
    // Allocate space for members.
    dealPhaseStateMachine = new QStateMachine();
    dealToPlayer          = new QState();
    dealToCPU             = new QState();
    dealTalon             = new QFinalState();

    // Set the position that the cards will end up for each transition.

    // Setup the transitions.
    //dealToPlayer->addTransition(/*object*/, /*SIGNAL()*/, dealToCPU);
    //dealToPlayer->addTransition(/*object*/, /*SIGNAL()*/, dealTalon);
    //dealToCPU->addTransition(/*object*/, /*SIGNAL()*/, dealToPlayer);
    //dealToCPU->addTransition(/*object*/, /*SIGNAL()*/, dealTalon);

    // Add the states to the state machine.
    dealPhaseStateMachine->addState(dealToPlayer);
    dealPhaseStateMachine->addState(dealToCPU);
    dealPhaseStateMachine->addState(dealTalon);

    // Set the intial state (for now will be dealToPlayer).
}

// Execute the state machine.
void DealPhase::Execute(void)
{
    dealPhaseStateMachine->start();
}

// Accessor for DealPhase's name member.
char* DealPhase::GetName(void)
{
    return name;
}
