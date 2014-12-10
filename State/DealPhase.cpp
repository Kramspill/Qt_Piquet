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
    dealToPlayer1  = new QState(stateMachine);
    dealToPlayer2  = new QState(stateMachine);
    dealToTalon    = new QState(stateMachine);
    finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(awaitingSignal);

    // Setup the transitions from the awaitingSignal state.
    awaitingSignal->addTransition(this, SIGNAL(DealToPlayer1()), dealToPlayer1);
    awaitingSignal->addTransition(this, SIGNAL(DealToPlayer2()), dealToPlayer2);

    // Setup the transitions from the dealToPlayer1 state.
    dealToPlayer1->addTransition(this, SIGNAL(TransferComplete()),
                                 dealToPlayer2);
    dealToPlayer1->addTransition(this, SIGNAL(BeginDealTalon()),   dealToTalon);

    // Setup the transitions from the dealToPlayer2 state.
    dealToPlayer2->addTransition(this, SIGNAL(TransferComplete()),
                                 dealToPlayer1);
    dealToPlayer2->addTransition(this, SIGNAL(BeginDealTalon()),   dealToTalon);

    // Setup the transitions from the dealToTalon state.
    dealToTalon->addTransition(  this, SIGNAL(TransferComplete()), finalState);

    // Initialize the dealCounter that determines when to deal the Talon.
    ResetDealCounter();

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DealPhase::onEntry(QEvent*)
{
    stateMachine->start();
    emit SetUI(Scene::DEAL);
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
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void DealPhase::ConnectSignals(void)
{
    connect(dealToPlayer1, SIGNAL(entered()), this, SLOT(DealToPlayer()));
    connect(dealToPlayer2, SIGNAL(entered()), this, SLOT(DealToCpu()));
    connect(dealToTalon,   SIGNAL(entered()), this, SLOT(DealTalon()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(DealPhaseFinished()));
}


//------------------------------------------------------------------------------
// DealToPlayer1 - Function that performs the required operations for the
//                 dealToPlayer state.
//------------------------------------------------------------------------------
void DealPhase::DealToPlayer1(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3,
                                 false);
        dealCounter--;
    }
    else
    {
        emit BeginDealTalon();
    }
}


//------------------------------------------------------------------------------
// DealToPlayer2 - Function that performs the required operations for the
//                 dealToPlayer2 state.
//------------------------------------------------------------------------------
void DealPhase::DealToPlayer2(void)
{
    if ( dealCounter > 0 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND, 3, false);
        dealCounter--;
    }
    else
    {
        emit BeginDealTalon();
    }
}


//------------------------------------------------------------------------------
// DealToTalon - Function that performs the required operations for the
//               dealToTalon state.
//------------------------------------------------------------------------------
void DealPhase::DealToTalon(void)
{
    emit RequestCardTransfer(CardArray::DECK, CardArray::TALON, 8, false);
}
