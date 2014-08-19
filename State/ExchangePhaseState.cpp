//------------------------------------------------------------------------------
// Filename: ExchangePhaseState.cpp
// Description: Represents the exchange phase in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "ExchangePhaseState.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ExchangePhaseState::ExchangePhaseState(QState* parent) :
    QState(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
ExchangePhaseState::ExchangePhaseState(ExchangePhaseState&) :
    QState()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
ExchangePhaseState::~ExchangePhaseState(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize and execute the internal state machine of this class.
//------------------------------------------------------------------------------
void ExchangePhaseState::Initialize(QPushButton* button)
{
    // Initialize the state machine.
    stateMachine = new QStateMachine();

    // Initialize member variable.
    cardsTransferred = 0;

    // Initialize the states within the state machine.
    QState*      playerDiscard      = new QState(stateMachine);
    QState*      playerDraw         = new QState(stateMachine);
    QState*      cpuDiscard         = new QState(stateMachine);
    QState*      cpuDraw            = new QState(stateMachine);
    QFinalState* finalState         = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerDiscard);

    // Setup the transitions from playerDiscard.
    playerDiscard->addTransition(this,  SIGNAL(TransferComplete()), playerDraw);

    // Setup the transitions from playerDraw.
    playerDraw->addTransition(   this,  SIGNAL(TransferComplete()), cpuDiscard);

    // Setup the transitions from cpuDiscard.
    cpuDiscard->addTransition(   this,  SIGNAL(TransferComplete()), cpuDraw);

    // Setup the transitions from cpuDraw.
    cpuDraw->addTransition(      this,  SIGNAL(TransferComplete()), finalState);

    // Setup the work done in each state.
    connect(button,            SIGNAL(clicked()),  this,
            SLOT(PlayerDiscards()));
    connect(playerDiscard,     SIGNAL(entered()),  this,
            SLOT(SignalEnableCardsSelectable()));
    connect(playerDiscard,     SIGNAL(exited()),   this,
            SLOT(SignalDisableCardsSelectable()));
    connect(playerDraw,        SIGNAL(entered()),  this,
            SLOT(PlayerDrawFromTalon()));
    connect(cpuDiscard,        SIGNAL(entered()),  this,
            SLOT(CpuDiscards()));
    connect(cpuDraw,           SIGNAL(entered()),  this,
            SLOT(CpuDrawFromTalon()));
    connect(stateMachine,      SIGNAL(finished()), this,
            SIGNAL(ExchangePhaseFinished()));
}


//------------------------------------------------------------------------------
// onEntry - Override of QState::onEntry.
//------------------------------------------------------------------------------
void ExchangePhaseState::onEntry(QEvent*)
{
    stateMachine->start();
}


//------------------------------------------------------------------------------
// onExit - Override of QState::onExit.
//------------------------------------------------------------------------------
void ExchangePhaseState::onExit(QEvent*)
{

}


//------------------------------------------------------------------------------
// CallTransferComplete - Inform the state machine that a card transfer has been
//                        completed.
//------------------------------------------------------------------------------
void ExchangePhaseState::CallTransferComplete(void)
{
    emit TransferComplete();
}


//------------------------------------------------------------------------------
// SetNumCardsTransferred - Set the number of player cards discarded.
//------------------------------------------------------------------------------
void ExchangePhaseState::SetNumCardsTransferred(int numCardsTransferred)
{
    cardsTransferred = numCardsTransferred;
}


//------------------------------------------------------------------------------
// SignalEnableCardsSelectable - Send a signal to enable card selection.
//------------------------------------------------------------------------------
void ExchangePhaseState::SignalEnableCardsSelectable(void)
{
    emit RequestCardsSelectable(true);
}


//------------------------------------------------------------------------------
// SignalDisableCardsSelectable - Send a signal to disable card selection.
//------------------------------------------------------------------------------
void ExchangePhaseState::SignalDisableCardsSelectable(void)
{
    emit RequestCardsSelectable(false);
}


//------------------------------------------------------------------------------
// PlayerDiscards - Player discards selected cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::PlayerDiscards(void)
{
    emit RequestSelectedCardsTransfer(CardArray::PLAYERHAND,
                                      CardArray::PLAYERDISCARDS);
}


//------------------------------------------------------------------------------
// PlayerDrawFromTalon - Player draws new cards from the talon.
//------------------------------------------------------------------------------
void ExchangePhaseState::PlayerDrawFromTalon(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::PLAYERHAND,
                             cardsTransferred);
}


//------------------------------------------------------------------------------
// CpuDiscards - Cpu discards selected cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::CpuDiscards(void)
{
    emit RequestCardTransfer(CardArray::CPUHAND, CardArray::CPUDISCARDS, 3);
}


//------------------------------------------------------------------------------
// TransferCpuCards - Transfer the cpu's cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::CpuDrawFromTalon(void)
{
    emit RequestCardTransfer(CardArray::TALON, CardArray::CPUHAND, 3);
}
