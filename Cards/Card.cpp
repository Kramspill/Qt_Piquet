#include "Card.h"

// Default Constructor.
Card::Card(void)
{
}

// Constructor.
Card::Card(const QString& svgFileName, Suit theSuit, Value theValue) :
    QGraphicsSvgItem(svgFileName),
    backImage(new QGraphicsSvgItem(":/Cards/Back/Resources/Back/Red_Back.svg")),
    suit(theSuit),
    value(theValue)
{
}

// Copy Constructor.
Card::Card(Card&) : QGraphicsSvgItem()
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

// Accessor for Card's backImage member.
QGraphicsSvgItem* Card::GetBackImage(void)
{
    return backImage;
}
