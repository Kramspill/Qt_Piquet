#include "Card.h"

// Constructor.
Card::Card(void)
{
}

Card::Card(const QPixmap& pixmap, Suit theSuit, Value theValue) :
    cardImage(pixmap),
    backImage(QPixmap(":/Cards/Back/Red_Back.svg")),
    suit(theSuit),
    value(theValue)
{
}

// Constructor that takes another card.
/*Card::Card(Card aCard)
{
    Card(aCard.GetCardImage(), aCard.GetSuit(), aCard.GetValue());
}*/

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

// Accessor for Card's cardImage member.
QPixmap Card::GetCardImage(void)
{
    return cardImage;
}

// Accessor for Card's backImage member.
QPixmap Card::GetBackImage(void)
{
    return backImage;
}
