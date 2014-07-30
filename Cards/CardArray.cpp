#include "CardArray.h"

// Constructor.
CardArray::CardArray(void) :
    size(0),
    cards(0)
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
void CardArray::AddCard(Card newCard)
{
    // Allocate space for the new card.
    Card* card = new Card(newCard);

    // Check if the array is empty.
    if ( !cards )
    {
        topCard = card;
    }

    // Add the new card to the array.
    cards = card;
    cards++;
    size++;
}

// Remove the top card in this array.
bool CardArray::RemoveTopCard(void)
{
    bool success = false;

    // Make sure there are cards in the array.
    if ( size > 0 )
    {
        // Remove the top card.
        Card* tempCard = topCard++;
        delete tempCard;
        size--;

        // If this was the last card, then
        // there is no longer a top card.
        if ( size == 0 )
        {
            topCard = 0;
        }

        success = true;
    }

    return success;
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
void CardArray::Stagger(CardArray::StaggerType staggerType)
{

}

// Accessor for CardArray's size member.
unsigned int CardArray::GetSize(void)
{
    return size;
}
