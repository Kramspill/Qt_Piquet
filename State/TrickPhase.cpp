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
    playTricks = new QState(stateMachine);
    finalState = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playTricks);

    // Setup the transitions from the playTricks state.
    playTricks->addTransition(this, SIGNAL(TricksComplete()), finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void TrickPhase::Destroy(void)
{
    delete playTricks;      playTricks   = 0;
    delete finalState;      finalState   = 0;
    delete stateMachine;    stateMachine = 0;
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void TrickPhase::onEntry(QEvent*)
{
    currentPhase = TRICK;

    if ( !restarting )
        stateMachine->start();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void TrickPhase::onExit(QEvent*)
{
    if ( stateMachine->isRunning() )
        stateMachine->stop();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void TrickPhase::ConnectSignals(void)
{
    connect(playTricks, SIGNAL(entered()), this, SLOT(PlayTricks()));

    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(TrickPhaseFinished()));
}

//------------------------------------------------------------------------------
// PlayTricks - Tricks are played out.
//------------------------------------------------------------------------------
void TrickPhase::PlayTricks(void)
{
    int count = 11;

    while ( count > 0 )
    {
        if ( trickWinner == PLAYER1 )
        {
            if ( !restarting )
                emit PlayTrick(PLAYER1);

            if ( !restarting )
                emit PlayTrick(PLAYER2);
        }
        else
        {
            if ( !restarting )
                emit PlayTrick(PLAYER2);

            if ( !restarting )
                emit PlayTrick(PLAYER1);
        }

        count--;
    }

    emit TricksComplete();
}
