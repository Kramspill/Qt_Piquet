#include "CardArray.h"

// Default Constructor.
CardArray::CardArray(void) :
    cards(0)
{
}

CardArray::CardArray(CardArray::CardArrayType arrayType) :
    cardArrayType(arrayType)
{
}

// Constructor.
CardArray::CardArray(int newSize) :
    cards(newSize)
{
}

// Copy Constructor.
CardArray::CardArray(CardArray&)
{
}

// Destructor.
CardArray::~CardArray(void)
{
}

// Add a card to the CardArray.
void CardArray::AddCard(Card* newCard)
{
    // Add the new card to the array.
    cards.push_back(newCard);

    // Set the cards position and update
    // the next position.
    newCard->SetPosition(nextCardPosition);
    UpdateNextPosition();
}

// Remove a card in this array.
// Doesn't free the memory associated with the card but
// instead returns a pointer to the removed Card.
Card* CardArray::RemoveCard(int index)
{
    Card* removedCard = 0;

    // Make sure there are cards in the array
    // and a card exists at index.
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

Card* CardArray::GetCard(int index)
{
    return cards[index];
}

void CardArray::UpdateNextPosition(int x, int y)
{
    // Check if this is the initial setup.
    if ( x != -1 && y != -1)
    {
        nextCardPosition = QPointF(x, y);
    }
    else if ( zPositionOnly )
    {

    }
    else
    {

    }
}

// Randomize this CardArray.
void CardArray::Shuffle(void)
{

}

// Sort this CardArray.
void CardArray::Sort(void)
{

}

// Visually stagger the cards in this CardArray.
void CardArray::Stagger(CardArray::StaggerType /*staggerType*/)
{

}

// Accessor for CardArray's size member.
int CardArray::GetSize(void)
{
    return cards.size();
}

CardArray::CardArrayType CardArray::GetCardArrayType()
{
    return cardArrayType;
}

void CardArray::SetZPosOnly(bool zPosOnly)
{
    zPositionOnly = zPosOnly;
}
