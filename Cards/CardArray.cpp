#include "CardArray.h"

// Constructor.
CardArray::CardArray(void) :
    size(0)
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
    cards[size] = newCard;
    size++;
}

// Remove the top card in this array.
void CardArray::RemoveCard(int index)
{
    // Make sure there are cards in the array.
    if ( size > 0 )
    {
        // Remove the card.
        delete cards[index];
        cards[index] = 0;
        size--;
    }
}

Card* CardArray::GetCard(int index)
{
    return cards[index];
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
    return size;
}
