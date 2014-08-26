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

    // Initialize the suitRanks array.
    suitRanks[0] = 0;
    suitRanks[1] = 1;
    suitRanks[2] = 2;
    suitRanks[3] = 3;

    // Initialize the cuurentRank.
    currentRank = 11;
}


//------------------------------------------------------------------------------
// UpdateCard - Update the status of a card in the knowledge base.
//------------------------------------------------------------------------------
void AI::UpdateKnowledgeBase(Card* card, int index,
                             CardArray::CardArrayType location)
{
    Card::Suit  suit  = card->GetSuit();
    Card::Value value = card->GetValue();

    // Create a knowledge item and add it to the knowledge base.
    KnowledgeItem item;
    item.location = location;
    item.index    = index;

    knowledgeBase[suit][value-7] = item;
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
    Card* card;
    int   size = cpuHand->GetSize();

    // Total up the values for each suit in the cpu's hand.
    for ( int index = 0; index < size; index++ )
    {
        card = cpuHand->GetCard(index);

        suitValues[card->GetSuit()] += pointValues[card->GetValue()-7];
    }

    // Sort them from highest to lowest (insertion sort).
    for ( int index = 1; index < 4; index++ )
    {
        int  valueAtIndex = suitValues[index];
        char suitAtIndex  = suitRanks[index];

        int innerIndex = index;
        while ( innerIndex > 0 && valueAtIndex > suitValues[innerIndex-1] )
        {
            // Swap the suit values.
            suitValues[innerIndex] = suitValues[innerIndex-1];

            // Swap the corresponding suitRanks array.
            suitRanks[innerIndex]  = suitRanks[innerIndex-1];

            innerIndex--;
        }

        // Put the suit value and rank in it's correct place.
        suitValues[innerIndex] = valueAtIndex;
        suitRanks[innerIndex]  = suitAtIndex;
    }
}


//------------------------------------------------------------------------------
// RankStoppers - Rank the cards that can act as 'Stoppers'.
//------------------------------------------------------------------------------
void AI::RankStoppers(void)
{
    bool stopperNotFound = true;

    for ( int index = 0; index < 4; index++ )
    {
        int cardValue       = 7;
        int additionalCards = 0;
        while ( stopperNotFound && cardValue > 4 )
        {
            KnowledgeItem item = knowledgeBase[suitRanks[index]][cardValue];

            if ( item.location == CardArray::CPUHAND )
            {
                cardRanks[currentRank--] = item.index;
                stopperNotFound          = false;
            }

            cardValue--;
            additionalCards++;
        }

        additionalCards--;

        if ( stopperNotFound || additionalCards > 0 )
        {
            while ( additionalCards > 0 && cardValue > 0 )
            {
                KnowledgeItem item = knowledgeBase[suitRanks[index]][cardValue];

                if ( item.location == CardArray::CPUHAND )
                {
                    cardRanks[currentRank--] = item.index;
                }
            }
        }

        stopperNotFound = true;
    }
}


//------------------------------------------------------------------------------
// RankSets - Rank the cards that can work in a Set.
//------------------------------------------------------------------------------
void AI::RankSets(void)
{
    // Make sure that there are still cards to rank.
    if ( currentRank >= 0 )
    {

    }
}


//------------------------------------------------------------------------------
// RankSequences - Rank the cards that can work in a Sequence.
//------------------------------------------------------------------------------
void AI::RankSequences(void)
{
    // Make sure that there are still cards to rank.
    if ( currentRank >= 0 )
    {

    }
}


//------------------------------------------------------------------------------
// FinishRanking - Rank the cards that have yet to be ranked.
//------------------------------------------------------------------------------
void AI::FinishRanking(void)
{
    // Make sure that there are still cards to rank.
    if ( currentRank >= 0 )
    {

    }
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
