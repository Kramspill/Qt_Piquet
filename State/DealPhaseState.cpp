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

    // Initialize the timers for the deals to allow animation.
    DealToPlayerTimer = new QTimer();
    DealToCpuTimer    = new QTimer();
    DealTalonTimer    = new QTimer();

    // Initialize the dealCounter that determines when to deal the Talon.
    dealCounter = 8;

    // Initialize the states within the state machine.
    QState*      initialState = new QState(stateMachine);
    QState*      dealToPlayer = new QState(stateMachine);
    QState*      dealToCpu    = new QState(stateMachine);
    QState*      dealTalon    = new QState(stateMachine);
    QFinalState* finalState   = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(initialState);

    // Setup the transitions from initialState.
    initialState->addTransition(button, SIGNAL(clicked()), dealToPlayer);
    //initialState->addTransition(SomeObject, SIGNAL(clicked()), dealToCpu);

    // Setup the transitions from dealToPlayer.
    dealToPlayer->addTransition(this, SIGNAL(BeginDealToCpu()), dealToCpu);
    dealToPlayer->addTransition(this, SIGNAL(BeginDealTalon()), dealTalon);

    // Setup the transitions from dealToCpu.
    dealToCpu->addTransition(this, SIGNAL(BeginDealToPlayer()), dealToPlayer);
    dealToCpu->addTransition(this, SIGNAL(BeginDealTalon()), dealTalon);

    // Setup the transitions from dealTalon.
    dealTalon->addTransition(this, SIGNAL(DealTalonFinished()), finalState);

    // Setup the work done in each state.
    connect(dealToPlayer, SIGNAL(entered()),  this, SLOT(DealToPlayer()));
    connect(dealToCpu,    SIGNAL(entered()),  this, SLOT(DealToCpu()));
    connect(dealTalon,    SIGNAL(entered()),  this, SLOT(DealTalon()));
    connect(stateMachine, SIGNAL(finished()), this, SIGNAL(DealPhaseFinished()));

    // Animation delay timer setup.
    connect(DealToPlayerTimer, SIGNAL(timeout()), this, SIGNAL(BeginDealToCpu()));
    connect(DealToCpuTimer,    SIGNAL(timeout()), this, SIGNAL(BeginDealToPlayer()));
    connect(DealTalonTimer,    SIGNAL(timeout()), this, SIGNAL(DealTalonFinished()));
}

void DealPhaseState::onEntry(QEvent*)
{
    stateMachine->start();
}

void DealPhaseState::onExit(QEvent*)
{

}

void DealPhaseState::ResetDealCounter(void)
{
    dealCounter = 8;
}

void DealPhaseState::DealToPlayer(void)
{
    if ( dealCounter > 0 )
    {
        CardArray* deck       = CardManager::GetSingleton().GetDeck();
        CardArray* playerHand = CardManager::GetSingleton().GetPlayerHand();

        CardManager::GetSingleton().TransferCards(deck, playerHand, 3);

        dealCounter--;
        DealToPlayerTimer->start(100);
    }
    else
    {
        emit BeginDealTalon();
    }
}

void DealPhaseState::DealToCpu(void)
{
    if ( dealCounter > 0 )
    {
        CardArray* deck       = CardManager::GetSingleton().GetDeck();
        CardArray* cpuHand    = CardManager::GetSingleton().GetCpuHand();

        CardManager::GetSingleton().TransferCards(deck, cpuHand, 3);

        dealCounter--;
        DealToCpuTimer->start(100);
    }
    else
    {
        emit BeginDealTalon();
    }
}

void DealPhaseState::DealTalon(void)
{
    CardArray* deck       = CardManager::GetSingleton().GetDeck();
    CardArray* talon      = CardManager::GetSingleton().GetTalon();

    CardManager::GetSingleton().TransferCards(deck, talon, 8);

    DealTalonTimer->start(100);
}
