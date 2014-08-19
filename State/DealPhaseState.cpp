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
    dealToPlayer->addTransition(this, SIGNAL(TransferComplete()), dealToCpu);
    dealToPlayer->addTransition(this, SIGNAL(BeginDealTalon()), dealTalon);

    // Setup the transitions from dealToCpu.
    dealToCpu->addTransition(this, SIGNAL(TransferComplete()), dealToPlayer);
    dealToCpu->addTransition(this, SIGNAL(BeginDealTalon()), dealTalon);

    // Setup the transitions from dealTalon.
    dealTalon->addTransition(this, SIGNAL(TransferComplete()), finalState);

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
// CallTransferComplete - Inform the state machine that a card transfer has been
//                        completed.
//------------------------------------------------------------------------------
void DealPhaseState::CallTransferComplete(void)
{
    emit TransferComplete();
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
}
