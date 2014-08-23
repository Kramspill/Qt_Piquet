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
CardArray::CardArray(CardArray::CardArrayType arrayType, int x, int y) :
    cards(0),
    selectedCards(0),
    selectionLimit(0),
    cardArrayType(arrayType),
    initialCardPosition(QPointF(x, y)),
    nextCardPosition(QPointF(x, y))
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(CardArray&)
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
                EmitCardMovedSignal(card, true);
            }
            break;

        case DECKSTAGGER:
            for ( int index = 0; index < arraySize; index++ )
            {
                card = GetCard(index);

                newPosition = card->GetPosition();
                newPosition.setY(newPosition.y() - index);

                card->SetPosition(newPosition);
                EmitCardMovedSignal(card, true);
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
void CardArray::CheckSelection(CardArray::SelectionType phase)
{
    Card*      aCard;
    Card::Suit theSuit = Card::NOSUIT;
    int        numOfSelectedCards = selectedCards.size();
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
            break;

        case SET:
            break;

        default:
            break;
    }

    if ( valid )
        emit SignalValidSelection();
}


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
// GetCardArrayType - Accessor for CardArray's cardArrayType member variable.
//------------------------------------------------------------------------------
CardArray::CardArrayType CardArray::GetCardArrayType(void)
{
    return cardArrayType;
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
        EmitCardMovedSignal(addedCard, noAnimation);
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

    switch ( cardArrayType )
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

                    // Inform the card that it has moved.
                    emit card->CardMoved(false);
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

                    // Inform the card that it has moved.
                    emit card->CardMoved(false);
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
// EmitCardMovedSignal - Send a signal to the card, informing it that it has
//                       moved.
//------------------------------------------------------------------------------
void CardArray::EmitCardMovedSignal(Card* card, bool noAnimation)
{
    // Emit a signal to update the animation regardless of where the card is
    // going.
    emit card->CardMoved(noAnimation);

    // Emit a signal to tell the card to change states.
    switch ( cardArrayType )
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
