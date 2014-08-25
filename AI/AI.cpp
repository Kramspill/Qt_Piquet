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
    QObject()
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
void AI::Initialize(void)
{
    // Initialize the pointValues array.
    pointValues[0] = 7;
    pointValues[1] = 8;
    pointValues[2] = 9;
    pointValues[3] = 10;
    pointValues[4] = 10;
    pointValues[5] = 10;
    pointValues[6] = 10;
    pointValues[7] = 11;
}


//------------------------------------------------------------------------------
// UpdateCard - Update the status of a card in the knowledge base.
//------------------------------------------------------------------------------
void AI::UpdateKnowledgeBase(Card* card, CardArray::CardArrayType location)
{
    Card::Suit  suit  = card->GetSuit();
    Card::Value value = card->GetValue();

    knowledgeBase[suit][value-7] = location;
}


//------------------------------------------------------------------------------
// SelectCardsToDiscard - Select cards to discard for the Exchange phase.
//------------------------------------------------------------------------------
void AI::SelectCardsToDiscard(void)
{
    // Rank the cards.
    RankCards();
}


//------------------------------------------------------------------------------
// RankCards - Rank the cards in the cpu's hand based on it's usefulness.
//------------------------------------------------------------------------------
void AI::RankCards(void)
{
    // Determine the cpu's best and worst suits.
    CalculateSuitValues();

    // Rank the 'Stoppers'.
    RankStoppers();

    // Rank the Cards that help with Sets.
    RankSets();

    // Rank the Cards that help with Sequences.
    RankSequences();

    // Rank the last of the cards.
    FinishRanking();
}


//------------------------------------------------------------------------------
// CalculateSuitValues - Determine the cpu's best and worst suits and rank them.
//------------------------------------------------------------------------------
void AI::CalculateSuitValues(void)
{
    int value = 0;

    for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
    {
        for ( int valueIndex = 0; valueIndex < 8; valueIndex++ )
        {
            value += pointValues[valueIndex];
        }

        suitValues[suitIndex] = value;
    }
}


//------------------------------------------------------------------------------
// RankStoppers - Rank the cards that can act as 'Stoppers'.
//------------------------------------------------------------------------------
void AI::RankStoppers(void)
{

}


//------------------------------------------------------------------------------
// RankSets - Rank the cards that can work in a Set.
//------------------------------------------------------------------------------
void AI::RankSets(void)
{

}


//------------------------------------------------------------------------------
// RankSequences - Rank the cards that can work in a Sequence.
//------------------------------------------------------------------------------
void AI::RankSequences(void)
{

}


//------------------------------------------------------------------------------
// FinishRanking - Rank the cards that have yet to be ranked.
//------------------------------------------------------------------------------
void AI::FinishRanking(void)
{

}


//------------------------------------------------------------------------------
// DeclarePoint - Select cards for the Point declaration.
//------------------------------------------------------------------------------
void AI::DeclarePoint(void)
{

}


//------------------------------------------------------------------------------
// DeclareSequence - Select cards for the Sequence declaration.
//------------------------------------------------------------------------------
void AI::DeclareSequence(void)
{

}


//------------------------------------------------------------------------------
// DeclareSet - Select cards for the Set declaration.
//------------------------------------------------------------------------------
void AI::DeclareSet(void)
{

}


//------------------------------------------------------------------------------
// SelectAIAction - Select the appropriate action to perform.
//------------------------------------------------------------------------------
void AI::SelectAIAction(AI::AIAction action)
{
    switch ( action )
    {
        case DISCARD:
            SelectCardsToDiscard();
            break;

        case POINT:
            DeclarePoint();
            break;

        case SEQUENCE:
            DeclareSequence();
            break;

        case SET:
            DeclareSet();
            break;

        default:
            break;
    }
}
