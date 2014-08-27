//------------------------------------------------------------------------------
// Filename: ExchangePhase.cpp
// Description: Represents the exchange phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "ExchangePhase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ExchangePhase::ExchangePhase(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
ExchangePhase::ExchangePhase(ExchangePhase&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
ExchangePhase::~ExchangePhase(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void ExchangePhase::Initialize(QPushButton* button)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize member variable.
    cardsTransferred = 0;

    // Initialize the states within the state machine.
    QState*      playerDiscard      = new QState(stateMachine);
    QState*      playerDraw         = new QState(stateMachine);
    QState*      cpuProcessing      = new QState(stateMachine);
    QState*      cpuDiscard         = new QState(stateMachine);
    QState*      cpuDraw            = new QState(stateMachine);
    QFinalState* finalState         = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerDiscard);

    // Setup the transitions from playerDiscard.
    playerDiscard->addTransition(this,  SIGNAL(TransferComplete()), playerDraw);

    // Setup the transitions from playerDraw.
    playerDraw->addTransition(   this, SIGNAL(TransferComplete()),
                                 cpuProcessing);

    // Setup the transitions from cpuDiscard.
    cpuProcessing->addTransition(this,  SIGNAL(AIProcessingComplete()),
                                 cpuDiscard);

    // Setup the transitions from cpuDiscard.
    cpuDiscard->addTransition(   this,  SIGNAL(TransferComplete()), cpuDraw);

    // Setup the transitions from cpuDraw.
    cpuDraw->addTransition(      this,  SIGNAL(TransferComplete()), finalState);

    // Set the cards to be selectable when required.
    connect(playerDiscard,     SIGNAL(entered()),  this,
            SLOT(SignalEnableCardsSelectable()));
    connect(playerDiscard,     SIGNAL(exited()),   this,
            SLOT(SignalDisableCardsSelectable()));

    // Setup the work done in each state.
    connect(button,        SIGNAL(clicked()), this, SLOT(PlayerDiscard()));
    connect(playerDraw,    SIGNAL(entered()), this, SLOT(PlayerDraw()));
    connect(cpuProcessing, SIGNAL(entered()), this, SLOT(CpuProcessing()));
    connect(cpuDiscard,    SIGNAL(entered()), this, SLOT(CpuDiscard()));
    connect(cpuDraw,       SIGNAL(entered()), this, SLOT(CpuDraw()));

    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(ExchangePhaseFinished()));
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void ExchangePhase::onEntry(QEvent*)
{
    stateMachine->start();

    emit UpdateAI();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void ExchangePhase::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// CallTransferComplete - Inform the state machine that a card transfer has been
//                        completed.
//------------------------------------------------------------------------------
void ExchangePhase::CallTransferComplete(void)
{
    emit TransferComplete();
}


//------------------------------------------------------------------------------
// SetNumCardsTransferred - Set the number of cards discarded last.
//------------------------------------------------------------------------------
void ExchangePhase::SetNumCardsTransferred(int numCardsTransferred)
{
    cardsTransferred = numCardsTransferred;
}


//------------------------------------------------------------------------------
// SignalEnableCardsSelectable - Send a signal to enable card selection.
//------------------------------------------------------------------------------
void ExchangePhase::SignalEnableCardsSelectable(void)
{
    emit RequestCardsSelectable(true, 5);
}


//------------------------------------------------------------------------------
// SignalDisableCardsSelectable - Send a signal to disable card selection.
//------------------------------------------------------------------------------
void ExchangePhase::SignalDisableCardsSelectable(void)
{
    emit RequestCardsSelectable(false, 0);
}


//------------------------------------------------------------------------------
// CallAIProcessingComplete - Informs this class to emit an AIProcessingComplete
//                            signal.
//------------------------------------------------------------------------------
void ExchangePhase::CallAIProcessingComplete(void)
{
    emit AIProcessingComplete();
}


//------------------------------------------------------------------------------
// PlayerDiscard - Player discards selected cards.
//------------------------------------------------------------------------------
void ExchangePhase::PlayerDiscard(void)
{
    emit RequestSelectedCardsTransfer(CardArray::PLAYERHAND,
                                      CardArray::PLAYERDISCARDS);
}


//------------------------------------------------------------------------------
// PlayerDraw - Player draws new cards from the talon.
//------------------------------------------------------------------------------
void ExchangePhase::PlayerDraw(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::PLAYERHAND,
                             cardsTransferred);
}


//------------------------------------------------------------------------------
// CpuProcessing - Cpu decides what cards to discard.
//------------------------------------------------------------------------------
void ExchangePhase::CpuProcessing(void)
{
    emit SignalAI(AI::DISCARD);
}


//------------------------------------------------------------------------------
// CpuDiscard - Cpu discards selected cards.
//------------------------------------------------------------------------------
void ExchangePhase::CpuDiscard(void)
{
    emit RequestSelectedCardsTransfer(CardArray::CPUHAND,
                                      CardArray::CPUDISCARDS);
}


//------------------------------------------------------------------------------
// CpuDraw - Cpu draws new cards from the talon.
//------------------------------------------------------------------------------
void ExchangePhase::CpuDraw(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::CPUHAND,
                             cardsTransferred);
}
