//------------------------------------------------------------------------------
// Filename: DeclarationPhase.cpp
// Description: Represents the declaration phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "DeclarationPhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
DeclarationPhase::DeclarationPhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
DeclarationPhase::DeclarationPhase(DeclarationPhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
DeclarationPhase::~DeclarationPhase(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void DeclarationPhase::Initialize(QPushButton* button, QPushButton* button2)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Assign this state's declareButton for easy access.
    declareButton = button;

    // Initialize the states within the state machine.
    QState*      playerPoint    = new QState(stateMachine);
    QState*      playerSequence = new QState(stateMachine);
    QState*      playerSet      = new QState(stateMachine);
    QState*      cpuPoint       = new QState(stateMachine);
    QState*      cpuSequence    = new QState(stateMachine);
    QState*      cpuSet         = new QState(stateMachine);
    QState*      initialTrick   = new QState(stateMachine);
    QFinalState* finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerPoint);

    // Setup the transitions from playerPoint.
    playerPoint->addTransition( this, SIGNAL(PointComplete()),  playerSequence);

    // Setup the transitions from playerSequence.
    playerSequence->addTransition(this, SIGNAL(SequenceComplete()), playerSet);

    // Setup the transitions from playerSet.
    playerSet->addTransition(   this, SIGNAL(SetComplete()),      initialTrick);

    // Setup the transitions from cpuPoint.
    cpuPoint->addTransition(    this, SIGNAL(PointComplete()),    cpuSequence);
    cpuPoint->addTransition(    this, SIGNAL(SequenceLost()),     cpuSequence);
    cpuPoint->addTransition(    this, SIGNAL(SetLost()),          cpuSet);
    cpuPoint->addTransition(    this, SIGNAL(NoMoreLosses()),     finalState);

    // Setup the transitions from cpuSequence.
    cpuSequence->addTransition( this, SIGNAL(SequenceComplete()), cpuSet);
    cpuSequence->addTransition( this, SIGNAL(SetLost()),          cpuSet);
    cpuSequence->addTransition( this, SIGNAL(NoMoreLosses()),     finalState);

    // Setup the transitions from cpuSet.
    cpuSet->addTransition(      this, SIGNAL(SetComplete()),      initialTrick);
    cpuSet->addTransition(      this, SIGNAL(NoMoreLosses()),     finalState);

    // Setup the transitions from initialTrick.
    initialTrick->addTransition(this, SIGNAL(NoLosses()),         finalState);
    initialTrick->addTransition(this, SIGNAL(PointLost()),        cpuPoint);
    initialTrick->addTransition(this, SIGNAL(SequenceLost()),     cpuSequence);
    initialTrick->addTransition(this, SIGNAL(SetLost()),          cpuSet);

    // Setup the work done in each state.
    connect(playerPoint,    SIGNAL(entered()), this, SLOT(PlayerPoint()));
    connect(playerSequence, SIGNAL(entered()), this, SLOT(PlayerSequence()));
    connect(playerSet,      SIGNAL(entered()), this, SLOT(PlayerSet()));
    connect(cpuPoint,       SIGNAL(entered()), this, SLOT(CpuPoint()));
    connect(cpuSequence,    SIGNAL(entered()), this, SLOT(CpuSequence()));
    connect(cpuSet,         SIGNAL(entered()), this, SLOT(CpuSet()));
    connect(initialTrick,   SIGNAL(entered()), this, SLOT(InitialTrick()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(DeclarationPhaseFinished()));
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DeclarationPhase::onEntry(QEvent*)
{
    stateMachine->start();
    emit RequestCardsSelectable(true, 12);
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void DeclarationPhase::onExit(QEvent*)
{
    emit RequestCardsSelectable(false, 0);
}


//------------------------------------------------------------------------------
// ValidSelection - Called in response to a correct selection being made.
//------------------------------------------------------------------------------
void DeclarationPhase::ValidSelection(void)
{
    // NOTE: either at this point, will check with the AI, OR
    // when this signal goes up the chain and reaches GameManager, we'll call
    // the AI check there and have the AI respond.
    emit SignalValidSelection();
}


//------------------------------------------------------------------------------
// PlayerPoint - Function that performs the required operations for the
//               playerPoint state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerPoint(void)
{
    // Ensure the declare button is disconnected from all signals.
    disconnect(declareButton, 0, 0, 0);

    // Reconnect the button to perform the desired checks when in this state.
    connect(declareButton, SIGNAL(clicked()), this,
            SIGNAL(RequestCheckSelection(CardArray::POINT)));

}


//------------------------------------------------------------------------------
// PlayerSequence - Function that performs the required operations for the
//                  playerSequence state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerSequence(void)
{
    // Ensure the declare button is disconnected from all signals.
    disconnect(declareButton, 0, 0, 0);

    // Reconnect the button to perform the desired checks when in this state.
    connect(declareButton, SIGNAL(clicked()), this,
            SIGNAL(RequestCheckSelection(CardArray::SEQUENCE)));
}


//------------------------------------------------------------------------------
// PlayerSet - Function that performs the required operations for the playerSet
//             state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerSet(void)
{
    // Ensure the declare button is disconnected from all signals.
    disconnect(declareButton, 0, 0, 0);

    // Reconnect the button to perform the desired checks when in this state.
    connect(declareButton, SIGNAL(clicked()), this,
            SIGNAL(RequestCheckSelection(CardArray::SET)));
}


//------------------------------------------------------------------------------
// CpuPoint - Function that performs the required operations for the cpuPoint
//            state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuPoint(void)
{

}


//------------------------------------------------------------------------------
// CpuSequence - Function that performs the required operations for the
//               cpuSequence state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuSequence(void)
{

}


//------------------------------------------------------------------------------
// CpuSet - Function that performs the required operations for the cpuSet state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuSet(void)
{

}


//------------------------------------------------------------------------------
// InitialTrick - Function that performs the required operations for the
//                initialTrick state.
//------------------------------------------------------------------------------
void DeclarationPhase::InitialTrick(void)
{

}
