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
void DealPhase::Initialize(QPushButton* button)
{
    // Initialize the dealCounter that determines when to deal the Talon.
    ResetDealCounter();

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

    // Setup the transitions from initialState.
    initialState->addTransition(button, SIGNAL(clicked()),        dealToPlayer);

    // Setup the transitions from dealToPlayer.
    dealToPlayer->addTransition(this, SIGNAL(TransferComplete()), dealToCpu);
    dealToPlayer->addTransition(this, SIGNAL(BeginDealTalon()),   dealTalon);

    // Setup the transitions from dealToCpu.
    dealToCpu->addTransition(   this, SIGNAL(TransferComplete()), dealToPlayer);
    dealToCpu->addTransition(   this, SIGNAL(BeginDealTalon()),   dealTalon);

    // Setup the transitions from dealTalon.
    dealTalon->addTransition(   this, SIGNAL(TransferComplete()), finalState);

    // Setup the work done in each state.
    connect(dealToPlayer, SIGNAL(entered()),  this, SLOT(DealToPlayer()));
    connect(dealToCpu,    SIGNAL(entered()),  this, SLOT(DealToCpu()));
    connect(dealTalon,    SIGNAL(entered()),  this, SLOT(DealTalon()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(DealPhaseFinished()));
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DealPhase::onEntry(QEvent*)
{
    stateMachine->start();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void DealPhase::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// ResetDealCounter - Reset the dealCounter member variable.
//------------------------------------------------------------------------------
void DealPhase::ResetDealCounter(void)
{
    dealCounter = 8;
}


//------------------------------------------------------------------------------
// DealToPlayer - Function that performs the required operations for the
//                dealToPlayer state.
//------------------------------------------------------------------------------
void DealPhase::DealToPlayer(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        dealCounter--;
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
void DealPhase::DealToCpu(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND, 3);
        dealCounter--;
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
void DealPhase::DealTalon(void)
{
    emit RequestCardTransfer(CardArray::DECK, CardArray::TALON, 8);
}
