#include "Card.h"

// Constructor.
Card::Card(const QPixmap& pixmap, Suit theSuit, Value theValue) :
    cardImage(pixmap),
    backImage(QPixmap(":/Cards/Back/Red_Back.svg")),
    suit(theSuit),
    value(theValue)
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
