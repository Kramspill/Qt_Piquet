//------------------------------------------------------------------------------
// Filename: CardLayout.cpp
// Description: The layout that is used for the CardArrays.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "CardLayout.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CardLayout::CardLayout(Type aType, QGraphicsLayoutItem* parent) :
    QGraphicsLayout(parent),
    type(aType)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardLayout::CardLayout(CardLayout&) :
    QGraphicsLayout()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardLayout::~CardLayout(void)
{
}


//------------------------------------------------------------------------------
// addItem - Add an item to this layout.
//------------------------------------------------------------------------------
void CardLayout::AddCard(Card* card, bool temp)
{
    this->addChildLayoutItem(card);
    setGeometry(geometry());
    cards.append(card);
}


//------------------------------------------------------------------------------
// GetItemIndex - Get the index of an item in this layout.
//------------------------------------------------------------------------------
int CardLayout::GetCardIndex(Card* card)
{
    return cards.indexOf(card);
}


//------------------------------------------------------------------------------
// RemoveCard - Remove a card from this layout. If no card is specified, then
//              the top card is removed.
//------------------------------------------------------------------------------
Card* CardLayout::RemoveCard(Card* card)
{
    Card* removedCard;

    if ( !card )
    {
        removedCard = cards.first();
        cards.removeFirst();
    }
    else
    {
        cards.takeAt(cards.indexOf(card));
    }

    return removedCard;
}


//------------------------------------------------------------------------------
// setGeometry - How the layout is defined.
//------------------------------------------------------------------------------
void CardLayout::setGeometry(const QRectF& rect)
{
    QGraphicsLayout::setGeometry(rect);

    if (cards.size() == 0)
        return;

    int width  = rect.width()  - (cards.size() - 1);
    int height = rect.height() - (cards.size() - 1);

    int index = 0;
    while ( index < cards.size() )
    {
        Card* card = cards.at(index);
        QRect geometry(rect.x() + index,
                       rect.y() + index,
                       width,
                       height);

        card->setGeometry(geometry);
        index++;
    }
}


//------------------------------------------------------------------------------
// sizeHint - The preferred size of this layout.
//------------------------------------------------------------------------------
QSizeF CardLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF size(0,0);

    int numOfItems = cards.size();
    if (numOfItems > 0)
        size = QSizeF(50,30);

    int index = 0;
    /*while ( index < numOfItems )
    {
        Card* card = cards.at(index);
        size = size.expandedTo(card->sizeHint(Qt::PreferredSize));
        index++;
    }*/

    return size;// + numOfItems * QSizeF(1, 1);
}


//------------------------------------------------------------------------------
// count - Number of items in this layout.
//------------------------------------------------------------------------------
int CardLayout::count(void) const
{
  return cards.size();
}


//------------------------------------------------------------------------------
// itemAt - Retrieve a layout item at the specified index.
//------------------------------------------------------------------------------
Card* CardLayout::itemAt(int index) const
{
    return cards.value(index);
}


//------------------------------------------------------------------------------
// removeAt - Remove a layout item at the given index.
//------------------------------------------------------------------------------
void CardLayout::removeAt(int index)
{
    if ( index >= 0 && index < cards.count() )
        cards.takeAt(index);
}


//------------------------------------------------------------------------------
// Shuffle - Randomize this CardArray.
//------------------------------------------------------------------------------
void CardLayout::Shuffle(void)
{

}


//------------------------------------------------------------------------------
// Sort - Sort this CardArray.
//------------------------------------------------------------------------------
void CardLayout::Sort(void)
{

}


//------------------------------------------------------------------------------
// ResetZPositions - Reset the zPositions in this array.
//------------------------------------------------------------------------------
void CardLayout::ResetZPositions(void)
{
    Card* card;
    int   arraySize = count();

    for ( int index = 0; index < arraySize; index++ )
    {
        card = itemAt(index);
        card->SetPosition(card->GetPosition(), index + 1);
    }
}

