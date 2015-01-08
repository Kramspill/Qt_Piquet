//------------------------------------------------------------------------------
// Filename: StateManager.cpp
// Description: Manager for the various states in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "StateManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
StateManager::StateManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
StateManager::StateManager(StateManager&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
StateManager::~StateManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the phases that represent the states of the game.
//------------------------------------------------------------------------------
void StateManager::Initialize(void)
{
    // Setup the state machine of the game.
    stateMachine = new QStateMachine();

    // Top level state.
    topLevelState = new QState(stateMachine);

    // Allocate memory to the phases and initialize them.
    elderSelect = new ElderSelect(topLevelState);
    elderSelect->Initialize();

    dealPhase = new DealPhase(topLevelState);
    dealPhase->Initialize();

    exchangePhase = new ExchangePhase(topLevelState);
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase(topLevelState);
    declarationPhase->Initialize();

    trickPhase = new TrickPhase(topLevelState);
    trickPhase->Initialize();

    summary = new Summary(topLevelState);
    summary->Initialize();

    finalState = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    topLevelState->setInitialState(elderSelect);
    stateMachine->setInitialState(topLevelState);

    // Setup the transitions between the states.
    topLevelState->addTransition(   this,
                                    SIGNAL(ResetState()),
                                    finalState);
    elderSelect->addTransition(     elderSelect,
                                    SIGNAL(ElderSelectFinished()),
                                    dealPhase);
    dealPhase->addTransition(       dealPhase,
                                    SIGNAL(DealPhaseFinished()),
                                    exchangePhase);
    exchangePhase->addTransition(   exchangePhase,
                                    SIGNAL(ExchangePhaseFinished()),
                                    declarationPhase);
    declarationPhase->addTransition(declarationPhase,
                                    SIGNAL(DeclarationPhaseFinished()),
                                    trickPhase);
    trickPhase->addTransition(      trickPhase,
                                    SIGNAL(TrickPhaseFinished()),
                                    summary);
    summary->addTransition(         summary,
                                    SIGNAL(NewGame()),
                                    elderSelect);
    summary->addTransition(         summary,
                                    SIGNAL(NextHand()),
                                    dealPhase);

    // Connect the various signals.
    ConnectSignals();

    // Execute the state machine.
    stateMachine->start();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void StateManager::Destroy(void)
{
    elderSelect->Destroy();
    dealPhase->Destroy();
    exchangePhase->Destroy();
    declarationPhase->Destroy();
    trickPhase->Destroy();
    summary->Destroy();

    delete elderSelect;         elderSelect      = 0;
    delete dealPhase;           dealPhase        = 0;
    delete exchangePhase;       exchangePhase    = 0;
    delete declarationPhase;    declarationPhase = 0;
    delete trickPhase;          trickPhase       = 0;
    delete summary;             summary          = 0;
    delete stateMachine;        stateMachine     = 0;
}


//------------------------------------------------------------------------------
// Reset - Reset the state manager.
//------------------------------------------------------------------------------
void StateManager::Reset(void)
{
    emit ResetState();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void StateManager::ConnectSignals(void)
{
    // Connect signals to/from the Elder select state.
    QObject::connect(elderSelect,
                     SIGNAL(ExecuteElderSelect()),
                     this,
                     SIGNAL(ExecuteElderSelect()));
    QObject::connect(this,
                     SIGNAL(ElderSelectComplete()),
                     elderSelect,
                     SIGNAL(ElderSelectComplete()));

    // Connect signals to/from the Deal phase state.
    QObject::connect(dealPhase,
                     SIGNAL(ExecuteDeal()),
                     this,
                     SIGNAL(ExecuteDeal()));
    QObject::connect(this,
                     SIGNAL(DealComplete()),
                     dealPhase,
                     SIGNAL(DealComplete()));

    // Connect signals to/from the Exchange phase state.
    QObject::connect(exchangePhase,
                     SIGNAL(ExecuteExchange()),
                     this,
                     SIGNAL(ExecuteExchange()));
    QObject::connect(this,
                     SIGNAL(ExchangeComplete()),
                     exchangePhase,
                     SIGNAL(ExchangeComplete()));

    // Connect signals to/from the Declaration phase state.
    QObject::connect(declarationPhase,
                     SIGNAL(AnnounceDeclaration(State, PlayerNum)),
                     this,
                     SIGNAL(AnnounceDeclaration(State, PlayerNum)));
    QObject::connect(declarationPhase,
                     SIGNAL(PlayTrick(PlayerNum)),
                     this,
                     SIGNAL(PlayTrick(PlayerNum)));

    // Connect signals to/from the Trick phase state.
    QObject::connect(trickPhase,
                     SIGNAL(PlayTrick(PlayerNum)),
                     this,
                     SIGNAL(PlayTrick(PlayerNum)));

    // Connect signals to/from the Summary state.
    QObject::connect(summary,
                     SIGNAL(ExecuteSummary()),
                     this,
                     SIGNAL(ExecuteSummary()));

    // Connect signals to/from the final state.
    QObject::connect(stateMachine,
                     SIGNAL(finished()),
                     this,
                     SLOT(Test()));
}


//------------------------------------------------------------------------------
// RestartStateMachine - Reset the state machine of this class.
//------------------------------------------------------------------------------
void StateManager::RestartStateMachine(void)
{
    Destroy();
    Initialize();
}
