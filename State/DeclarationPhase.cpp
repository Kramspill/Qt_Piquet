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

    // Initialize the states within the state machine.
    elderDeclarations   = new QState(stateMachine);
    elderTrick          = new QState(stateMachine);
    youngerDeclarations = new QState(stateMachine);
    youngerTrick        = new QState(stateMachine);
    finalState          = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(elderDeclarations);

    // Setup the transitions from the elderDeclarations state.
    elderDeclarations->addTransition(this,
                                     SIGNAL(DeclarationsComplete()),
                                     elderTrick);

    // Setup the transitions from the elderTrick state.
    elderTrick->addTransition(this,
                              SIGNAL(TrickComplete()), youngerDeclarations);

    // Setup the transitions from the elderTrick state.
    youngerDeclarations->addTransition(this,
                                       SIGNAL(DeclarationsComplete()),
                                       youngerTrick);

    // Setup the transitions from the elderTrick state.
    youngerTrick->addTransition(this, SIGNAL(TrickComplete()), finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void DeclarationPhase::onEntry(QEvent*)
{
    stateMachine->start();
}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with additional
//                  necessary signals.
//------------------------------------------------------------------------------
void DeclarationPhase::ConnectSignals(void)
{
    connect(elderDeclarations, SIGNAL(entered()),
            this,              SLOT(ElderDeclarations()));
    connect(elderTrick,   SIGNAL(entered()), this, SLOT(ElderTrick()));
    connect(youngerDeclarations, SIGNAL(entered()),
            this,                SLOT(YoungerDeclarations()));
    connect(youngerTrick, SIGNAL(entered()), this, SLOT(YoungerTrick()));

    connect(stateMachine,
            SIGNAL(finished()),
            this,
            SIGNAL(DeclarationPhaseFinished()));
}


//------------------------------------------------------------------------------
// ElderDeclarations - Elder makes their declarations.
//------------------------------------------------------------------------------
void DeclarationPhase::ElderDeclarations(void)
{
    emit AnnounceDeclaration(POINT,    elder);
    emit AnnounceDeclaration(SEQUENCE, elder);
    emit AnnounceDeclaration(SET,      elder);

    emit DeclarationsComplete();
}


//------------------------------------------------------------------------------
// ElderTrick - Elder playes their initial trick.
//------------------------------------------------------------------------------
void DeclarationPhase::ElderTrick(void)
{
    emit PlayTrick(elder);
    emit TrickComplete();
}


//------------------------------------------------------------------------------
// YoungerDeclarations - Younger makes their declarations.
//------------------------------------------------------------------------------
void DeclarationPhase::YoungerDeclarations(void)
{
    if ( declarationResults->pointWinner == younger )
        emit AnnounceDeclaration(POINT, younger);

    if ( declarationResults->sequenceWinner == younger )
        emit AnnounceDeclaration(SEQUENCE, younger);

    if ( declarationResults->setWinner == younger )
        emit AnnounceDeclaration(SET, younger);

    emit DeclarationsComplete();
}


//------------------------------------------------------------------------------
// YoungerTrick - Younger plays their initial trick.
//------------------------------------------------------------------------------
void DeclarationPhase::YoungerTrick(void)
{
    //emit PlayTrick(younger);
    //emit TrickComplete();
}
