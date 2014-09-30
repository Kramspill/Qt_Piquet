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
void StateManager::Initialize(QPushButton* button,  QPushButton* button2,
                              QPushButton* button3, QPushButton* button4)
{
    // Setup the state machine of the Game.
    stateMachine = new QStateMachine();

    // Allocate memory to the phases and initialize them.
    dealPhase = new DealPhase(stateMachine);
    dealPhase->Initialize(button);

    exchangePhase = new ExchangePhase(stateMachine);
    exchangePhase->Initialize(button2);

    declarationPhase = new DeclarationPhase(stateMachine);
    declarationPhase->Initialize(button3, button4);

    /*
    trickPhase = new TrickPhase();
    trickPhase->Initialize();
    */

    // Set the initial state for the state machine.
    stateMachine->setInitialState(dealPhase);

    // Setup the transitions between the states.
    dealPhase->addTransition(dealPhase, SIGNAL(DealPhaseFinished()),
                             exchangePhase);
    exchangePhase->addTransition(exchangePhase,
                                 SIGNAL(ExchangePhaseFinished()),
                                 declarationPhase);
    /*
    declarationPhase->addTransition(SomeObject, SIGNAL(SomeSignal()),
                                    trickPhase);
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
                     SIGNAL(RequestDialog(Dialog::DialogType)),
                     this,
                     SIGNAL(RequestDialog(Dialog::DialogType)));

    QObject::connect(dealPhase,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)));

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

    // Connect signals to/fom the declaration phase state.
    /*QObject::connect(this,
                     SIGNAL(SignalValidSelection()),
                     declarationPhase,
                     SLOT(ValidSelection()));*/
    QObject::connect(declarationPhase,
                     SIGNAL(SetCardsSelectable(bool, int)),
                     this,
                     SIGNAL(SetCardsSelectable(bool, int)));
    QObject::connect(declarationPhase,
                     SIGNAL(DeclareSelection(CardArray::SelectionType)),
                     this,
                     SIGNAL(DeclareSelection(CardArray::SelectionType)));
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
}
