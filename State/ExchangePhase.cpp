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
    // Initialize member variables.
    cardsTransferred = 0;
    exchangeButton   = button;

    // Initialize the state machine.
    stateMachine  = new QStateMachine();

    // Initialize the states within the state machine.
    playerDiscard = new QState(stateMachine);
    playerDraw    = new QState(stateMachine);
    cpuProcessing = new QState(stateMachine);
    cpuDiscard    = new QState(stateMachine);
    cpuDraw       = new QState(stateMachine);
    finalState    = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerDiscard);

    // Setup the transitions from playerDiscard.
    playerDiscard->addTransition(this,  SIGNAL(TransitionState()), playerDraw);

    // Setup the transitions from playerDraw.
    playerDraw->addTransition(   this, SIGNAL(TransitionState()),
                                 cpuProcessing);

    // Setup the transitions from cpuProcessing.
    cpuProcessing->addTransition(this,  SIGNAL(AIProcessingComplete()),
                                 cpuDiscard);

    // Setup the transitions from cpuDiscard.
    cpuDiscard->addTransition(   this,  SIGNAL(TransitionState()), cpuDraw);

    // Setup the transitions from cpuDraw.
    cpuDraw->addTransition(      this,  SIGNAL(TransitionState()), finalState);

    // Setup the work done in each state.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void ExchangePhase::onEntry(QEvent*)
{
    stateMachine->start();
    emit SetUI(Scene::EXCHANGE);
    emit UpdateAI();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void ExchangePhase::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// ConnectSignals - Setup the work done in each state along with aadditional
//                  necessary signals.
//------------------------------------------------------------------------------
void ExchangePhase::ConnectSignals(void)
{
    // Set the cards to be selectable when required.
    connect(playerDiscard,  SIGNAL(entered()), this,
            SLOT(SignalEnableCardsSelectable()));
    connect(playerDiscard,  SIGNAL(exited()),  this,
            SLOT(SignalDisableCardsSelectable()));

    connect(this, SIGNAL(TransferComplete(int)),
            this, SLOT(InformTransferComplete(int)));

    // Setup the work done in each state.
    connect(this, SIGNAL(ExecuteExchange()),
            this, SLOT(PlayerDiscard()));
    connect(playerDraw,     SIGNAL(entered()), this, SLOT(PlayerDraw()));
    connect(cpuProcessing,  SIGNAL(entered()), this, SLOT(CpuProcessing()));
    connect(cpuDiscard,     SIGNAL(entered()), this, SLOT(CpuDiscard()));
    connect(cpuDraw,        SIGNAL(entered()), this, SLOT(CpuDraw()));

    connect(stateMachine,   SIGNAL(finished()), this,
            SIGNAL(ExchangePhaseFinished()));
}


//------------------------------------------------------------------------------
// SignalEnableCardsSelectable - Send a signal to enable card selection.
//------------------------------------------------------------------------------
void ExchangePhase::SignalEnableCardsSelectable(void)
{
    emit SetCardsSelectable(true, 5);
}


//------------------------------------------------------------------------------
// SignalDisableCardsSelectable - Send a signal to disable card selection.
//------------------------------------------------------------------------------
void ExchangePhase::SignalDisableCardsSelectable(void)
{
    emit SetCardsSelectable(false, 0);
}


//------------------------------------------------------------------------------
// InformTransferComplete - Set the number of cards discarded last and inform
//                          this state that a card transfer has finished.
//------------------------------------------------------------------------------
void ExchangePhase::InformTransferComplete(int numOfCardsTransferred)
{
    cardsTransferred = numOfCardsTransferred;
    emit TransitionState();
}


//------------------------------------------------------------------------------
// PlayerDiscard - Player discards selected cards.
//------------------------------------------------------------------------------
void ExchangePhase::PlayerDiscard(void)
{
    emit RequestCardTransfer(CardArray::PLAYERHAND, CardArray::PLAYERDISCARDS,
                             0, true);
}


//------------------------------------------------------------------------------
// PlayerDraw - Player draws new cards from the talon.
//------------------------------------------------------------------------------
void ExchangePhase::PlayerDraw(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::PLAYERHAND,
                             cardsTransferred, false);
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
    emit RequestCardTransfer(CardArray::CPUHAND, CardArray::CPUDISCARDS,
                             0, true);
}


//------------------------------------------------------------------------------
// CpuDraw - Cpu draws new cards from the talon.
//------------------------------------------------------------------------------
void ExchangePhase::CpuDraw(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::CPUHAND,
                             cardsTransferred, false);
}
