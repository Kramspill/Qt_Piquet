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
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void KnowledgeBase::Destroy(void)
{
    for ( int outerIndex = 0; outerIndex < 4; outerIndex++ )
    {
        for ( int innerIndex = 0; innerIndex < 8; innerIndex++ )
        {
            delete cardStatus[outerIndex][innerIndex];
            cardStatus[outerIndex][innerIndex] = 0;
        }
    }
}


//------------------------------------------------------------------------------
// UpdateCard - Update the status of a card.
//------------------------------------------------------------------------------
void KnowledgeBase::UpdateCard(Card::Suit suit, Card::Rank rank, int index,
                               CardArray::Type location)
{
    cardStatus[suit][rank-7]->location = location;
    cardStatus[suit][rank-7]->index    = index;
    cardStatus[suit][rank-7]->selected = false;
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

        card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        card->setSelected(true);
    }
}


//------------------------------------------------------------------------------
// SelectExchanges - Select cards to discard based on hand evaluation.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectExchanges(CardArray* cpuHand, int talonSize)
{
    // Initialize a new hand so the passed in CardArray doesn't get changed.
    CardArray* hand = new CardArray();
    for ( int i = 0; i < cpuHand->GetSize(); i++ )
    {
        Card* c = new Card();

        c->SetSuit(cpuHand->GetCard(i)->GetSuit());
        c->SetRank(cpuHand->GetCard(i)->GetRank());

        hand->AddCard(c, false, true);
    }

    // Calculate the possible cards that can be added.
    CardArray* possibleCards = new CardArray();
    for ( int i = 0; i < 4; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            if ( cardStatus[i][j]->location == CardArray::UNKNOWN )
            {
                Card* card = new Card();

                card->SetSuit((Card::Suit)i);
                card->SetRank((Card::Rank)(j+7));

                possibleCards->AddCard(card, false, true);
            }
        }
    }

    // Array to store removed cards.
    CardArray* removedCards  = new CardArray();

    // Evaluate the current hand.
    float e    = Evaluate(hand);
    SelectCardRemovals(e, hand, possibleCards, removedCards);

    // Select the chosen cards.
    Card* card; Card* c; Card* r;
    int i = 0;
    int numDiscards = (talonSize > 5) ? 5 : talonSize;
    int size = removedCards->GetSize();
    while ( i < numDiscards && i < size )
    {
        int  j     = 0;
        bool found = false;
        while ( !found )
        {
            c = cpuHand->GetCard(j);
            r = removedCards->GetCard(i);

            if ( c->GetSuit() == r->GetSuit() && c->GetRank() == r->GetRank() )
                found = true;
            else
                j++;
        }
        i++;

        if ( found )
        {
            card = cpuHand->GetCard(j);

            card->setFlag(QGraphicsItem::ItemIsSelectable, true);
            card->setSelected(true);
        }
    }

    // Free the memory.
    size = hand->GetSize();
    for ( int i = 0; i < size; i++ )
    {
        card = hand->GetCard(0);
        hand->RemoveCard(card, true);

        delete card;
    }
    delete hand;

    size = possibleCards->GetSize();
    for ( int i = 0; i < size; i++ )
    {
        card = possibleCards->GetCard(0);
        possibleCards->RemoveCard(card, true);

        delete card;
    }
    delete possibleCards;

    delete removedCards;
}


//------------------------------------------------------------------------------
// SelectMcsExchange - Choose cards to discard for the Exchange. Uses Monte
//                     Carlo Sampling.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectMcsExchange(CardArray* cpuHand, int talonSize)
{
    // Create an array of pointers to elements representing the cpu's hand.
    std::vector<McsElement*> myHand = GenerateElementArray(cpuHand);

    // Generate a set of hands for the opponent.
    std::vector<std::vector<McsElement*> > oppHands = GenOppHands(50);

    // Determine the selected cards.
    int numSimulations = 0;
    while ( numSimulations < 1000 )
    {
        Mcs(myHand, oppHands, talonSize, numSimulations);
        numSimulations += 50;
    }

    // Go through 'myHand' and select cards that were chosen the most.
    int maxPlays    = 0;
    int maxIndex    = 0;
    for ( int i = 0; i < 5; i++ )
    {
        if ( myHand[i]->numPlays > maxPlays )
        {
            maxPlays = myHand[i]->numPlays;
            maxIndex = i;
        }
    }
    int numDiscards = myHand[maxIndex]->numDiscards;

    int selectedIndex[5];
    int selectedPlays[5];
    for ( int i = 0; i < 5; i++ )
    {
        selectedIndex[i] = -1;
        selectedPlays[i] = -1;
    }

    for ( int i = 5; i < (int)myHand.size(); i++ )
    {
        int numPlays = myHand[i]->numPlays;

        int  j    = 0;
        bool done = false;
        while ( j < numDiscards && !done )
        {
            if ( numPlays > selectedPlays[j] )
            {
                selectedPlays[j] = numPlays;
                selectedIndex[j] = i-5;
                done = true;
            }
            j++;
        }
    }

    // Select the chosen cards.
    for ( int i = 0; i < numDiscards; i++ )
    {
        Card* card = cpuHand->GetCard(selectedIndex[i]);

        card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        card->setSelected(true);
    }
}


//------------------------------------------------------------------------------
// SelectTrick - Choose a card from the cpu's hand to play.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectTrick(CardArray* cpuHand)
{
    bool  trickFound = false;
    int   suit       = 0;
    int   value      = 0;
    Card* card;

    // Check if the opponent has a trick in play.
    while ( !trickFound && suit < 4 )
    {
        value = 0;
        while ( !trickFound && value < 8 )
        {
            if ( cardStatus[suit][value]->location == CardArray::PLAYERTRICK )
                trickFound = true;

            value++;
        }

        suit++;
    }

    // If a trick was found then select a card of the same suit.
    if ( trickFound )
    {
        bool cardFound = false;

        suit--;
        value = 7;

        // Check if we have a card of the same suit.
        while ( !cardFound && value >= 0 )
        {
            if ( cardStatus[suit][value]->location == CardArray::CPUHAND )
                cardFound = true;

            value--;
        }

        if ( cardFound )
        {
            value++;
            cardFound = false;

            int i = 0;
            while ( !cardFound )
            {
                card = cpuHand->GetCard(i++);

                if ( card->GetSuit() == suit && card->GetRank()-7 == value )
                {
                    cardFound = true;
                }
            }

        }
        else
        {
            // For now, we just get the top card.
            card = cpuHand->GetCard(0);
        }
    }
    else
    {
        // For now, we just get the top card.
        card = cpuHand->GetCard(0);
    }

    card->setSelected(true);
}


//------------------------------------------------------------------------------
// SelectMMTrick - Choose a card from the cpu's hand to play. Uses imp-minimax.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectMMTrick(CardArray* cpuHand, PlayerNum n)
{
    Node* root;
    int max = -1000;
    Card* card = cpuHand->GetCard(0);

    // Create a node based on current state.
    root              = new Node();
    root->payoff      = 0;
    root->myTurnNext  = true;
    root->myWins      = (n == PLAYER1) ? trickResults->player1Wins : trickResults->player2Wins;
    root->oppWins     = (n == PLAYER1) ? trickResults->player2Wins : trickResults->player1Wins;
    root->piquetGiven = specialScores->piqueScored;
    root->myScore     = myScore;
    root->oppScore    = oppScore;

    // Allocate space for state.
    root->state = new CardArray::Type*[4];
    for ( int i = 0; i < 4; i++ )
        root->state[i] = new CardArray::Type[8];

    // Initialize state.
    for ( int i = 0; i < 4; i++ )
    {
        for (int j = 0; j < 8; j++ )
        {
            root->state[i][j] = cardStatus[i][j]->location;
        }
    }

    // Call the imp-minimax function to determine the next move.
    ImpMinimax(root, DEPTH, true, n);

    // Select the move from the tree.
    Node* move;
    for ( int i = 0; i < (int)root->children.size(); i++ )
    {
        Node* n = root->children[i];

        if ( n->payoff > max )
        {
            max = n->payoff;
            move = n;
        }
    }

    for ( int i = 0; i < 4; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            CardArray::Type type = move->state[i][j];
            if ( (type == CardArray::PLAYERTRICK && n == PLAYER1) ||
                 (type == CardArray::CPUTRICK && n == PLAYER2) )
            {
                int n = 0;
                while ( card != NULL && (card->GetSuit() != i && card->GetValue() != j) )
                {
                    n++;
                    card = cpuHand->GetCard(n);
                }

                if ( card )
                    card->setSelected(true);

                break;
            }
        }
    }

    // Free the memory allocated for the tree.
    FreeTree(root);
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
        }
    }
}


//------------------------------------------------------------------------------
// SelectSequence - Calculate the cpu's best Sequence and select it.
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

            if ( item->location == CardArray::CPUHAND &&
                 item->selected == false )
            {
                count++;
            }
            else if ( count >= 3 && count >= currentNumCards )
            {
                currentNumCards = count;
                currentValue    = valueIndex + 6;
                count           = 0;
            }
            else
            {
                count           = 0;
            }
        }

        // For the case when Ace is last card.
        if ( count >= 3 && count >= currentNumCards )
        {
            currentNumCards = count;
            currentValue    = 14;
            count           = 0;
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
        for ( int i = 0; i < hand->GetSize(); i++ )
        {
            Card* card = hand->GetCard(i);

            if ( card->GetSuit() == bestSuit  &&
                 card->GetRank() <= bestValue &&
                 card->GetRank() > bestValue - bestNumCards )
            {
                card->setSelected(true);
                cardStatus[card->GetSuit()][card->GetRank()-7]->selected = true;
            }
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

            if ( item->location == CardArray::CPUHAND &&
                 item->selected == false )
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
                cardStatus[card->GetSuit()][card->GetRank()-7]->selected = true;
            }
        }
    }
}


//------------------------------------------------------------------------------
// UpdateScores - Update the score knowledge.
//------------------------------------------------------------------------------
void KnowledgeBase::SetScores(int myScore, int oppScore)
{
    this->myScore  = myScore;
    this->oppScore = oppScore;
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


//------------------------------------------------------------------------------
// ImpMinimax - Implementation of imperfect-info minimax for trick play.
//------------------------------------------------------------------------------
int KnowledgeBase::ImpMinimax(KnowledgeBase::Node* n,
                              int                  depth,
                              bool                 myMove,
                              PlayerNum            p)
{
    int bestValue;
    int value;

    // Generate the list of possible moves we can make.
    GenerateMoves(n, p);

    // Check for terminal/zero depth
    if ( n->children.size() > 0 && depth > 0 )
    {
        // Check whether we are maximizing or minimizing at this node.
        if ( myMove )
        {
            bestValue = -1000;

            // Recurse on child nodes.
            for ( int i = 0; i < (int)n->children.size(); i++ )
            {
                Node* child = n->children[i];

                value     = ImpMinimax(child, depth-1, n->myTurnNext, p);
                bestValue = std::max(bestValue, value);
            }

        }
        else
        {
            bestValue = 1000;

            // Recurse on child nodes.
            for ( int i = 0; i < (int)n->children.size(); i++ )
            {
                Node* child = n->children[i];

                value     = ImpMinimax(child, depth-1, n->myTurnNext, p);
                bestValue = std::min(bestValue, value);
            }
        }

        // Store the best payoff at this node.
        n->payoff = bestValue;
    }
    else
    {
        bestValue = n->payoff;
    }

    return bestValue;
}


//------------------------------------------------------------------------------
// GenerateMoves - Generate a list of possible children of the given node.
//------------------------------------------------------------------------------
void KnowledgeBase::GenerateMoves(KnowledgeBase::Node* parent, PlayerNum p)
{
    bool oppTrick = false;
    bool myTrick  = false;

    int  oppTrickLoc[2];
    int  myTrickLoc[2];

    // Check if there are tricks in play.
    for ( int i = 0; i < 4; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            if ( (parent->state[i][j] == CardArray::PLAYERTRICK &&
                  p == PLAYER2) ||
                 (parent->state[i][j] == CardArray::CPUTRICK &&
                  p == PLAYER1) )
            {
                oppTrick = true;
                oppTrickLoc[0] = i;
                oppTrickLoc[1] = j;
            }
            else if ( (parent->state[i][j] == CardArray::PLAYERTRICK &&
                       p == PLAYER1) ||
                      (parent->state[i][j] == CardArray::CPUTRICK &&
                       p == PLAYER2) )
            {
                myTrick = true;
                myTrickLoc[0] = i;
                myTrickLoc[1] = j;
            }
        }
    }

    // Check if the children are of the ai's moves or not.
    if ( parent->myTurnNext )
    {
        // If there are two tricks in play, we are starting a new trick.
        if ( myTrick || !oppTrick )
        {
            for ( int i = 0; i < 4; i++ )
            {
                for ( int j = 0; j < 8; j++ )
                {
                    if ( (parent->state[i][j] == CardArray::PLAYERHAND &&
                          p == PLAYER1) ||
                         (parent->state[i][j] == CardArray::CPUHAND &&
                          p == PLAYER2) )
                    {
                        Node* child = new Node();

                        // Allocate space for state.
                        child->state = new CardArray::Type*[4];
                        for ( int m = 0; m < 4; m++ )
                            child->state[m] = new CardArray::Type[8];

                        // Initialize the state.
                        for ( int k = 0; k < 4; k++ )
                        {
                            for ( int l = 0; l < 8; l++ )
                            {
                                child->state[k][l] = parent->state[k][l];
                                if ( child->state[k][l] == CardArray::PLAYERTRICK ||
                                     child->state[k][l] == CardArray::CPUTRICK )
                                {
                                    child->state[k][l] = CardArray::PREVIOUSTRICKS;
                                }
                            }
                        }

                        if ( p == PLAYER1 )
                            child->state[i][j] = CardArray::PLAYERTRICK;
                        else
                            child->state[i][j] = CardArray::CPUTRICK;

                        // Update node information.
                        child->myTurnNext  = false;
                        child->piquetGiven = parent->piquetGiven;
                        child->myWins      = parent->myWins;
                        child->oppWins     = parent->oppWins;
                        child->myScore     = parent->myScore + 1;
                        child->oppScore    = parent->oppScore;
                        child->payoff      = parent->payoff + j;

                        // Special score modifiers.
                        if ( !child->piquetGiven &&
                             (child->myScore >= 30 && child->oppScore == 0) )
                        {
                            child->myScore += 30;
                            child->payoff  += 30;
                            child->piquetGiven = true;
                        }

                        // Add the child.
                        parent->children.push_back(child);
                    }
                }
            }
        }
        else
        {
            bool restricted = false;

            // Determine if our moves are restricted to a suit.
            for ( int j = 0; j < 8; j++ )
            {
                if ( (parent->state[oppTrickLoc[0]][j] == CardArray::PLAYERHAND &&
                      p == PLAYER1) ||
                     (parent->state[oppTrickLoc[0]][j] == CardArray::CPUHAND &&
                      p == PLAYER2) )
                {
                    restricted = true;

                    Node* child = new Node();

                    // Allocate space for state.
                    child->state = new CardArray::Type*[4];
                    for ( int i = 0; i < 4; i++ )
                        child->state[i] = new CardArray::Type[8];

                    // Initialize the state.
                    for ( int k = 0; k < 4; k++ )
                    {
                        for ( int l = 0; l < 8; l++ )
                        {
                            child->state[k][l] = parent->state[k][l];
                        }
                    }

                    if ( p == PLAYER1 )
                        child->state[oppTrickLoc[0]][j] = CardArray::PLAYERTRICK;
                    else
                        child->state[oppTrickLoc[0]][j] = CardArray::CPUTRICK;

                    // Update node information.
                    child->piquetGiven = parent->piquetGiven;

                    // Set the payoff.
                    if ( oppTrickLoc[1] < j )
                    {
                        child->myTurnNext  = true;
                        child->myWins      = parent->myWins + 1;
                        child->myScore     = parent->myScore + 1;
                        child->oppWins     = parent->oppWins;
                        child->oppScore    = parent->oppScore;
                        child->payoff      = parent->payoff + (8 - (j - oppTrickLoc[1]));

                        // Check for final victory.
                        if ( child->myWins + child->oppWins == 12 )
                        {
                           child->myScore++;
                           child->payoff++;
                        }

                        // Special score modifiers.
                        if ( !child->piquetGiven &&
                             (child->myScore >= 30 && child->oppScore == 0) )
                        {
                            child->myScore += 30;
                            child->payoff  += 30;
                            child->piquetGiven = true;
                        }
                    }
                    else
                    {
                        child->myTurnNext  = false;
                        child->myWins      = parent->myWins;
                        child->myScore     = parent->myScore;
                        child->oppWins     = parent->oppWins + 1;
                        child->oppScore    = parent->oppScore;
                        child->payoff      = parent->payoff - 1;

                        // Check for final victory.
                        if ( child->myWins + child->oppWins == 12 )
                        {
                           child->oppScore++;
                           child->payoff--;

                           // Special score modifiers.
                           if ( !child->piquetGiven &&
                                (child->oppScore >= 30 && child->myScore == 0) )
                           {
                               child->oppScore += 30;
                               child->payoff   -= 30;
                               child->piquetGiven = true;
                           }
                        }
                    }

                    // Check for final special scores.
                    if ( child->myWins + child->oppWins == 12 )
                    {
                       if ( child->myWins > child->oppWins )
                       {
                           if ( child->oppWins == 0 )
                           {
                               child->myScore += 40;
                               child->payoff  += 40;
                           }
                           else
                           {
                               child->myScore += 10;
                               child->payoff  += 10;
                           }
                       }
                       else if ( child->myWins < child->oppWins )
                       {
                           if ( child->myWins == 0 )
                           {
                               child->oppScore += 40;
                               child->payoff   -= 40;
                           }
                           else
                           {
                               child->oppScore += 10;
                               child->payoff   -= 10;
                           }
                       }
                    }

                    // Add the child.
                    parent->children.push_back(child);
                }
            }

            if ( !restricted )
            {
                for ( int i = 0; i < 4; i++ )
                {
                    for ( int j = 0; j < 8; j++ )
                    {
                        if ( (parent->state[i][j] == CardArray::PLAYERHAND &&
                              p == PLAYER1) ||
                             (parent->state[i][j] == CardArray::CPUHAND &&
                              p == PLAYER2) )
                        {
                            Node* child = new Node();

                            // Allocate space for state.
                            child->state = new CardArray::Type*[4];
                            for ( int m = 0; m < 4; m++ )
                                child->state[m] = new CardArray::Type[8];

                            // Initialize the state.
                            for ( int k = 0; k < 4; k++ )
                            {
                                for ( int l = 0; l < 8; l++ )
                                {
                                    child->state[k][l] = parent->state[k][l];
                                }
                            }

                            if ( p == PLAYER1 )
                                child->state[i][j] = CardArray::PLAYERTRICK;
                            else
                                child->state[i][j] = CardArray::CPUTRICK;

                            // Update node information.
                            child->myTurnNext  = false;
                            child->myWins      = parent->myWins;
                            child->myScore     = parent->myScore;
                            child->oppWins     = parent->oppWins + 1;
                            child->oppScore    = parent->oppScore;
                            child->payoff      = parent->payoff - j;

                            // Check for final victory.
                            if ( child->myWins + child->oppWins == 12 )
                            {
                               child->oppScore++;
                               child->payoff--;

                               // Special score modifiers.
                               if ( !child->piquetGiven &&
                                    (child->oppScore >= 30 && child->myScore == 0) )
                               {
                                   child->oppScore += 30;
                                   child->payoff   -= 30;
                                   child->piquetGiven = true;
                               }

                               if ( child->myWins > child->oppWins )
                               {
                                   if ( child->oppWins == 0 )
                                   {
                                       child->myScore += 40;
                                       child->payoff  += 40;
                                   }
                                   else
                                   {
                                       child->myScore += 10;
                                       child->payoff  += 10;
                                   }
                               }
                               else if ( child->myWins < child->oppWins )
                               {
                                   if ( child->myWins == 0 )
                                   {
                                       child->oppScore += 40;
                                       child->payoff   -= 40;
                                   }
                                   else
                                   {
                                       child->oppScore += 10;
                                       child->payoff   -= 10;
                                   }
                               }
                            }

                            // Add the child.
                            parent->children.push_back(child);
                        }
                    }
                }
            }
        }
    }
    else
    {
        // If there are two tricks in play, they are starting a new trick.
        if ( oppTrick || !myTrick )
        {
            for ( int i = 0; i < 4; i++ )
            {
                for ( int j = 0; j < 8; j++ )
                {
                    if ( parent->state[i][j] == CardArray::UNKNOWN )
                    {
                        Node* child = new Node();

                        // Allocate space for state.
                        child->state = new CardArray::Type*[4];
                        for ( int m = 0; m < 4; m++ )
                            child->state[m] = new CardArray::Type[8];

                        // Initialize the state.
                        for ( int k = 0; k < 4; k++ )
                        {
                            for ( int l = 0; l < 8; l++ )
                            {
                                child->state[k][l] = parent->state[k][l];
                                if ( child->state[k][l] == CardArray::PLAYERTRICK ||
                                     child->state[k][l] == CardArray::CPUTRICK )
                                {
                                    child->state[k][l] = CardArray::PREVIOUSTRICKS;
                                }
                            }
                        }

                        if ( p == PLAYER2 )
                            child->state[i][j] = CardArray::PLAYERTRICK;
                        else
                            child->state[i][j] = CardArray::CPUTRICK;

                        // Update node information.
                        child->myTurnNext  = true;
                        child->piquetGiven = parent->piquetGiven;
                        child->myWins      = parent->myWins;
                        child->oppWins     = parent->oppWins;
                        child->myScore     = parent->myScore;
                        child->oppScore    = parent->oppScore + 1;
                        child->payoff      = parent->payoff - 1;

                        // Special score modifiers.
                        if ( !child->piquetGiven &&
                             (child->oppScore >= 30 && child->myScore == 0) )
                        {
                            child->oppScore += 30;
                            child->payoff   -= 30;
                            child->piquetGiven = true;
                        }

                        // Add the child.
                        parent->children.push_back(child);
                    }
                }
            }
        }
        else
        {
            for ( int i = 0; i < 4; i++ )
            {
                for ( int j = 0; j < 8; j++ )
                {
                    if ( parent->state[i][j] == CardArray::UNKNOWN )
                    {
                        Node* child = new Node();

                        // Allocate space for state.
                        child->state = new CardArray::Type*[4];
                        for ( int m = 0; m < 4; m++ )
                            child->state[m] = new CardArray::Type[8];

                        // Initialize the state.
                        for ( int k = 0; k < 4; k++ )
                        {
                            for ( int l = 0; l < 8; l++ )
                            {
                                child->state[k][l] = parent->state[k][l];
                            }
                        }

                        if ( p == PLAYER1 )
                            child->state[i][j] = CardArray::PLAYERTRICK;
                        else
                            child->state[i][j] = CardArray::CPUTRICK;

                        // Set the payoff.
                        if ( myTrickLoc[0] == i && myTrickLoc[1] < j )
                        {
                            child->myTurnNext  = false;
                            child->myWins      = parent->myWins;
                            child->myScore     = parent->myScore;
                            child->oppWins     = parent->oppWins + 1;
                            child->oppScore    = parent->oppScore + 1;
                            child->payoff      = parent->payoff - 1;

                            // Check for final victory.
                            if ( child->myWins + child->oppWins == 12 )
                            {
                               child->oppScore++;
                               child->payoff--;
                            }

                            // Special score modifiers.
                            if ( !child->piquetGiven &&
                                 (child->oppScore >= 30 && child->myScore == 0) )
                            {
                                child->oppScore += 30;
                                child->payoff   -= 30;
                                child->piquetGiven = true;
                            }
                        }
                        else
                        {
                            child->myTurnNext  = true;
                            child->myWins      = parent->myWins + 1;
                            child->myScore     = parent->myScore;
                            child->oppWins     = parent->oppWins;
                            child->oppScore    = parent->oppScore;
                            child->payoff      = parent->payoff + 1;

                            // Check for final victory.
                            if ( child->myWins + child->oppWins == 12 )
                            {
                               child->myScore++;
                               child->payoff++;

                               // Special score modifiers.
                               if ( !child->piquetGiven &&
                                    (child->myScore >= 30 && child->oppScore == 0) )
                               {
                                   child->myScore += 30;
                                   child->payoff  += 30;
                                   child->piquetGiven = true;
                               }
                            }
                        }

                        // Check for final special scores.
                        if ( child->myWins + child->oppWins == 12 )
                        {
                           if ( child->myWins > child->oppWins )
                           {
                               if ( child->oppWins == 0 )
                               {
                                   child->myScore += 40;
                                   child->payoff  += 40;
                               }
                               else
                               {
                                   child->myScore += 10;
                                   child->payoff  += 10;
                               }
                           }
                           else if ( child->myWins < child->oppWins )
                           {
                               if ( child->myWins == 0 )
                               {
                                   child->oppScore += 40;
                                   child->payoff   -= 40;
                               }
                               else
                               {
                                   child->oppScore += 10;
                                   child->payoff   -= 10;
                               }
                           }
                        }

                        // Add the child.
                        parent->children.push_back(child);
                    }
                }
            }
        }
    }
}



//------------------------------------------------------------------------------
// FreeTree - Free memory allocated to a set of nodes.
//------------------------------------------------------------------------------
void KnowledgeBase::FreeTree(KnowledgeBase::Node* root)
{
    Node* n;
    for ( int i = 0; i < (int)root->children.size(); i++ )
    {
        n = root->children[i];

        FreeTree(n);
    }

    // Free the memory.
    for ( int m = 0; m < 4; m++ )
    {
        delete[] root->state[m];
        root->state[m] = 0;
    }

    delete root->state;
    root->state = 0;

    delete root;
    root = 0;
}


//------------------------------------------------------------------------------
// SelectCardRemovals - Determine the possible cards to be removed.
//------------------------------------------------------------------------------
void KnowledgeBase::SelectCardRemovals(float      e,
                                       CardArray* hand,
                                       CardArray* possibleCards,
                                       CardArray* removedCards)
{
    std::vector<CardEvals*> cardSets;

    // For each card in the hand, evaluate removing it.
    Card* c;
    Card* posCard;
    for ( int i = 0; i < hand->GetSize(); i++ )
    {
        std::vector<float> max;
        std::vector<float> min;

        c = hand->GetCard(0);
        hand->RemoveCard(c, true);

        // Replace the removed card with all possible cards.
        for ( int j = 0; j < possibleCards->GetSize(); j++ )
        {
            posCard = possibleCards->GetCard(j);
            hand->AddCard(posCard, false, true);

            float temp = Evaluate(hand);

            if ( temp > e )
                max.push_back(temp);
            else
                min.push_back(temp);

            hand->RemoveCard(posCard, true);
        }

        // Weight the evaluation with the probability that it will improve/not.
        float maxProb = (float)max.size() / (max.size() + min.size());
        float minProb = (float)min.size() / (max.size() + min.size());

        // Calculate max average.
        float sum = 0;
        for ( int k = 0; k < (int)max.size(); k++ )
            sum += max[k];

        float maxAverage = e;
        if ( max.size() > 0 )
            maxAverage = sum / max.size();

        // Calculate min average.
        sum = 0;
        for ( int k = 0; k < (int)min.size(); k++ )
            sum += min[k];

        float minAverage = e;
        if ( min.size() > 0 )
            minAverage = sum / min.size();

        float anE = e + ((maxAverage-e) * maxProb) - ((e-minAverage) * minProb);

        // Return the card.
        hand->AddCard(c, false, true);

        // Determine if the card evaluation is better.
        if ( anE > e )
        {
            CardEvals* ev = new CardEvals();

            ev->eval = anE;
            ev->card = c;

            cardSets.push_back(ev);
        }
    }

    // Sort the potentially removable cards.
    std::sort(cardSets.begin(), cardSets.end(), SortFunction);

    // Add potential cards to be removed to the removed CardArray.
    for ( int i = 0; i < (int)cardSets.size(); i++ )
    {
        Card* aCard = cardSets[i]->card;
        removedCards->AddCard(aCard, false, true);
    }

    // Free the memory.
    int size = cardSets.size();
    for ( int i = size-1; i > 0; i-- )
    {
        CardEvals* ev = cardSets[i];

        cardSets.pop_back();
        delete ev;
    }
}


//------------------------------------------------------------------------------
// Evaluate - Perform a score evaluation on a given hand.
//------------------------------------------------------------------------------
float KnowledgeBase::Evaluate(CardArray* hand)
{
    // Gather information about the given hand.
    // Calculate an offset based on the point value of the cards to avoid
    // equivalent hand evaluations.
    float e = 0;
    int  handSuits[4] = { 0 };
    bool handStatus[4][8] = { false };
    int  handValue = 0;
    for ( int i = 0; i < hand->GetSize(); i++ )
    {
        Card* c = hand->GetCard(i);

        handSuits[c->GetSuit()]++;
        handStatus[c->GetSuit()][c->GetRank()-7] = true;

        handValue += c->GetRank();
    }

    // Evaluation based on high cards.
    e += ((handValue / 156.0) * 11);

    // Calculate the point.
    int max = 0;
    for ( int i = 0; i < 4; i++ )
    {
        if ( handSuits[i] > max )
            max = handSuits[i];
    }

    e += max;

    // Calculate the sequences.
    max = 0;
    for ( int i = 0; i < 4; i++ )
    {
        int seq = 0;
        for ( int j = 0; j < 8; j++ )
        {
            if ( handStatus[i][j] )
            {
                seq++;
                if ( j == 7 && seq >= 3 )
                    max += (seq < 5) ? seq : seq + 10;
            }
            else if ( seq >= 3 )
            {
                max += (seq < 5) ? seq : seq + 10;
                seq = 0;
            }
            else
            {
                seq = 0;
            }
        }
    }

    e += max;

    // Calculate the sets.
    max = 0;
    for ( int i = 3; i < 8; i++ )
    {
        int set = 0;
        for ( int j = 0; j < 4; j++ )
        {
            if ( handStatus[i][j] )
                set++;
        }

        if ( set >= 3 )
            max += (set == 3) ? 3 : 14;
    }

    e += max;

    return e;
}


//------------------------------------------------------------------------------
// GenerateElementArray - Generate a vector of items representing the cpu' hand.
//------------------------------------------------------------------------------
std::vector<KnowledgeBase::McsElement*> KnowledgeBase::GenerateElementArray(CardArray* cpuHand)
{
    std::vector<McsElement*> hand;
    McsElement* e;

    // Add an additional items for choosing not to discard max elements.
    for ( int i = 0; i < 5; i++ )
    {
        e              = new McsElement();
        e->suit        = Card::NOSUIT;
        e->rank        = Card::NORANK;
        e->numWins     = 0;
        e->numPlays    = 0;
        e->numDiscards = 5-i;

        hand.push_back(e);
    }

    for ( int i = 0; i < cpuHand->GetSize(); i++ )
    {
        e = new McsElement();

        e->suit        = cpuHand->GetCard(i)->GetSuit();
        e->rank        = cpuHand->GetCard(i)->GetRank();
        e->numWins     = 0;
        e->numPlays    = 0;
        e->numDiscards = 0;

        hand.push_back(e);
    }

    return hand;
}


//------------------------------------------------------------------------------
// GenOppHands - Generate a vector of items representing a set of possible
//               hands the opponent could have.
//------------------------------------------------------------------------------
std::vector<std::vector<KnowledgeBase::McsElement*> > KnowledgeBase::GenOppHands(int numHands)
{
    std::vector<McsElement*> possCards;

    // Create a vector of possible cards to choose.
    for ( int i = 0; i < 4; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            if ( cardStatus[i][j]->location == CardArray::UNKNOWN )
            {
                McsElement* e = new McsElement();

                e->suit        = (Card::Suit)i;
                e->rank        = (Card::Rank)(j+7);
                e->numWins     = 0;
                e->numPlays    = 0;
                e->numDiscards = 0;

                possCards.push_back(e);
            }
        }
    }

    // Shuffle the possible cards and create a set of hands.
    std::vector<std::vector<McsElement*> > possHands;
    for ( int i = 0; i < numHands; i++ )
    {
        std::vector<McsElement*> v;

        std::srand(time(0));
        std::random_shuffle(possCards.begin(), possCards.end());

        for ( int j = 0; j < 12; j++ )
        {
            v.push_back(possCards[j]);
        }

        possHands.push_back(v);
    }

    return possHands;
}


//------------------------------------------------------------------------------
// Mcs - Modified Monte Carlo method for selecting cards to exchange.
//------------------------------------------------------------------------------
void KnowledgeBase::Mcs(std::vector<KnowledgeBase::McsElement*> myHand,
                        std::vector<std::vector<KnowledgeBase::McsElement*> > oppHands,
                        int talonSize, int numSimulations)
{
    // For each possible opponent hands
    for ( int i = 0; i < (int)oppHands.size(); i++ )
    {
        std::vector<McsElement*> possHand;
        for ( int j = 0; j < 12; j++ )
        {
            possHand.push_back(oppHands.at(i).at(j));
        }
        bool seenCards[4][8] = { false };

        // Determine possible cards we could pick up.
        for ( int j = 0; j < (int)myHand.size(); j++ )
        {
            McsElement* e = myHand[j];

            if ( e->suit != Card::NOSUIT )
                seenCards[(int)e->suit][(int)(e->rank-7)] = true;
        }

        for ( int j = 0; j < (int)possHand.size(); j++ )
        {
            McsElement* e = possHand.at(j);

            if ( e->suit != Card::NOSUIT )
                seenCards[(int)e->suit][(int)(e->rank-7)] = true;
        }

        std::vector<McsElement*> possCards;
        for ( int j = 0; j < 4; j++ )
        {
            for ( int k = 0; k < 8; k++ )
            {
                if ( !seenCards[j][k] )
                {
                    McsElement* e = new McsElement();

                    e->suit        = (Card::Suit)j;
                    e->rank        = (Card::Rank)(k+7);
                    e->numWins     = 0;
                    e->numPlays    = 0;
                    e->numDiscards = 0;

                    possCards.push_back(e);
                }
            }
        }

        // Randomize the vector of possible cards.
        std::srand(time(0));
        std::random_shuffle(possCards.begin(), possCards.end());

        // Select cards to discard based on UCT. Start by determining how
        // many cards we are discarding.
        int min = (talonSize < 5) ? (5 - talonSize) : 0;
        int selectedIndex[6]  = { -1 };
        float selectedScores[6] = { -1 };
        for ( int j = min; j < 5; j++ )
        {
            float u = Uct(myHand[j], numSimulations);
            if ( u > selectedScores[0] )
            {
                selectedScores[0] = u;
                selectedIndex[0]  = j;
            }
        }

        for ( int j = 5; j < (int)myHand.size(); j++ )
        {
            float u = Uct(myHand[j], numSimulations);

            int  k    = 1;
            bool done = false;
            while ( k < 6 && !done )
            {
                if ( u > selectedScores[k] )
                {
                    selectedScores[k] = u;
                    selectedIndex[k]  = j;
                    done = true;
                }
                k++;
            }
        }

        // Determine the winner of that hand based on declarations, replacing
        // discarded cards by an equal number of random possible cards.
        // Start by sorting the scores in case we are discarding less than 5.
        for ( int j = 2; j < 6; j++ )
        {
            int score = selectedScores[j];
            int index = selectedIndex[j];

            int innerIndex = j;
            while ( innerIndex > 1 && score > selectedScores[innerIndex-1] )
            {
                // Swap the scores.
                selectedScores[innerIndex] = selectedScores[innerIndex-1];

                // Swap the corresponding indexes.
                selectedIndex[innerIndex]  = selectedIndex[innerIndex-1];

                innerIndex--;
            }

            // Put the score and index in it's correct place.
            selectedScores[innerIndex] = score;
            selectedIndex[innerIndex]  = index;
        }

        // Now replace the selected cards with an equal number of possible cards.
        int numCards = myHand[selectedIndex[0]]->numDiscards;
        std::vector<McsElement*> newHand;
        for ( int j = 5; j < (int)myHand.size(); j++ )
        {
            newHand.push_back(myHand[j]);
        }

        for ( int j = 1; j <= numCards; j++ )
        {
            newHand[selectedIndex[j]-5] = possCards[j-1];
        }

        // Now play out the declarations to determine the winner.
        bool win = ExecuteDecTest(newHand, possHand);

        // Update the information.
        for ( int j = 0; j <= numCards; j++ )
        {
            myHand[selectedIndex[j]]->numPlays++;

            if ( win )
                myHand[selectedIndex[j]]->numWins++;
        }

        // Free the possible cards vector.
        int max = possCards.size();
        for ( int j = max; j >= 0; j-- )
        {
            possCards.pop_back();
        }

        numSimulations++;
    }
}


//------------------------------------------------------------------------------
// Uct - Uct algorithm.
//------------------------------------------------------------------------------
float KnowledgeBase::Uct(KnowledgeBase::McsElement* e, int numSim)
{
    float exploitation = 0;
    float exploration  = 0;

    if ( e->numPlays == 0 )
    {
        exploitation = 0;
        if ( numSim == 0)
            exploration  = sqrt(2);
        else
            exploration  = 5;
    }
    else
    {
        exploitation = (float)e->numWins / e->numPlays;
        exploration  = sqrt(2) * sqrt(log(numSim) / e->numPlays);
    }

    return (exploitation + exploration);
}


//------------------------------------------------------------------------------
// ExecuteDecTest - Execute declarations to determine the winner.
//------------------------------------------------------------------------------
bool KnowledgeBase::ExecuteDecTest(std::vector<KnowledgeBase::McsElement*> myHand,
                                   std::vector<KnowledgeBase::McsElement*> oppHand)
{
    int l_myScore  = 0;
    int l_oppScore = 0;

    // Gather information about the given hands.
    int  myHandSuits[4]      = { 0 };
    bool myHandStatus[4][8]  = { false };
    int  oppHandSuits[4]     = { 0 };
    bool oppHandStatus[4][8] = { false };

    for ( int i = 0; i < (int)myHand.size(); i++ )
    {
        McsElement* e1 = myHand[i];
        McsElement* e2 = oppHand[i];

        myHandSuits[e1->suit]++;
        myHandStatus[e1->suit][e1->rank-7] = true;
        oppHandSuits[e2->suit]++;
        oppHandStatus[e2->suit][e2->rank-7] = true;
    }

    // Calculate the point winner.
    int myMax       = 0;
    int myBestSuit  = -1;
    int oppMax      = 0;
    int oppBestSuit = -1;
    for ( int i = 0; i < 4; i++ )
    {
        if ( myHandSuits[i] > myMax )
        {
            myMax      = myHandSuits[i];
            myBestSuit = i;
        }
        if ( oppHandSuits[i] > oppMax )
        {
            oppMax      = oppHandSuits[i];
            oppBestSuit = i;
        }
    }

    // Check for draws.
    if ( myMax == oppMax && myMax != 0 )
    {
        int myTotal  = 0;
        int oppTotal = 0;

        for ( int i = 0; i < 8; i++ )
        {
            if ( myHandStatus[myBestSuit][i] )
            {
                if ( i < 4 )
                    myTotal += (i+7);
                else if ( i < 7 )
                    myTotal += 10;
                else
                    myTotal += 11;
            }

            if ( oppHandStatus[oppBestSuit][i] )
            {
                if ( i < 4 )
                    oppTotal += (i+7);
                else if ( i < 7 )
                    oppTotal += 10;
                else
                    oppTotal += 11;
            }
        }

        if ( myTotal >= oppTotal )
        {
            if ( myTotal > oppTotal )
                oppMax = 0;
        }
        else
        {
            myMax = 0;
        }
    }

    // Update score.
    if ( myMax >= oppMax )
    {
        if ( myMax > oppMax )
            l_myScore += myMax;
    }
    else
    {
        l_oppScore += oppMax;
    }

    // Calculate the sequence.
    myMax  = 0;
    oppMax = 0;
    for ( int i = 0; i < 4; i++ )
    {
        int mySeq  = 0;
        int oppSeq = 0;
        for ( int j = 0; j < 8; j++ )
        {
            // My Sequence.
            if ( myHandStatus[i][j] )
            {
                mySeq++;
                if ( j == 7 && mySeq > myMax && mySeq >= 3 )
                {
                    myBestSuit = i;
                    myMax = mySeq;
                }
            }
            else if ( mySeq > myMax && mySeq >= 3 )
            {
                myBestSuit = i;
                myMax = mySeq;
                mySeq = 0;
            }
            else
            {
                mySeq = 0;
            }

            // Opp Sequences.
            if ( oppHandStatus[i][j] )
            {
                oppSeq++;
                if ( j == 7 && oppSeq > oppMax && oppSeq >= 3 )
                {
                    oppBestSuit = i;
                    oppMax = oppSeq;
                }
            }
            else if ( oppSeq > oppMax && oppSeq >= 3 )
            {
                oppBestSuit = i;
                oppMax = oppSeq;
                oppSeq = 0;
            }
            else
            {
                oppSeq = 0;
            }
        }
    }

    myMax  = (myMax < 5)  ? myMax  : myMax  + 10;
    oppMax = (oppMax < 5) ? oppMax : oppMax + 10;

    // Check for draws.
    if ( myMax == oppMax && myMax != 0 )
    {
        int i = 7;
        bool found = false;
        while ( i >= 0 && !found )
        {
            if ( myHandStatus[myBestSuit][i] )
            {
                found = true;
                i++;
            }
            i--;
        }

        int j = 7;
        found = false;
        while ( j >= 0 && !found )
        {
            if ( oppHandStatus[myBestSuit][j] )
            {
                found = true;
                j++;
            }
            j--;
        }

        if ( i >= j )
        {
            if ( i > j )
                oppMax = 0;
        }
        else
        {
            myMax = 0;
        }
    }

    // Update score.
    if ( myMax >= oppMax )
    {
        if ( myMax > oppMax )
            l_myScore += myMax;
    }
    else
    {
        l_oppScore += oppMax;
    }

    // Calculate the sets.
    myMax  = 0;
    oppMax = 0;
    int myHiCard  = 0;
    int oppHiCard = 0;
    for ( int i = 3; i < 8; i++ )
    {
        int mySet  = 0;
        int oppSet = 0;
        for ( int j = 0; j < 4; j++ )
        {
            if ( myHandStatus[i][j] )
                mySet++;

            if ( oppHandStatus[i][j] )
                oppSet++;
        }

        if ( mySet > myMax && mySet >= 3 )
        {
            myHiCard = i;
            myMax = mySet;
        }

        if ( oppSet > oppMax && oppSet >= 3 )
        {
            oppHiCard = i;
            oppMax = oppSet;
        }
    }

    myMax  = (myMax == 3)  ? myMax  : myMax  + 10;
    oppMax = (oppMax < 5) ? oppMax : oppMax + 10;

    // Check for draws.
    if ( myMax == oppMax && myMax != 0 )
    {
        if ( myHiCard >= oppHiCard )
        {
            if ( myHiCard > oppHiCard )
                oppMax = 0;
        }
        else
        {
            myMax = 0;
        }
    }

    // Update score.
    if ( myMax >= oppMax )
    {
        if ( myMax > oppMax )
            l_myScore += myMax;
    }
    else
    {
        l_oppScore += oppMax;
    }

    return (l_myScore > l_oppScore);
}
