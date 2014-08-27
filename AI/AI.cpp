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

    // Initialize the currentRank.
    currentRank = 11;

    // Initialize the member array.
    for ( int outerIndex = 0; outerIndex < 4; outerIndex++ )
    {
        for ( int innerIndex = 0; innerIndex < 8; innerIndex++ )
        {
            knowledgeBase[outerIndex][innerIndex] = 0;
        }
    }
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
    KnowledgeItem* item = new KnowledgeItem;
    item->location      = location;
    item->index         = index;
    item->rank          = -1;

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


//------------------------------------------------------------------------------
// SelectCardsToDiscard - Select cards to discard for the Exchange phase.
//------------------------------------------------------------------------------
void AI::SelectCardsToDiscard(void)
{
    Card* card;

    // Rank the cards.
    RankCards();

    // Select 3 cards for now.
    for ( int index = 11; index > 8; index-- )
    {
        card = cpuHand->GetCard(cardRanks[index]);
        cpuHand->SetSelectionLimit(12);

        card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        card->setSelected(true);
        emit SignalCardSelectionsChanged(card, CardArray::CPUHAND);
    }

    emit AIProcessingComplete();
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

    // Check each suit.
    for ( int index = 0; index < 4; index++ )
    {
        int cardValue       = 7;
        int additionalCards = 0;
        while ( stopperNotFound && cardValue > 4 )
        {
            KnowledgeItem* item = knowledgeBase[suitRanks[index]][cardValue];

            // If the item at this location is in the cpuHand then a stopper
            // has been found.
            if ( item && item->location == CardArray::CPUHAND )
            {
                item->rank               = currentRank;
                cardRanks[currentRank--] = item->index;
                stopperNotFound          = false;
            }

            cardValue--;
            additionalCards++;
        }

        additionalCards--;

        // If we couldn't find a stopper or we require additional cards for the
        // stopper, then we'll add up to two cards to the ranked cards.
        if ( stopperNotFound || additionalCards > 0 )
        {
            while ( additionalCards > 0 && cardValue > 0 )
            {
                KnowledgeItem* item =
                        knowledgeBase[suitRanks[index]][cardValue];

                if ( item && item->location == CardArray::CPUHAND )
                {
                    item->rank               = currentRank;
                    cardRanks[currentRank--] = item->index;
                }

                cardValue--;
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
        // Only check down to tens.
        for ( int valueIndex = 7; valueIndex > 2; valueIndex-- )
        {
            int cardCount = 0;

            KnowledgeItem* item;
            for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
            {
                item = knowledgeBase[suitRanks[suitIndex]][valueIndex];

                if ( item && item->location == CardArray::CPUHAND )
                {
                    cardCount++;
                }
            }

            // If we found a set, add the cards to the ranking.
            if ( cardCount > 2 )
            {
                for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
                {
                    item = knowledgeBase[suitRanks[suitIndex]][valueIndex];

                    if ( item && item->location == CardArray::CPUHAND )
                    {
                        if ( item->rank == -1)
                        {
                            item->rank               = currentRank;
                            cardRanks[currentRank--] = item->index;
                        }
                    }
                }
            }
        }
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
        int sequenceCount = 0;
        KnowledgeItem* item;

        // Check for sequences in the best two suits.
        for ( int suitIndex = 0; suitIndex < 2; suitIndex++ )
        {
            sequenceCount = 0;

            for ( int valueIndex = 7; valueIndex >= 0; valueIndex-- )
            {
                item = knowledgeBase[suitRanks[suitIndex]][valueIndex];

                if ( item && item->location == CardArray::CPUHAND )
                {
                    sequenceCount++;
                }
                else if ( sequenceCount >= 3 )
                {
                    // Go back up the cards ranking the unranked ones.
                    int highestCardInSequence = valueIndex + sequenceCount + 1;
                    for ( int index = valueIndex + 1;
                          index < highestCardInSequence; index++ )
                    {
                        item = knowledgeBase[suitRanks[suitIndex]][index];

                        if ( item->rank == -1 )
                        {
                            item->rank               = currentRank;
                            cardRanks[currentRank--] = item->index;
                        }
                    }
                }
                else
                {
                    sequenceCount = 0;
                }
            }
        }
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
        KnowledgeItem* item;

        // Rank the rest based on their Point contribution.
        for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
        {
            for ( int valueIndex = 7; valueIndex <= 0; valueIndex++ )
            {
                item = knowledgeBase[suitRanks[suitIndex]][valueIndex];

                if ( item && item->location == CardArray::CPUHAND &&
                     item->rank == -1 )
                {
                    item->rank               = currentRank;
                    cardRanks[currentRank--] = item->index;
                }
            }
        }
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
