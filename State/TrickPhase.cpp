//------------------------------------------------------------------------------
// Filename: TrickPhase.cpp
// Description: Represents the trick phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "TrickPhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
TrickPhase::TrickPhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
TrickPhase::TrickPhase(TrickPhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
TrickPhase::~TrickPhase(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void TrickPhase::Initialize(void)
{
    // For now assume player goes first.
    player = true;

    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    playerTrick = new QState(stateMachine);
    cpuTrick    = new QState(stateMachine);
    scoreTrick  = new QState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(scoreTrick);

    // Setup the transitions from scoreTrick.
    scoreTrick->addTransition(this,  SIGNAL(PlayersTurn()), playerTrick);
    scoreTrick->addTransition(this,  SIGNAL(CpusTurn()),    cpuTrick);

    // Setup the transitions from playerTrick.
    playerTrick->addTransition(this, SIGNAL(CpusTurn()),    cpuTrick);

    // Setup the transitions from cpuTrick.
    cpuTrick->addTransition(this,    SIGNAL(PlayersTurn()), playerTrick);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void TrickPhase::onEntry(QEvent*)
{
    stateMachine->start();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void TrickPhase::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void TrickPhase::ConnectSignals(void)
{
    connect(scoreTrick,  SIGNAL(entered()),  this, SLOT(ScoreTrick()));
    connect(playerTrick, SIGNAL(entered()),  this, SLOT(PlayerTrick()));
    connect(playerTrick, SIGNAL(exited()),   this, SLOT(ExitPlayerTrick()));
    connect(cpuTrick,    SIGNAL(entered()),  this, SLOT(CpuTrick()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(TrickPhaseFinished()));
}


//------------------------------------------------------------------------------
// PlayerMoveFinished - When a card is transferred, check if the user did the
//                      transferral and cycle the state.
//------------------------------------------------------------------------------
void TrickPhase::PlayerMoveFinished(int numOfCardsTransferred)
{
    if ( stateMachine->configuration().contains(playerTrick) &&
         numOfCardsTransferred == 1 )
    {
        // ERROR HERE!!!
        emit CpusTurn();
    }
}


//------------------------------------------------------------------------------
// ScoreTrick - Function that performs the required operations for the
//              scoreTrick state.
//------------------------------------------------------------------------------
void TrickPhase::ScoreTrick(void)
{
    emit CheckTrick(player);
}


//------------------------------------------------------------------------------
// PlayerTrick - Function that performs the required operations for the
//               playerTrick state.
//------------------------------------------------------------------------------
void TrickPhase::PlayerTrick(void)
{
    emit SetCardsMoveable(true);

    if ( !player )
    {
        emit CheckTrick(player);
    }
}


//------------------------------------------------------------------------------
// PlayerTrick - Function that performs the required operations for the
//               playerTrick exited() state.
//------------------------------------------------------------------------------
void TrickPhase::ExitPlayerTrick(void)
{
    emit SetCardsMoveable(false);
}


//------------------------------------------------------------------------------
// CpuTrick - Function that performs the required operations for the cpuTrick
//            state.
//------------------------------------------------------------------------------
void TrickPhase::CpuTrick(void)
{
    emit UpdateAI();
    emit SignalAI(AI::TRICK);
    emit RequestCardTransfer(CardArray::CPUHAND, CardArray::CPUTRICK,
                             0, true);

    if ( player )
    {
        emit CheckTrick(player);
    }
    else
    {
        emit PlayersTurn();
    }
}


//------------------------------------------------------------------------------
// TrickResult - Function that gets called to update who should lead the next
//               trick.
//------------------------------------------------------------------------------
void TrickPhase::TrickResult(bool winningPlayer)
{
    player = winningPlayer;

    if ( winningPlayer )
    {
        emit PlayersTurn();
    }
    else
    {
        emit CpusTurn();
    }
}
