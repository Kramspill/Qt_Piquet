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
CardLayout::CardLayout(QGraphicsLayoutItem* parent) :
    QGraphicsLayout(parent)
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
void CardLayout::AddItem(QGraphicsLayoutItem* layoutItem)
{
    QGraphicsLayout::addChildLayoutItem(layoutItem);

    items.append(layoutItem);
}


//------------------------------------------------------------------------------
// GetItemIndex - Get the index of an item in this layout.
//------------------------------------------------------------------------------
int CardLayout::GetItemIndex(QGraphicsLayoutItem* item)
{
    return items.indexOf(item);
}


//------------------------------------------------------------------------------
// setGeometry - How the layout is defined.
//------------------------------------------------------------------------------
void CardLayout::setGeometry(const QRect& rect)
{
    QGraphicsLayout::setGeometry(rect);

    if (items.size() == 0)
        return;

    int width  = rect.width()  - (items.size() - 1);
    int height = rect.height() - (items.size() - 1);

    int index = 0;
    while ( index < items.size() )
    {
        QGraphicsLayoutItem* item = items.at(index);
        QRect geometry(rect.x() + index,
                       rect.y() + index,
                       width,
                       height);

        item->setGeometry(geometry);
        index++;
    }
}


//------------------------------------------------------------------------------
// sizeHint - The preferred size of this layout.
//------------------------------------------------------------------------------
QSizeF CardLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF size(0,0);

    int numOfItems = items.size();
    if (numOfItems > 0)
        size = QSizeF(100,70);

    int index = 0;
    while ( index < numOfItems )
    {
        //QGraphicsLayoutItem* item = items.at(index);
        //size = size.expandedTo(item->sizeHint(Qt::PreferredSize));
        index++;
    }

    return size + numOfItems * QSizeF(1, 1);
}


//------------------------------------------------------------------------------
// count - Number of items in this layout.
//------------------------------------------------------------------------------
int CardLayout::count(void) const
{
  return items.size();
}


//------------------------------------------------------------------------------
// itemAt - Retrieve a layout item at the specified index.
//------------------------------------------------------------------------------
QGraphicsLayoutItem* CardLayout::itemAt(int index) const
{
    return items.value(index);
}


//------------------------------------------------------------------------------
// removeAt - Remove a layout item at the given index.
//------------------------------------------------------------------------------
void CardLayout::removeAt(int index)
{
    if ( index >= 0 && index < items.count() )
        items.takeAt(index);
}

