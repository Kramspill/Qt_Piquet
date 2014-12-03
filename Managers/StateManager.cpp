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
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhase = new DealPhase(stateMachine);
    dealPhase->Initialize();

    exchangePhase = new ExchangePhase(stateMachine);
    exchangePhase->Initialize();

    declarationPhase = new DeclarationPhase(stateMachine);
    declarationPhase->Initialize();

    trickPhase = new TrickPhase();
    trickPhase->Initialize();

    // Set the initial state for the state machine.
    stateMachine->setInitialState(dealPhase);

    // Setup the transitions between the states.
    dealPhase->addTransition(dealPhase, SIGNAL(DealPhaseFinished()),
                             exchangePhase);
    exchangePhase->addTransition(exchangePhase,
                                 SIGNAL(ExchangePhaseFinished()),
                                 declarationPhase);
    declarationPhase->addTransition(declarationPhase,
                                    SIGNAL(DeclarationPhaseFinished()),
                                    trickPhase);
    /*
    trickPhase->addTransition(SomeObject, SIGNAL(SomeSignal()),
                              playSummaryState);
    */

    // Connect the various signals.
    ConnectSignals();

    stateMachine->start();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void StateManager::ConnectSignals(void)
{
    // Connect signals to/from the deal phase state.
    QObject::connect(this,
                     SIGNAL(ExecuteDeal()),
                     dealPhase,
                     SIGNAL(ExecuteDeal()));

    QObject::connect(dealPhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)));

    QObject::connect(dealPhase,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SIGNAL(SetUI(Scene::PhaseType)));

    // Connect signals to/fom the exchange phase state.
    QObject::connect(exchangePhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)));
    QObject::connect(exchangePhase,
                     SIGNAL(SetCardsSelectable(bool, int)),
                     this,
                     SIGNAL(SetCardsSelectable(bool, int)));
    QObject::connect(exchangePhase,
                     SIGNAL(SignalAI(AI::AIAction)),
                     this,
                     SIGNAL(SignalAI(AI::AIAction)));
    QObject::connect(exchangePhase,
                     SIGNAL(UpdateAI()),
                     this,
                     SIGNAL(UpdateAI()));

    QObject::connect(exchangePhase,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SIGNAL(SetUI(Scene::PhaseType)));

    QObject::connect(this,
                     SIGNAL(ExecuteExchange()),
                     exchangePhase,
                     SIGNAL(ExecuteExchange()));

    // Connect signals to/fom the declaration phase state.
    QObject::connect(declarationPhase,
                     SIGNAL(SetCardsSelectable(bool, int)),
                     this,
                     SIGNAL(SetCardsSelectable(bool, int)));

    QObject::connect(declarationPhase,
                     SIGNAL(SetCardsMoveable(bool)),
                     this,
                     SIGNAL(SetCardsMoveable(bool)));

    QObject::connect(declarationPhase,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SIGNAL(SetUI(Scene::PhaseType)));

    QObject::connect(declarationPhase,
                     SIGNAL(DeclareSelection(CardArray::SelectionType)),
                     this,
                     SIGNAL(DeclareSelection(CardArray::SelectionType)));

    QObject::connect(declarationPhase,
                     SIGNAL(SignalAI(AI::AIAction)),
                     this,
                     SIGNAL(SignalAI(AI::AIAction)));

    QObject::connect(declarationPhase,
                     SIGNAL(UpdateAI()),
                     this,
                     SIGNAL(UpdateAI()));

    QObject::connect(declarationPhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)));

    // Connect signals to/fom the trick phase state.
    QObject::connect(trickPhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)));

    QObject::connect(trickPhase,
                     SIGNAL(SignalAI(AI::AIAction)),
                     this,
                     SIGNAL(SignalAI(AI::AIAction)));

    QObject::connect(trickPhase,
                     SIGNAL(UpdateAI()),
                     this,
                     SIGNAL(UpdateAI()));

    QObject::connect(trickPhase,
                     SIGNAL(SetCardsMoveable(bool)),
                     this,
                     SIGNAL(SetCardsMoveable(bool)));

    QObject::connect(trickPhase,
                     SIGNAL(CheckTrick(bool)),
                     this,
                     SIGNAL(CheckTrick(bool)));

    QObject::connect(this,
                     SIGNAL(TrickResult(bool)),
                     trickPhase,
                     SLOT(TrickResult(bool)));
}


//------------------------------------------------------------------------------
// SignalTransferComplete - Inform the current state that a transfer request has
//                          finished.
//------------------------------------------------------------------------------
void StateManager::SignalTransferComplete(int numOfCardsTransferred)
{
    if ( stateMachine->configuration().contains(dealPhase) )
    {
        emit dealPhase->TransferComplete();
    }
    else if ( stateMachine->configuration().contains(exchangePhase) )
    {
        emit exchangePhase->TransferComplete(numOfCardsTransferred);
    }
    else if ( stateMachine->configuration().contains(declarationPhase) )
    {
        emit declarationPhase->TransferComplete();
    }
    else if ( stateMachine->configuration().contains(trickPhase) )
    {
        trickPhase->PlayerMoveFinished(numOfCardsTransferred);
    }
}


//------------------------------------------------------------------------------
// AIProcessingComplete - Inform the current state that the ai has finished
//                        processing a request.
//------------------------------------------------------------------------------
void StateManager::AIProcessingComplete(void)
{
    if ( stateMachine->configuration().contains(exchangePhase) )
    {
        emit exchangePhase->AIProcessingComplete();
    }
    else if ( stateMachine->configuration().contains(declarationPhase) )
    {
        declarationPhase->PhaseComplete();
    }
}
