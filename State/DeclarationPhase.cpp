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
void DeclarationPhase::Initialize(void)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize the status of each phase.
    for ( int index = 0; index < 3; index++ )
    {
        phaseStatus[index] = PENDING;
    }

    // Initialize the states within the state machine.
    playerPoint        = new QState(stateMachine);
    playerSequence     = new QState(stateMachine);
    playerSet          = new QState(stateMachine);
    cpuPoint           = new QState(stateMachine);
    cpuSequence        = new QState(stateMachine);
    cpuSet             = new QState(stateMachine);
    cpuProcessing      = new QState(stateMachine);
    playerInitialTrick = new QState(stateMachine);
    cpuInitialTrick    = new QState(stateMachine);
    finalState         = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerPoint);

    // Setup the transitions from playerPoint.
    playerPoint->addTransition(this, SIGNAL(PointComplete()),  playerSequence);

    // Setup the transitions from playerSequence.
    playerSequence->addTransition(this, SIGNAL(SequenceComplete()), playerSet);

    // Setup the transitions from playerSet.
    playerSet->addTransition(this, SIGNAL(SetComplete()), playerInitialTrick);

    // Setup the transitions from playerInitialTrick.
    playerInitialTrick->addTransition(this,
                                      SIGNAL(TransferComplete()), cpuPoint);
    //playerInitialTrick->addTransition(this,
    //                                  SIGNAL(TransferComplete()), finalState);

    // Setup the transitions from cpuPoint.
    cpuPoint->addTransition(this, SIGNAL(PointComplete()), cpuSequence);

    // Setup the transitions from cpuSequence.
    cpuSequence->addTransition(this, SIGNAL(SequenceComplete()), cpuSet);

    // Setup the transitions from cpuSet.
    cpuSet->addTransition(this, SIGNAL(SetComplete()), cpuProcessing);

    // Setup the transitions from cpuSet.
    cpuProcessing->addTransition(this, SIGNAL(AIProcessingComplete()),
                                 cpuInitialTrick);

    // Setup the transitions from cpuInitialTrick.
    cpuInitialTrick->addTransition(this, SIGNAL(TransferComplete()), finalState);
    //cpuInitialTrick->addTransition(this, SIGNAL(Losses()), playerPoint);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// PhaseComplete - Emit a signal to move to the next phase.
//------------------------------------------------------------------------------
void DeclarationPhase::PhaseComplete(void)
{
    if ( stateMachine->configuration().contains(playerPoint) )
    {
        emit PointComplete();
    }
    else if ( stateMachine->configuration().contains(playerSequence) )
    {
        emit SequenceComplete();
    }
    else if ( stateMachine->configuration().contains(playerSet) )
    {
        emit SetComplete();
    }
    else if ( stateMachine->configuration().contains(cpuProcessing) )
    {
        emit AIProcessingComplete();
    }
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DeclarationPhase::onEntry(QEvent*)
{
    stateMachine->start();
    emit SetCardsSelectable(true, 12);
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void DeclarationPhase::onExit(QEvent*)
{
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void DeclarationPhase::ConnectSignals(void)
{
    // Setup the work done in each state.
    connect(playerPoint,    SIGNAL(entered()), this, SLOT(PlayerPoint()));
    connect(playerSequence, SIGNAL(entered()), this, SLOT(PlayerSequence()));
    connect(playerSet,      SIGNAL(entered()), this, SLOT(PlayerSet()));
    connect(playerInitialTrick, SIGNAL(entered()),
            this,               SLOT(PlayerInitialTrick()));

    connect(cpuPoint,        SIGNAL(entered()), this, SLOT(CpuPoint()));
    connect(cpuSequence,     SIGNAL(entered()), this, SLOT(CpuSequence()));
    connect(cpuSet,          SIGNAL(entered()), this, SLOT(CpuSet()));
    connect(cpuProcessing,   SIGNAL(entered()), this, SLOT(CpuProcessing()));
    connect(cpuInitialTrick, SIGNAL(entered()), this, SLOT(CpuInitialTrick()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(DeclarationPhaseFinished()));
}


//------------------------------------------------------------------------------
// PlayerPoint - Function that performs the required operations for the
//               playerPoint state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerPoint(void)
{
    emit SetUI(Scene::POINT);
}


//------------------------------------------------------------------------------
// PlayerSequence - Function that performs the required operations for the
//                  playerSequence state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerSequence(void)
{
    emit SetUI(Scene::SEQUENCE);
}


//------------------------------------------------------------------------------
// PlayerSet - Function that performs the required operations for the playerSet
//             state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerSet(void)
{
    emit SetUI(Scene::SET);
}


//------------------------------------------------------------------------------
// PlayerInitialTrick - Function that performs the required operations for the
//                      playerInitialTrick state.
//------------------------------------------------------------------------------
void DeclarationPhase::PlayerInitialTrick(void)
{
    emit SetCardsSelectable(false, 0);
    emit SetCardsMoveable(true);
    emit SetUI(Scene::TRICK);
}


//------------------------------------------------------------------------------
// CpuPoint - Function that performs the required operations for the cpuPoint
//            state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuPoint(void)
{
    // For now just skip.
    emit PointComplete();
}


//------------------------------------------------------------------------------
// CpuSequence - Function that performs the required operations for the
//               cpuSequence state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuSequence(void)
{
    // For now just skip.
    emit SequenceComplete();
}


//------------------------------------------------------------------------------
// CpuSet - Function that performs the required operations for the cpuSet state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuSet(void)
{
    // For now just skip.
    emit SetComplete();
}


//------------------------------------------------------------------------------
// CpuProcessing - Function that gives the cpu time to think about it's next
//                 move.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuProcessing(void)
{
    emit UpdateAI();
    emit SignalAI(AI::TRICK);
}


//------------------------------------------------------------------------------
// CpuInitialTrick - Function that performs the required operations for the
//                   cpuInitialTrick state.
//------------------------------------------------------------------------------
void DeclarationPhase::CpuInitialTrick(void)
{
    emit RequestCardTransfer(CardArray::CPUHAND, CardArray::CPUTRICK,
                             0, true);
}
