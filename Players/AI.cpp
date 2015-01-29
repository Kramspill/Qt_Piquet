//------------------------------------------------------------------------------
// Filename: AI.cpp
// Description: Represents the opponent played by the cpu.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "AI.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
AI::AI(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
AI::AI(AI&) :
    Player()
{

}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
AI::~AI(void)
{

}


//------------------------------------------------------------------------------
// Initialize - Initialize itself.
//------------------------------------------------------------------------------
void AI::Initialize(PlayerNum num)
{
    playerNumber = num;

    // Initialize the knowledge base.
    knowledgeBase = new KnowledgeBase();
    knowledgeBase->Initialize();

    // Connect the signals.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void AI::Destroy(void)
{
    knowledgeBase->Destroy();

    delete knowledgeBase;   knowledgeBase = 0;
}


//------------------------------------------------------------------------------
// Reset - Reset itself.
//------------------------------------------------------------------------------
void AI::Reset(void)
{
    knowledgeBase->Initialize();
}


//------------------------------------------------------------------------------
// SelectElder - Player executes an Elder selection.
//------------------------------------------------------------------------------
void AI::SelectElder(void)
{
    // Set the UI.
    emit SetUI(ELDERSELECT);

    // Wait for the user to select 'Randomize'.
    QEventLoop* loop = new QEventLoop();
    connect(this, SIGNAL(BeginElderSelect()), loop, SLOT(quit()));
    connect(this, SIGNAL(ExitLoop()), loop, SLOT(quit()));
    loop->exec();
    delete loop;
}


//------------------------------------------------------------------------------
// ExecuteDeal - Player executes a deal.
//------------------------------------------------------------------------------
void AI::ExecuteDeal(void)
{
    // Set the UI.
    emit SetUI(DEAL);

    // Begin dealing out the cards.
    if ( playerNumber == PLAYER1 )
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::TALON,      8);
    }
    else
    {
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
        emit RequestCardTransfer(CardArray::DECK, CardArray::TALON,      8);
    }

    emit DealComplete();
}


//------------------------------------------------------------------------------
// ExecuteExchange - Player executes an exchange.
//------------------------------------------------------------------------------
void AI::ExecuteExchange(void)
{
    // Perform the Carte Blanche declaration if necessary.
    if ( declarationResults->carteBlancheWinner == playerNumber )
        ExecuteCarteBlanche();

    // Request information on card positions.
    emit RequestCardPositions(playerNumber);

    // Select the cards to exchange.
    SelectCardsToDiscard();

    if ( playerNumber == PLAYER1 )
    {
        emit RequestCardTransfer(CardArray::PLAYERHAND,
                                 CardArray::PLAYERDISCARDS,
                                 0);
        emit RequestCardTransfer(CardArray::TALON,
                                 CardArray::PLAYERHAND,
                                 0);
    }
    else
    {
        emit RequestCardTransfer(CardArray::CPUHAND,
                                 CardArray::CPUDISCARDS,
                                 0);
        emit RequestCardTransfer(CardArray::TALON,
                                 CardArray::CPUHAND,
                                 0);
    }

    // Update information on card positions.
    emit RequestCardPositions(playerNumber);

    if ( younger == playerNumber)
        emit ExchangeComplete();
}


//------------------------------------------------------------------------------
// AnnouceDeclaration - Player prepares to make a declaration.
//------------------------------------------------------------------------------
void AI::AnnounceDeclaration(State phase)
{
    switch ( phase )
    {
        case POINT:
            knowledgeBase->SelectPoint(cpuHand);
            break;

        case SEQUENCE:
            knowledgeBase->SelectSequence(cpuHand);
            break;

        case SET:
            knowledgeBase->SelectSet(cpuHand);
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// Respond - Player responds to a declaration.
//------------------------------------------------------------------------------
void AI::Respond(State phase)
{
    AnnounceDeclaration(phase);

    emit RequestCardPositions(playerNumber);
}


//------------------------------------------------------------------------------
// PlayTrick - Player plays a single trick.
//------------------------------------------------------------------------------
void AI::PlayTrick(void)
{
    emit RequestCardPositions(playerNumber);

    knowledgeBase->SelectTrick(cpuHand);

    if ( playerNumber == PLAYER1 )
    {
        emit RequestCardTransfer(CardArray::PLAYERHAND,
                                 CardArray::PLAYERTRICK,
                                 0);
    }
    else
    {
        emit RequestCardTransfer(CardArray::CPUHAND,
                                 CardArray::CPUTRICK,
                                 0);
    }
}


//------------------------------------------------------------------------------
// CarteBlanche - Player declares Carte Blanche
//------------------------------------------------------------------------------
void AI::CarteBlanche(void)
{
    declarationResults->carteBlancheWinner = playerNumber;
    specialScores->carteBlancheScored      = true;
}


//------------------------------------------------------------------------------
// UpdateKnowledgeBase - Update the status of a card in the knowledge base.
//------------------------------------------------------------------------------
void AI::UpdateKnowledgeBase(Card* card, int index,
                             CardArray::Type location)
{
    Card::Suit suit = card->GetSuit();
    Card::Rank rank = card->GetRank();

    // Add the information to the knowledge base.
    knowledgeBase->UpdateCard(suit, rank, index, location);
}


//------------------------------------------------------------------------------
// UpdateHand - Provide the ai with up-to-date information on it's cards.
//------------------------------------------------------------------------------
void AI::UpdateHand(CardArray* newCpuHand)
{
    cpuHand = newCpuHand;
}


//------------------------------------------------------------------------------
// SelectCardsToDiscard - Select cards to discard for the Exchange phase.
//------------------------------------------------------------------------------
void AI::SelectCardsToDiscard(void)
{
    knowledgeBase->FlagDispensableCards(cpuHand);
}


//------------------------------------------------------------------------------
// SelectTrickToPlay - Select a cars to play for the Trick phase.
//------------------------------------------------------------------------------
void AI::SelectTrickToPlay(void)
{
    knowledgeBase->SelectTrick(cpuHand);
}


//------------------------------------------------------------------------------
// ExecuteCarteBlanche - Execute a Carte Blanche declaration.
//------------------------------------------------------------------------------
void AI::ExecuteCarteBlanche(void)
{
    for ( int i =0; i < 12; i++ )
    {
        if ( playerNumber == PLAYER1 )
        {
            emit RequestCardTransfer(CardArray::PLAYERHAND,
                                     CardArray::PLAYERTRICK,
                                     1);
        }
        else
        {
            emit RequestCardTransfer(CardArray::CPUHAND,
                                     CardArray::CPUTRICK,
                                     1);
        }
    }

    if ( playerNumber == PLAYER1 )
    {
        emit RequestCardTransfer(CardArray::PLAYERTRICK,
                                 CardArray::PLAYERHAND,
                                 12);
    }
    else
    {
        emit RequestCardTransfer(CardArray::CPUTRICK,
                                 CardArray::CPUHAND,
                                 12);
    }

    emit ScoreCarteBlanche();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void AI::ConnectSignals(void)
{
}
