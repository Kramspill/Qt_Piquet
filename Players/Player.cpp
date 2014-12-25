//------------------------------------------------------------------------------
// Filename: Player.cpp
// Description: Represents a player in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Player.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Player::Player(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
Player::Player(Player&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Player::~Player(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize this class.
//------------------------------------------------------------------------------
void Player::Initialize(PlayerNum num)
{
    playerNumber = num;

    ConnectSignals();
}


//------------------------------------------------------------------------------
// ExecuteDeal - Player executes a deal.
//------------------------------------------------------------------------------
void Player::ExecuteDeal(void)
{
    // Set the UI.
    emit SetUI(DEAL);

    // Wait for the user to select 'Deal'.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(BeginDeal()), loop, SLOT(quit()));
    loop->exec();

    // Begin dealing out the cards.
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::TALON,      8);

    emit DealComplete();
}


//------------------------------------------------------------------------------
// ExecuteExchange - Player executes an exchange.
//------------------------------------------------------------------------------
void Player::ExecuteExchange(void)
{
    // Set the UI.
    emit SetUI(EXCHANGE);

    // Wait for the user to select 'Exchange'.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(BeginExchange()), loop, SLOT(quit()));
    loop->exec();

    // Transfer the cards.
    emit RequestCardTransfer(CardArray::PLAYERHAND,
                             CardArray::PLAYERDISCARDS,
                             0);
    emit RequestCardTransfer(CardArray::TALON,
                             CardArray::PLAYERHAND,
                             0);

    // Inform the StateManager if all exchanges have finished.
    if ( younger == playerNumber)
        emit ExchangeComplete();
}


//------------------------------------------------------------------------------
// AnnouceDeclaration - Player prepares to make a declaration.
//------------------------------------------------------------------------------
void Player::AnnounceDeclaration(State phase)
{
    // Set the UI.
    emit SetUI(phase);

    // Wait for the user to select 'Declare' or 'Skip'.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(Declare()), loop, SLOT(quit()));
    loop->exec();
}


//------------------------------------------------------------------------------
// Respond - Player responds to a declaration.
//------------------------------------------------------------------------------
void Player::Respond(State phase)
{
    // Set the UI to the Response state.
    emit SetUI(RESPOND);

    // Wait for user to make a response.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(Declare()), loop, SLOT(quit()));
    loop->exec();
}


//------------------------------------------------------------------------------
// PlayTrick - Player plays a single trick.
//------------------------------------------------------------------------------
void Player::PlayTrick(void)
{
    // Set the UI to the Trick state.
    emit SetUI(TRICK);

    // Enable the players cards to be movable.
    emit SetCardsMoveable(true);

    // Prep the user's hand so their choice will always be valid.
    emit PrepForTrick();

    // Wait for user to make a response.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(TrickPlayed()), loop, SLOT(quit()));
    loop->exec();

    // Finish up the exchange.
    emit RequestCardTransfer(CardArray::PLAYERHAND,
                             CardArray::PLAYERTRICK,
                             0);

    // Disable the players cards to not be moveable.
    emit SetCardsMoveable(false);
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void Player::ConnectSignals(void)
{
    connect(this, SIGNAL(Skip()), this, SLOT(SkipRequested()));
}


//------------------------------------------------------------------------------
// SkipRequested - User requested a skip.
//------------------------------------------------------------------------------
void Player::SkipRequested(void)
{
    emit DeselectCards();
    emit Declare();
}
