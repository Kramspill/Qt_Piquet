//------------------------------------------------------------------------------
// Filename: DealPhaseState.cpp
// Description: Represents the deal phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "DealPhaseState.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
DealPhaseState::DealPhaseState(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
DealPhaseState::DealPhaseState(DealPhaseState&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
DealPhaseState::~DealPhaseState(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void DealPhaseState::Initialize(QPushButton* button)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the timers for the deals to allow animation.
    DealToPlayerTimer = new QTimer();
    DealToCpuTimer    = new QTimer();
    DealTalonTimer    = new QTimer();

    // Initialize the dealCounter that determines when to deal the Talon.
    ResetDealCounter();

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
    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(DealPhaseFinished()));

    // Animation delay timer setup.
    connect(DealToPlayerTimer, SIGNAL(timeout()), this,
            SIGNAL(BeginDealToCpu()));
    connect(DealToCpuTimer,    SIGNAL(timeout()), this,
            SIGNAL(BeginDealToPlayer()));
    connect(DealTalonTimer,    SIGNAL(timeout()), this,
            SIGNAL(DealTalonFinished()));
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DealPhaseState::onEntry(QEvent*)
{
    stateMachine->start();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void DealPhaseState::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// ResetDealCounter - Reset the dealCounter member variable.
//------------------------------------------------------------------------------
void DealPhaseState::ResetDealCounter(void)
{
    dealCounter = 8;
}


//------------------------------------------------------------------------------
// DealToPlayer - Function that performs the required operations for the
//                dealToPlayer state.
//------------------------------------------------------------------------------
void DealPhaseState::DealToPlayer(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);

        dealCounter--;
        DealToPlayerTimer->start(100);
    }
    else
    {
        emit BeginDealTalon();
    }
}


//------------------------------------------------------------------------------
// DealToCpu - Function that performs the required operations for the dealToCpu
//             state.
//------------------------------------------------------------------------------
void DealPhaseState::DealToCpu(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND, 3);

        dealCounter--;
        DealToCpuTimer->start(100);
    }
    else
    {
        emit BeginDealTalon();
    }
}


//------------------------------------------------------------------------------
// DealTalon - Function that performs the required operations for the dealTalon
//             state.
//------------------------------------------------------------------------------
void DealPhaseState::DealTalon(void)
{
    emit RequestCardTransfer(CardArray::DECK, CardArray::TALON, 8);

    DealTalonTimer->start(100);
}
