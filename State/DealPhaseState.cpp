#include "DealPhaseState.h"

// Constructor.
DealPhaseState::DealPhaseState(QState* parent) :
    QState(parent)
{
    // This may get removed and called explicitly.
    //Initialize();
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
// the DealPhaseState. QPushButton* button added for now.
void DealPhaseState::Initialize(QPushButton* button)
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

    initialState->addTransition(button, SIGNAL(clicked()), dealToPlayer);
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

    // Setup the work done in each state.
    connect(dealToPlayer, SIGNAL(entered()),  this, SLOT(DealToPlayer()));
    connect(dealToCpu,    SIGNAL(entered()),  this, SLOT(DealToCpu()));
    connect(dealTalon,    SIGNAL(entered()),  this, SLOT(DealTalon()));
    connect(stateMachine, SIGNAL(finished()), this, SIGNAL(DealPhaseFinished()));
}

void DealPhaseState::onEntry(QEvent*)
{
    stateMachine->start();
}

void DealPhaseState::onExit(QEvent*)
{

}

void DealPhaseState::DealToPlayer(void)
{
    CardArray* deck       = CardManager::GetSingleton().GetDeck();
    CardArray* playerHand = CardManager::GetSingleton().GetPlayerHand();

    CardManager::GetSingleton().TransferCards(deck, playerHand, 3);
}

void DealPhaseState::DealToCpu(void)
{
    CardArray* deck       = CardManager::GetSingleton().GetDeck();
    CardArray* cpuHand    = CardManager::GetSingleton().GetCpuHand();

    CardManager::GetSingleton().TransferCards(deck, cpuHand, 3);
}

void DealPhaseState::DealTalon(void)
{
    CardArray* deck       = CardManager::GetSingleton().GetDeck();
    CardArray* talon      = CardManager::GetSingleton().GetTalon();

    CardManager::GetSingleton().TransferCards(deck, talon, 3);
}
