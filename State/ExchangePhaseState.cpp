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

    // Initialize the timers for the deals to allow animation.
    playerDiscardTimer = new QTimer();
    playerDrawTimer    = new QTimer();
    cpuDiscardTimer    = new QTimer();
    cpuDrawTimer       = new QTimer();

    playerDiscardTimer->setSingleShot(true);
    playerDrawTimer->setSingleShot(true);
    cpuDiscardTimer->setSingleShot(true);
    cpuDrawTimer->setSingleShot(true);

    // Initialize the states within the state machine.
    QState*      playerExchange = new QState(stateMachine);
    QState*      cpuExchange    = new QState(stateMachine);
    QFinalState* finalState     = new QFinalState(stateMachine);

    // Set the initial state for the state machine.
    stateMachine->setInitialState(playerExchange);

    // Setup the transitions from playerExchange.
    playerExchange->addTransition(this, SIGNAL(ValidSelection()),
                                  cpuExchange);
    //playerExchange->addTransition(button, SIGNAL(ValidSelection()),
    //                              finalState);

    // Setup the transitions from cpuExchange.
    cpuExchange->addTransition(this, SIGNAL(CpuExchangeFinished()), finalState);
    //cpuExchange->addTransition(this, SIGNAL(CpuExchangeFinished()),
    //                           playerExchange);

    // Setup the work done in each state.
    connect(playerExchange, SIGNAL(entered()), this,
            SIGNAL(SignalEnableCardSelection()));
    connect(playerExchange, SIGNAL(exited()), this,
            SIGNAL(SignalDisableCardSelection()));
    connect(cpuExchange, SIGNAL(entered()), this, SLOT(ExecuteCpuExchange()));
    connect(button, SIGNAL(clicked()), this, SLOT(CheckSelection()));
    connect(stateMachine, SIGNAL(finished()), this,
            SIGNAL(ExchangePhaseFinished()));

    // Animation delay timer setup.
    connect(playerDiscardTimer, SIGNAL(timeout()), this,
            SLOT(TransferPlayerCards()));
    connect(playerDrawTimer,    SIGNAL(timeout()), this,
            SIGNAL(ValidSelection()));
    connect(cpuDiscardTimer,    SIGNAL(timeout()), this,
            SLOT(TransferCpuCards()));
    connect(cpuDrawTimer,    SIGNAL(timeout()), this,
            SIGNAL(CpuExchangeFinished()));
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
// CheckSelection - Check the user's selection of cards to exchange is valid.
//------------------------------------------------------------------------------
void ExchangePhaseState::CheckSelection(void)
{

    emit RequestSelectedCardsTransfer(CardArray::PLAYERHAND,
                                      CardArray::PLAYERDISCARDS);

    playerDiscardTimer->start(100);
}


//------------------------------------------------------------------------------
// TransferPlayerCards - Transfer the player's cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::TransferPlayerCards(void)
{
    RequestCardTransfer(CardArray::TALON, CardArray::PLAYERHAND, 5);

    playerDrawTimer->start(100);
}


//------------------------------------------------------------------------------
// ExecuteCpuExchange - Commence the cpu's turn to exchange cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::ExecuteCpuExchange(void)
{
    emit RequestCardTransfer(CardArray::CPUHAND, CardArray::CPUDISCARDS, 3);

    cpuDiscardTimer->start(100);
}


//------------------------------------------------------------------------------
// TransferCpuCards - Transfer the cpu's cards.
//------------------------------------------------------------------------------
void ExchangePhaseState::TransferCpuCards(void)
{
    RequestCardTransfer(CardArray::TALON, CardArray::CPUHAND, 3);

    cpuDrawTimer->start(100);
}
