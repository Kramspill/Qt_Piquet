//------------------------------------------------------------------------------
// Filename: KnowledgeBase.cpp
// Description: Represents the cpu's knowledge of the cards.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "KnowledgeBase.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
KnowledgeBase::KnowledgeBase(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
KnowledgeBase::KnowledgeBase(KnowledgeBase&) :
    QObject()
{

}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
KnowledgeBase::~KnowledgeBase(void)
{

}


//------------------------------------------------------------------------------
// Initialize - Initialize itself.
//------------------------------------------------------------------------------
void KnowledgeBase::Initialize(void)
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

    // Initialize the card status'.
    for ( int outerIndex = 0; outerIndex < 4; outerIndex++ )
    {
        for ( int innerIndex = 0; innerIndex < 8; innerIndex++ )
        {
            KnowledgeItem* item = new KnowledgeItem();

            item->location = CardArray::UNKNOWN;
            item->index    = 0;
            item->rank     = -1;

            cardStatus[outerIndex][innerIndex] = item;
        }
    }

}


//------------------------------------------------------------------------------
// UpdateCard - Update the status of a card.
//------------------------------------------------------------------------------
void KnowledgeBase::UpdateCard(Card::Suit suit, Card::Rank rank, int index,
                               CardArray::CardArrayType location)
{
    cardStatus[suit][rank-7]->location = location;
    cardStatus[suit][rank-7]->index    = index;
}


//------------------------------------------------------------------------------
// FlagDispensableCards - Flag cards that have no value to the cpu so that they
//                        may be exchanged.
//------------------------------------------------------------------------------
void KnowledgeBase::FlagDispensableCards(CardArray* cpuHand)
{
    Card* card;

    // Rank the cards.
    RankCards(cpuHand);

    // Select 3 cards for now.
    for ( int index = 2; index >= 0; index-- )
    {
        card = cpuHand->GetCard(cardRanks[index]);
        cpuHand->SetSelectionLimit(12);

        card->setSelected(true);
        card->UpdateSelection();
        emit SignalCardSelectionsChanged(card, CardArray::CPUHAND);
    }
}


//------------------------------------------------------------------------------
// SelectTrick - Choose a card from the cpu's hand to play.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectTrick(CardArray* cpuHand)
{
    // For now, we just get the top card.
    Card* card = cpuHand->GetCard(0);

    card->setSelected(true);
    card->UpdateSelection();
    emit SignalCardSelectionsChanged(card, CardArray::CPUHAND);
}


//------------------------------------------------------------------------------
// SelectPoint - Calculate the cpu's best Point and select it.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectPoint(CardArray* hand)
{
    int currentNumCards = 0;
    int bestNumCards    = 0;
    int currentValue    = 0;
    int bestValue       = 0;
    int bestSuit        = 0;

    for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
    {
        // Initialize the current score to 0.
        currentNumCards = 0;
        currentValue    = 0;

        for ( int valueIndex = 0; valueIndex < 8; valueIndex++ )
        {
            KnowledgeItem* item = cardStatus[suitIndex][valueIndex];

            if ( item->location == CardArray::CPUHAND )
            {
                currentNumCards++;
                currentValue   += pointValues[valueIndex];
            }
        }

        // Check if this is now the best Point.
        if ( currentNumCards >= bestNumCards )
        {
            if ( currentNumCards > bestNumCards )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
                bestSuit     = suitIndex;
            }
            else if ( currentValue > bestValue )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
                bestSuit     = suitIndex;
            }
        }
    }

    // Now select the cards.
    for ( int i = 0; i < hand->GetSize(); i++ )
    {
        Card* card = hand->GetCard(i);

        if ( card->GetSuit() == bestSuit )
        {
            card->setSelected(true);
            card->UpdateSelection();
        }
    }
}


//------------------------------------------------------------------------------
// SelectSequence - Calculate the cpu's best Sequence and select it..
//------------------------------------------------------------------------------
void KnowledgeBase::SelectSequence(CardArray* hand)
{
    int currentNumCards = 0;
    int bestNumCards    = 0;
    int currentValue    = 0;
    int bestValue       = 0;
    int bestSuit        = 0;

    for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
    {
        // Initialize the current score to 0.
        currentNumCards = 0;
        currentValue    = 0;
        int count       = 0;

        for ( int valueIndex = 0; valueIndex < 8; valueIndex++ )
        {
            KnowledgeItem* item = cardStatus[suitIndex][valueIndex];

            if ( item->location == CardArray::CPUHAND )
            {
                count++;
            }
            else if ( count >= 3 && count >= currentNumCards )
            {
                currentNumCards = count;
                currentValue    = valueIndex + 7;
                count           = 0;
            }
        }

        // Check if this is now the best Sequence.
        if ( currentNumCards >= bestNumCards )
        {
            if ( currentNumCards > bestNumCards )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
                bestSuit     = suitIndex;
            }
            else if ( currentValue > bestValue )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
                bestSuit     = suitIndex;
            }
        }
    }

    // Now select the cards.
    if ( bestNumCards > 0 )
    {
        Card* card;

       // Start by finding the top card.
        bool topCardNotFound = true;
        int  i = 0;
        while ( topCardNotFound && i < 12 )
        {
            card = hand->GetCard(i++);

            if ( card->GetSuit() == bestSuit &&
                 card->GetRank() == bestValue )
            {
                topCardNotFound = false;
                i--;
            }
        }

        card->setSelected(true);
        card->UpdateSelection();
        i--;
        bestNumCards--;

        while ( bestNumCards > 0 )
        {
            Card* card = hand->GetCard(i--);
            card->setSelected(true);
            card->UpdateSelection();
            bestNumCards--;
        }
    }
}


//------------------------------------------------------------------------------
// SelectSet - Calculate the cpu's best Set and select it.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectSet(CardArray* hand)
{
    int currentNumCards = 0;
    int bestNumCards    = 0;
    int currentValue    = 0;
    int bestValue       = 0;

    for ( int valueIndex = 3; valueIndex < 8; valueIndex++ )
    {
        // Initialize the current score to 0.
        currentNumCards = 0;
        currentValue    = 0;
        int count       = 0;

        for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
        {
            KnowledgeItem* item = cardStatus[suitIndex][valueIndex];

            if ( item->location == CardArray::CPUHAND )
            {
                count++;
            }
        }

        // Set the currentScore if it's greater than 2 cards.
        if ( count > 2 )
        {
            currentNumCards = count;
            currentValue    = valueIndex + 7;
        }

        // Check if this is now the best Set.
        if ( currentNumCards >= bestNumCards )
        {
            if ( currentNumCards > bestNumCards )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
            }
            else if ( currentValue > bestValue )
            {
                bestNumCards = currentNumCards;
                bestValue    = currentValue;
            }
        }
    }

    // Now select the cards.
    if ( bestNumCards > 0 )
    {
        for ( int i = 0; i < hand->GetSize(); i++ )
        {
            Card* card = hand->GetCard(i);

            if ( card->GetRank() == bestValue )
            {
                card->setSelected(true);
                card->UpdateSelection();
            }
        }
    }
}


//------------------------------------------------------------------------------
// RankCards - Rank the cards in the cpu's hand based on it's usefulness.
//------------------------------------------------------------------------------
void KnowledgeBase::RankCards(CardArray* cpuHand)
{
    // Determine the cpu's best and worst suits.
    CalculateSuitValues(cpuHand);

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
void KnowledgeBase::CalculateSuitValues(CardArray* cpuHand)
{
    Card* card;
    int   size = cpuHand->GetSize();

    // Total up the values for each suit in the cpu's hand.
    for ( int index = 0; index < size; index++ )
    {
        card = cpuHand->GetCard(index);

        suitValues[card->GetSuit()] += pointValues[card->GetRank()-7];
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
void KnowledgeBase::RankStoppers(void)
{
    bool stopperNotFound = true;

    // Check each suit.
    for ( int index = 0; index < 4; index++ )
    {
        int cardValue       = 7;
        int additionalCards = 0;
        while ( stopperNotFound && cardValue > 4 )
        {
            KnowledgeItem* item = cardStatus[suitRanks[index]][cardValue];

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
                        cardStatus[suitRanks[index]][cardValue];

                if ( item && item->location == CardArray::CPUHAND )
                {
                    item->rank               = currentRank;
                    cardRanks[currentRank--] = item->index;

                    additionalCards--;
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
void KnowledgeBase::RankSets(void)
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
                item = cardStatus[suitRanks[suitIndex]][valueIndex];

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
                    item = cardStatus[suitRanks[suitIndex]][valueIndex];

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
void KnowledgeBase::RankSequences(void)
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
                item = cardStatus[suitRanks[suitIndex]][valueIndex];

                if ( item && item->location == CardArray::CPUHAND )
                {
                    sequenceCount++;
                }
                else if ( sequenceCount >= 3 )
                {
                    // Go back up the cards ranking the unranked ones.
                    int highestCardInSequence = valueIndex + sequenceCount;
                    for ( int index = valueIndex + 1;
                          index <= highestCardInSequence; index++ )
                    {
                        item = cardStatus[suitRanks[suitIndex]][index];

                        if ( item->rank == -1 )
                        {
                            item->rank               = currentRank;
                            cardRanks[currentRank--] = item->index;
                        }
                    }

                    sequenceCount = 0;
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
void KnowledgeBase::FinishRanking(void)
{
    // Make sure that there are still cards to rank.
    if ( currentRank >= 0 )
    {
        KnowledgeItem* item;

        // Rank the rest based on their Point contribution.
        for ( int suitIndex = 0; suitIndex < 4; suitIndex++ )
        {
            for ( int valueIndex = 7; valueIndex >= 0; valueIndex-- )
            {
                item = cardStatus[suitRanks[suitIndex]][valueIndex];

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
