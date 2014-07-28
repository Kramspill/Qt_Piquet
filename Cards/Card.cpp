#include "Card.h"

// Constructor.
Card::Card(void)
{
}

// Copy Constructor.
Card::Card(Card&)
{
}

// Destructor.
Card::~Card(void)
{
}

// Accessor for Card's suit member.
Card::Suit Card::GetSuit(void)
{
    return suit;
}

// Accessor for Card's value member.
Card::Value Card::GetValue(void)
{
    return value;
}
