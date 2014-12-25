//------------------------------------------------------------------------------
// Filename: CardArray.cpp
// Description: Represents an array of cards (stored as a vector).
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "CardArray.h"


//------------------------------------------------------------------------------
// Default Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(void)
{
}


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(CardArray::Type arrayType, int x, int y) :
    cards(0),
    selectedCards(0),
    selectionLimit(0),
    type(arrayType),
    initialCardPosition(QPointF(x, y)),
    nextCardPosition(QPointF(x, y))
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(CardArray&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardArray::~CardArray(void)
{
}


//------------------------------------------------------------------------------
// AddCard - Add a card to the CardArray.
//------------------------------------------------------------------------------
void CardArray::AddCard(Card* newCard, bool initialCardCreation)
{
    // Add the new card to the array.
    cards.push_back(newCard);

    // Update the position and state of the cards.
    UpdateCardPositions(newCard, initialCardCreation);
}


//------------------------------------------------------------------------------
// RemoveCard - Remove a given card from this array. Doesn't free the memory
//              associated with the card.
//------------------------------------------------------------------------------
void CardArray::RemoveCard(Card* aCard)
{
    std::vector<Card*>::iterator iterator;

    // Locate the card and remove it.
    iterator = std::find(cards.begin(), cards.end(), aCard);
    cards.erase(iterator);

    UpdateCardPositions();
}


//------------------------------------------------------------------------------
// RemoveTopCard - Remove the last card from this array. Doesn't free the memory
//                 associated with the card but instead returns a pointer to the
//                 removed Card.
//------------------------------------------------------------------------------
Card* CardArray::RemoveTopCard(void)
{
    Card* removedCard = 0;

    // Make sure there are cards in the array
    // and a card exists at the given index.
    if ( cards.size() > 0 )
    {
        removedCard = cards.back();

        // Remove the card.
        cards.pop_back();

        // Clean up the card array and update the next card position.
        UpdateCardPositions();
    }

    return removedCard;
}


//------------------------------------------------------------------------------
// GetCard - Return a card from this CardArray at the given index.
//------------------------------------------------------------------------------
Card* CardArray::GetCard(int index)
{
    return cards[index];
}


//------------------------------------------------------------------------------
// Shuffle - Randomize this CardArray.
//------------------------------------------------------------------------------
void CardArray::Shuffle(void)
{
    // Shuffle the cards.
    std::srand(std::time(0));
    std::random_shuffle(cards.begin(), cards.end());

    ResetZPositions();
}


//------------------------------------------------------------------------------
// Sort - Sort this CardArray.
//------------------------------------------------------------------------------
void CardArray::Sort(void)
{

}


//------------------------------------------------------------------------------
// Stagger - Visually stagger the cards in this CardArray.
//------------------------------------------------------------------------------
void CardArray::Stagger(CardArray::StaggerType staggerType)
{
    QPointF newPosition;
    Card*   card;
    int     arraySize = GetSize();

    switch ( staggerType )
    {
        case NOSTAGGER:
            newPosition = QPointF(nextCardPosition.x(),
                                  nextCardPosition.y() + (GetSize() + 1));

            for ( int index = 0; index < arraySize; index++ )
            {
                card = GetCard(index);

                card->SetPosition(newPosition);
                UpdateCardState(card, true);
            }
            break;

        case DECKSTAGGER:
            for ( int index = 0; index < arraySize; index++ )
            {
                card = GetCard(index);

                newPosition = card->GetPosition();
                newPosition.setY(newPosition.y() - index);

                card->SetPosition(newPosition);
                UpdateCardState(card, true);
            }
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// UpdateCardSelections - Update the the selected cards member vector.
//------------------------------------------------------------------------------
bool CardArray::UpdateCardSelections(Card* card)
{
    bool success = false;

    if ( !card->isSelected() )
    {
        std::vector<Card*>::iterator iterator;

        // The card has been deselected.
        // Remove the card from the selectedCards vector.
        iterator = std::find(selectedCards.begin(), selectedCards.end(), card);
        selectedCards.erase(iterator);

        success = true;
    }
    else if ( selectedCards.size() < selectionLimit )
    {
        // The card has been selected and the limit has not yet been reached.
        // Add the card to the selectedCards vector.
        selectedCards.push_back(card);
        success = true;
    }
    else
    {
        // The card has been selected but the limit has been reached.
        // Set the card to be unselected in the scene.
        card->setSelected(false);
    }

    return success;
}


//------------------------------------------------------------------------------
// CheckSelection - Check selectedCards contains valid Cards for the phase.
//------------------------------------------------------------------------------
bool CardArray::CheckSelection(CardArray::SelectionType phase)
{
    Card*      aCard;
    Card::Suit theSuit;
    Card::Rank theRank;
    int        numOfSelectedCards = selectedCards.size();
    bool       cardBuckets[8] = { false };
    int        i;
    bool       valid = true;

    switch ( phase )
    {
        case POINT:
            // Get the first card to verify which suit to compare the other
            // cards to.
            aCard   = selectedCards[0];
            theSuit = aCard->GetSuit();

            for ( int index = 1; index < numOfSelectedCards; index++ )
            {
                aCard = selectedCards[index];

                if ( aCard->GetSuit() != theSuit )
                {
                    valid = false;
                    index = numOfSelectedCards;
                }
            }
            break;

        case SEQUENCE:
            // Perform a bucket sort then check the cards.
            aCard   = selectedCards[0];
            theSuit = aCard->GetSuit();

            if ( numOfSelectedCards < 3 )
            {
                valid = false;
            }
            else
            {
                for ( int index = 0; index < numOfSelectedCards; index++ )
                {
                    aCard = selectedCards[index];

                    // Place the card in it's bucket.
                    cardBuckets[aCard->GetRank()-7] = true;

                    // Check they are of the same suit during sorting.
                    if ( aCard->GetSuit() != theSuit )
                    {
                    valid = false;
                    index = numOfSelectedCards;
                    }
                }
            }

            // Check the selection order.
            if ( valid )
            {
                i = 0;

                while ( i < 8 && !cardBuckets[i])
                {
                    i++;
                }

                while ( i < 8 && numOfSelectedCards > 0 && cardBuckets[i])
                {
                    i++;
                    numOfSelectedCards--;
                }

                if ( numOfSelectedCards != 0 )
                {
                    valid = false;
                }
            }
            break;

        case SET:
            aCard   = selectedCards[0];
            theSuit = aCard->GetSuit();
            theRank = aCard->GetRank();

            if ( theRank < 10 || numOfSelectedCards < 3 )
            {
                valid = false;
            }
            else
            {
                for ( int index = 1; index < numOfSelectedCards; index++ )
                {
                    aCard = selectedCards[index];

                    // Check they are of the same suit during sorting.
                    if ( aCard->GetSuit() != theSuit &&
                     aCard->GetRank() != theRank )
                    {
                        valid = false;
                        index = numOfSelectedCards;
                    }
                }
            }
            break;

        default:
            break;
    }

    return valid;
}


//------------------------------------------------------------------------------
// GetSelectionScore - Get the score of the current selection.
//------------------------------------------------------------------------------
/*ScoreManager::PhaseScore CardArray::GetSelectionScore(CardArray::SelectionType
                                                      phase)
{
    ScoreManager::PhaseScore score;

    score.numOfCards = GetSelectedCardsSize();
    score.totalValue = 0;

    Card::Rank maxCard = Card::SEVEN;

    // The selection has already been verified so we can make some assumptions
    // in the calculations to speed things up.
    switch ( phase )
    {
        case POINT:
            for ( int index = 0; index < score.numOfCards; index++ )
            {
                score.totalValue += selectedCards[index]->GetValue();
            }
            break;

        case SEQUENCE:
            for ( int index = 0; index < score.numOfCards; index++ )
            {
                if ( selectedCards[index]->GetRank() > maxCard )
                {
                    maxCard = selectedCards[index]->GetRank();
                    score.totalValue = selectedCards[index]->GetRank();
                }
            }
            break;

        case SET:
            score.totalValue = selectedCards[0]->GetRank();
            break;
    }

    return score;
}*/


//------------------------------------------------------------------------------
// RemoveSelectedCard - Remove the first card from the selectedCards vector.
//------------------------------------------------------------------------------
Card* CardArray::RemoveSelectedCard(void)
{
    Card* removedCard = 0;


    if ( selectedCards.size() > 0 )
    {
        removedCard = selectedCards.front();

        // Deselect and prevent further selection of the card.
        removedCard->setSelected(false);
        removedCard->setFlag(QGraphicsItem::ItemIsSelectable, false);

        // Remove the card froom the selectedCards vector.
        selectedCards.erase(selectedCards.begin());

        // Remove the Card from the main array.
        RemoveCard(removedCard);
    }

    return removedCard;
}


//------------------------------------------------------------------------------
// DeselectAll - Deselect all cards in this array.
//------------------------------------------------------------------------------
void CardArray::DeselectAll(void)
{
    Card* card;
    int   numOfSelectedCards = selectedCards.size();

    for ( int index = 0; index < numOfSelectedCards; index++ )
    {
        card = selectedCards[index];
        card->setSelected(false);
    }
}


//------------------------------------------------------------------------------
// GetSize - Return the size of the cards vector.
//------------------------------------------------------------------------------
int CardArray::GetSize(void)
{
    return cards.size();
}


//------------------------------------------------------------------------------
// GetSelectedCardsSize - Return the size of the selectedCards vector.
//------------------------------------------------------------------------------
int CardArray::GetSelectedCardsSize(void)
{
    return selectedCards.size();
}


//------------------------------------------------------------------------------
// GetType - Accessor for CardArray's Type member variable.
//------------------------------------------------------------------------------
CardArray::Type CardArray::GetType(void)
{
    return type;
}


//------------------------------------------------------------------------------
// SetSelectionLimit - Set the limit of how many cards can be selected in this
//                     array at once.
//------------------------------------------------------------------------------
void CardArray::SetSelectionLimit(int newLimit)
{
    selectionLimit = newLimit;
}


//------------------------------------------------------------------------------
// UpdateCardPositions - Update the positions of the cards in the array.
//------------------------------------------------------------------------------
void CardArray::UpdateCardPositions(Card* addedCard, bool noAnimation)
{
    bool newCardAdded = false;

    // If a new card has been added, set it's position and state.
    if ( addedCard )
    {
        addedCard->SetPosition(nextCardPosition, GetSize());
        UpdateCardState(addedCard, noAnimation);
        newCardAdded = true;
    }

    // Clean up the positions of the cards and update the next card's position.
    CleanUpCardPositions(newCardAdded);
}


//------------------------------------------------------------------------------
// CleanUpCardPositions - Clean up the positions of the cards and update the
//                        next card's position.
//------------------------------------------------------------------------------
void CardArray::CleanUpCardPositions(bool newCardAdded)
{
    Card*   card;
    QPointF shiftedPosition;
    int     arraySize = GetSize();

    switch ( type )
    {
        case DECK:
        case TALON:
        case PLAYERDISCARDS:
        case CPUDISCARDS:
            if ( newCardAdded )
            {
                nextCardPosition = QPointF(nextCardPosition.x(),
                                           nextCardPosition.y() - 1);
            }
            else
            {
                nextCardPosition = QPointF(nextCardPosition.x(),
                                           nextCardPosition.y() + 1);
            }
            break;

        case PLAYERHAND:
        case PREVIOUSTRICKS:
            if ( arraySize > 0 )
            {
                // Loop through the array of cards and shift them.
                for ( int index = 0; index < arraySize; index++ )
                {
                    card = GetCard(index);

                    // Get the original position of the card and shift it.
                    shiftedPosition.setX(initialCardPosition.x() -
                                         (10*arraySize) + (index*20));
                    shiftedPosition.setY(card->GetPosition().y());

                    // Set the new position of the card.
                    card->SetPosition(shiftedPosition, index + 1);

                    // Update the card's animation.
                    card->UpdateAnimation(false);
                }

                // Update the position of the next card.
                nextCardPosition = QPointF(shiftedPosition.x() + 20,
                                           shiftedPosition.y());
            }
            else
            {
                nextCardPosition = initialCardPosition;
            }
            break;

        case CPUHAND:
            if ( arraySize > 0 )
            {
                // Loop through the array of cards and shift them.
                for ( int index = 0; index < arraySize; index++ )
                {
                    card = GetCard(index);

                    // Get the original position of the card and shift it.
                    shiftedPosition.setX(initialCardPosition.x() +
                                         (10*arraySize) - (index*20));
                    shiftedPosition.setY(card->GetPosition().y());

                    // Set the new position of the card.
                    card->SetPosition(shiftedPosition, arraySize - index);

                    // Update the card's animation.
                    card->UpdateAnimation(false);
                }

                // Update the position of the next card.
                nextCardPosition = QPointF(shiftedPosition.x() - 20,
                                           shiftedPosition.y());
            }
            else
            {
                nextCardPosition = initialCardPosition;
            }
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// UpdateCardState - Update the state and animation of a card.
//------------------------------------------------------------------------------
void CardArray::UpdateCardState(Card* card, bool noAnimation)
{
    // Update the card's animation regardless of where the card is going.
    card->UpdateAnimation(noAnimation);

    // Emit a signal to tell the card to change states.
    switch ( type )
    {
        case TALON:
            emit card->InTalon();
            break;

        case PLAYERHAND:
            emit card->InPlayerHand();
            break;

        case CPUHAND:
            emit card->InCpuHand();
            break;

        case PLAYERDISCARDS:
            emit card->InPlayerDiscards();
            break;

        case CPUDISCARDS:
            emit card->InCpuDiscards();
            break;

        case PLAYERTRICK:
            emit card->InPlayerTrick();
            break;

        case CPUTRICK:
            emit card->InCpuTrick();
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// ResetZPositions - Reset the zPositions in this array.
//------------------------------------------------------------------------------
void CardArray::ResetZPositions(void)
{
    Card* card;
    int   arraySize = GetSize();

    for ( int index = 0; index < arraySize; index++ )
    {
        card = GetCard(index);
        card->SetPosition(card->GetPosition(), index + 1);
    }
}
