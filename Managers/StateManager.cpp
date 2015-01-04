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

    // Allocate memory to the phases and initialize them.
    elderSelect = new ElderSelect(stateMachine);
    elderSelect->Initialize();

    dealPhase = new DealPhase(stateMachine);
    dealPhase->Initialize();

    exchangePhase = new ExchangePhase(stateMachine);
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase(stateMachine);
    declarationPhase->Initialize();

    trickPhase = new TrickPhase(stateMachine);
    trickPhase->Initialize();

    summary = new Summary(stateMachine);
    summary->Initialize();

    // Set the initial state for the state machine.
    stateMachine->setInitialState(elderSelect);

    // Setup the transitions between the states.
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

    // Connect the various signals.
    ConnectSignals();

    // Execute the state machine.
    stateMachine->start();
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
    QObject::connect(this,
                     SIGNAL(SummaryComplete()),
                     summary,
                     SIGNAL(SummaryComplete()));
}
