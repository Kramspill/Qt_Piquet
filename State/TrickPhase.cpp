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
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the states within the state machine.
    awaitingSignal = new QState(stateMachine);
    player1Trick   = new QState(stateMachine);
    player2Trick   = new QState(stateMachine);
    finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(awaitingSignal);

    // Setup the transitions from the awaitingSignal state.
    awaitingSignal->addTransition(this,
                                  SIGNAL(Player1PlayTrick()),
                                  player1Trick);
    awaitingSignal->addTransition(this,
                                  SIGNAL(Player2PlayTrick()),
                                  player2Trick);

    // Setup the transitions from the player1Trick state.
    player1Trick->addTransition(  this,
                                  SIGNAL(Player2PlayTrick()),
                                  player2Trick);
    player1Trick->addTransition(  this,
                                  SIGNAL(AllTricksComplete()),
                                  finalState);

    // Setup the transitions from the player1Trick state.
    player2Trick->addTransition(  this,
                                  SIGNAL(Player1PlayTrick()),
                                  player1Trick);
    player2Trick->addTransition(  this,
                                  SIGNAL(AllTricksComplete()),
                                  finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void TrickPhase::onEntry(QEvent*)
{
    currentPhase = TRICK;

    stateMachine->start();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void TrickPhase::ConnectSignals(void)
{
    connect(player1Trick, SIGNAL(entered()),  this, SLOT(Player1Trick()));
    connect(player2Trick, SIGNAL(entered()),  this, SLOT(Player2Trick()));

    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(TrickPhaseFinished()));
}


//------------------------------------------------------------------------------
// Player1Trick - Player 1 plays a trick.
//------------------------------------------------------------------------------
void TrickPhase::Player1Trick(void)
{
    emit PlayTrick(1);
}


//------------------------------------------------------------------------------
// Player2Trick - Player 2 plays a trick.
//------------------------------------------------------------------------------
void TrickPhase::Player2Trick(void)
{
    emit PlayTrick(2);
}
