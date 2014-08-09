#include "CardArray.h"

// Default Constructor.
CardArray::CardArray(void) :
    cards(0)
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
        removedCard = cards[index];

        // Remove the card.
        cards.erase(cards.begin() + index);
    }

    return removedCard;
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
    return cards.size();
}
