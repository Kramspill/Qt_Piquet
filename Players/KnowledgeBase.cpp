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
                        child->payoff      = parent->payoff + 1;

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
                        child->payoff      = parent->payoff + 1;

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
