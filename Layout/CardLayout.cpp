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
CardLayout::CardLayout(QWidget* parent) :
    QLayout(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardLayout::CardLayout(CardLayout&) :
    QLayout()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardLayout::~CardLayout(void)
{
    Destroy();
}


//------------------------------------------------------------------------------
// Destroy - Cleans up the memory allocated by this layout.
//------------------------------------------------------------------------------
void CardLayout::Destroy(void)
{
    QLayoutItem *item;

    while ( (item = takeAt(0)) )
        delete item;
}


//------------------------------------------------------------------------------
// addItem - Add items to this layout.
//------------------------------------------------------------------------------
void CardLayout::addItem(QLayoutItem* item)
{
    items.append(item);
}


//------------------------------------------------------------------------------
// setGeometry - How the layout is defined.
//------------------------------------------------------------------------------
void CardLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);

    if (items.size() == 0)
        return;

    int width  = rect.width()  - (items.size() - 1) * spacing();
    int height = rect.height() - (items.size() - 1) * spacing();

    int index = 0;
    while ( index < items.size() )
    {
        QLayoutItem* item = items.at(index);
        QRect geometry(rect.x() + index * spacing(),
                       rect.y() + index * spacing(),
                       width,
                       height);

        item->setGeometry(geometry);
        index++;
    }
}


//------------------------------------------------------------------------------
// sizeHint - The preferred size of this layout.
//------------------------------------------------------------------------------
QSize CardLayout::sizeHint(void) const
{
    QSize size(0,0);

    int numOfItems = items.size();
    if (numOfItems > 0)
        size = QSize(100,70);

    int index = 0;
    while ( index < numOfItems )
    {
        QLayoutItem* item = items.at(index);
        size = size.expandedTo(item->sizeHint());
        index++;
    }

    return size + numOfItems * QSize(spacing(), spacing());
}


//------------------------------------------------------------------------------
// itemAt - Retrieve a layout item at the specified index.
//------------------------------------------------------------------------------
QLayoutItem* CardLayout::itemAt(int index) const
{
    return items.value(index);
}


//------------------------------------------------------------------------------
// takeAt - Remove a layout item at the given index.
//------------------------------------------------------------------------------
QLayoutItem* CardLayout::takeAt(int index)
{
    bool validRange = index >= 0 && index < items.size();

    return validRange ? items.takeAt(index) : 0;
}
