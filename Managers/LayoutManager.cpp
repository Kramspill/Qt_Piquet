//------------------------------------------------------------------------------
// Filename: LayoutManager.cpp
// Description: Manages the layouts in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "LayoutManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
LayoutManager::LayoutManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
LayoutManager::LayoutManager(LayoutManager&)
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
LayoutManager::~LayoutManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize this manager.
//------------------------------------------------------------------------------
void LayoutManager::Initialize(void)
{
    // Allocate memory for the members.
    mainLayout           = new QGraphicsAnchorLayout();
    playingField         = new QGraphicsAnchorLayout();
    scoreLayout          = new QGraphicsAnchorLayout(); // Temp type
    dialogLayout         = new QGraphicsAnchorLayout(); // Temp type
    deckLayout           = new CardLayout();
    playerCardsLayout    = new CardLayout();
    cpuCardsLayout       = new CardLayout();
    talonLayout          = new CardLayout();
    playerDiscardLayout  = new CardLayout();
    cpuDiscardLayout     = new CardLayout();
    previousTricksLayout = new CardLayout();
    currentTrickLayout   = new CardLayout();

    // Position the layouts within the mainLayout.
    PositionLayouts();
}


//------------------------------------------------------------------------------
// Transfer - Transfer an item from one layout to another.
//------------------------------------------------------------------------------
void LayoutManager::Transfer(QGraphicsLayoutItem* item,
                             LayoutManager::Location src,
                             LayoutManager::Location dest)
{
    // Get a pointer to the chosen layouts.
    CardLayout* srcLayout  = GetLayout(src);
    CardLayout* destLayout = GetLayout(dest);

    // Get the index of the item from the source layout.
    int index = srcLayout->GetItemIndex(item);

    // Remove the item from the source and add it to the destination.
    srcLayout->removeAt(index);
    destLayout->AddItem(item);
}


//------------------------------------------------------------------------------
// GetLayout - Get a specific layout (for now only works with CardLayouts).
//------------------------------------------------------------------------------
CardLayout* LayoutManager::GetLayout(LayoutManager::Location layout)
{
    CardLayout* chosenLayout;

    switch ( layout )
    {
        case DECK:
            chosenLayout = deckLayout;
            break;

        case PLAYERHAND:
            chosenLayout = playerCardsLayout;
            break;

        case CPUHAND:
            chosenLayout = cpuCardsLayout;
            break;

        case TALON:
            chosenLayout = talonLayout;
            break;

        case PLAYERDISCARDS:
            chosenLayout = playerDiscardLayout;
            break;

        case CPUDISCARDS:
            chosenLayout = cpuDiscardLayout;
            break;

        case PREVTRICKS:
            chosenLayout = previousTricksLayout;
            break;

        case CURRENTTRICK:
            chosenLayout = currentTrickLayout;
            break;

        default:
            break;
    }

    return chosenLayout;
}


//------------------------------------------------------------------------------
// PositionLayouts - Set the positions of the layouts contained by mainLayout.
//------------------------------------------------------------------------------
void LayoutManager::PositionLayouts(void)
{
    mainLayout->addAnchor(playerCardsLayout, Qt::AnchorTop,
                          mainLayout,        Qt::AnchorTop);
    mainLayout->addAnchor(cpuCardsLayout,    Qt::AnchorBottom,
                          mainLayout,        Qt::AnchorBottom);
    mainLayout->addAnchor(dialogLayout,      Qt::AnchorRight,
                          mainLayout,        Qt::AnchorRight);
    mainLayout->addAnchor(dialogLayout,      Qt::AnchorBottom,
                          mainLayout,        Qt::AnchorBottom);

    // Playing field.
    mainLayout->addAnchor(playingField,      Qt::AnchorTop,
                          mainLayout,        Qt::AnchorTop);
    mainLayout->addAnchor(playingField,      Qt::AnchorBottom,
                          mainLayout,        Qt::AnchorBottom);
    mainLayout->addAnchor(playingField,      Qt::AnchorLeft,
                          mainLayout,        Qt::AnchorLeft);
    mainLayout->addAnchor(playingField,      Qt::AnchorRight,
                          mainLayout,        Qt::AnchorRight);

    // Inside playing field.
    mainLayout->addAnchor(deckLayout,        Qt::AnchorTop,
                          playingField,      Qt::AnchorTop);
    mainLayout->addAnchor(deckLayout,        Qt::AnchorBottom,
                          playingField,      Qt::AnchorBottom);
    mainLayout->addAnchor(deckLayout,        Qt::AnchorLeft,
                          playingField,      Qt::AnchorLeft);
    mainLayout->addAnchor(deckLayout,        Qt::AnchorRight,
                          playingField,      Qt::AnchorRight);
}
