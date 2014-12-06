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
    player = 1;

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
    playerTrick->addTransition(this, SIGNAL(CheckTrick()),    scoreTrick);

    // Setup the transitions from cpuTrick.
    cpuTrick->addTransition(this,    SIGNAL(CheckTrick()), scoreTrick);

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
void TrickPhase::MoveFinished(int numOfCardsTransferred)
{
    if ( (stateMachine->configuration().contains(playerTrick) ||
          stateMachine->configuration().contains(cpuTrick)) &&
         numOfCardsTransferred < 2 )
    {
        emit CheckTrick();
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
}


//------------------------------------------------------------------------------
// TrickResult - Function that gets called to update who should lead the next
//               trick.
//------------------------------------------------------------------------------
void TrickPhase::TrickResult(int winningPlayer)
{
    if ( winningPlayer == 0 || winningPlayer == 1 )
    {
        player = winningPlayer;

        if ( player == 1 )
            emit PlayersTurn();
        else
            emit CpusTurn();
    }
    else
    {
        if ( player == 0 )
            emit PlayersTurn();
        else
            emit CpusTurn();
    }
}
