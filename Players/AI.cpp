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
// ExecuteDeal - Player executes a deal.
//------------------------------------------------------------------------------
void AI::ExecuteDeal(void)
{
    // Set the UI.
    emit SetUI(DEAL);

    // Begin dealing out the cards.
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::PLAYERHAND, 3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::CPUHAND,    3);
    emit RequestCardTransfer(CardArray::DECK, CardArray::TALON,      8);

    emit DealComplete();
}


//------------------------------------------------------------------------------
// ExecuteExchange - Player executes an exchange.
//------------------------------------------------------------------------------
void AI::ExecuteExchange(void)
{
    // Request information on card positions.
    emit RequestCardPositions(playerNumber);

    // Select the cards to exchange.
    SelectCardsToDiscard();

    emit RequestCardTransfer(CardArray::CPUHAND,
                             CardArray::CPUDISCARDS,
                             0);
    emit RequestCardTransfer(CardArray::TALON,
                             CardArray::CPUHAND,
                             0);

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

    emit RequestCardTransfer(CardArray::CPUHAND,
                             CardArray::CPUTRICK,
                             0);
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

    //emit AIProcessingComplete();
}


//------------------------------------------------------------------------------
// SelectTrickToPlay - Select a cars to play for the Trick phase.
//------------------------------------------------------------------------------
void AI::SelectTrickToPlay(void)
{
    knowledgeBase->SelectTrick(cpuHand);

    emit AIProcessingComplete();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void AI::ConnectSignals(void)
{
    connect(knowledgeBase,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardArray::Type)),
            this,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardArray::Type)));
}
