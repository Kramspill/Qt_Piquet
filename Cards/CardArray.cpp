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
CardArray::CardArray(CardArray::CardArrayType arrayType) :
    cards(0),
    cardArrayType(arrayType)
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
void CardArray::AddCard(Card* newCard)
{
    // Add the new card to the array.
    cards.push_back(newCard);

    // Set the cards position and update
    // the next position.
    newCard->SetPosition(nextCardPosition);
    UpdateNextPosition();
}


//------------------------------------------------------------------------------
// RemoveCard - Remove a card from this array. Doesn't free the memory
//              associated with the card but instead returns a pointer to the
//              removed Card.
//------------------------------------------------------------------------------
Card* CardArray::RemoveCard(int index)
{
    Card* removedCard = 0;

    // Make sure there are cards in the array
    // and a card exists at the given index.
    if ( cards.size() > 0 && cards[index] )
    {
        removedCard = cards.front();//cards[index];

        // Remove the card.
        cards.erase(cards.begin());// + index);

        // Update the next card position.
        UpdateNextPosition();
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
// UpdateNextPosition - Update the position that the next card added to this
//                      array will be given.
//------------------------------------------------------------------------------
void CardArray::UpdateNextPosition(int x, int y)
{
    // Check if this is the initial setup.
    if ( x != -1 && y != -1)
    {
        nextCardPosition = QPointF(x, y);
    }
    else if ( zPositionOnly )
    {
        nextCardPosition = QPointF(nextCardPosition.x(),
                                   nextCardPosition.y() - 1);
    }
    else
    {
        nextCardPosition = QPointF(nextCardPosition.x() + 16,
                                   nextCardPosition.y());
    }
}


//------------------------------------------------------------------------------
// Shuffle - Randomize this CardArray.
//------------------------------------------------------------------------------
void CardArray::Shuffle(void)
{

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
void CardArray::Stagger(CardArray::StaggerType /*staggerType*/)
{

}


//------------------------------------------------------------------------------
// GetSize - Accessor for CardArray's size member variable.
//------------------------------------------------------------------------------
int CardArray::GetSize(void)
{
    return cards.size();
}


//------------------------------------------------------------------------------
// GetCardArrayType - Accessor for CardArray's cardArrayType member variable.
//------------------------------------------------------------------------------
CardArray::CardArrayType CardArray::GetCardArrayType(void)
{
    return cardArrayType;
}


//------------------------------------------------------------------------------
// SetZPosOnly - Mutator for CardArray's zPositionOnly member variable.
//------------------------------------------------------------------------------
void CardArray::SetZPosOnly(bool zPosOnly)
{
    zPositionOnly = zPosOnly;
}
