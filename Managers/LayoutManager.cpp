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
    mainLayout           = new QGraphicsGridLayout();
    playingField         = new QGraphicsGridLayout();
    scoreLayout          = new QGraphicsGridLayout();
    dialogLayout         = new QGraphicsGridLayout();
    /*deckLayout           = new CardLayout();
    playerCardsLayout    = new CardLayout();
    cpuCardsLayout       = new CardLayout();
    talonLayout          = new CardLayout();
    playerDiscardLayout  = new CardLayout();
    cpuDiscardLayout     = new CardLayout();
    previousTricksLayout = new CardLayout();
    playerTrickLayout    = new CardLayout();
    cpuTrickLayout       = new CardLayout();*/

    // Position the layouts within the mainLayout.
    PositionLayouts();

    // Activate the main layout.
    mainLayout->activate();
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
    //int index = srcLayout->GetItemIndex(item);

    // Remove the item from the source and add it to the destination.
    //srcLayout->removeAt(index);
    //destLayout->AddItem(item);
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

        case PLAYERTRICK:
            chosenLayout = playerTrickLayout;
            break;

        case CPUTRICK:
            chosenLayout = cpuTrickLayout;
            break;

        default:
            chosenLayout = 0;
            break;
    }

    return chosenLayout;
}


//------------------------------------------------------------------------------
// PositionLayouts - Set the positions of the layouts contained by mainLayout.
//------------------------------------------------------------------------------
void LayoutManager::PositionLayouts(void)
{
    // Add the layouts within mainLayout.
    mainLayout->addItem(playingField,           1, 1, 3, 7);
    mainLayout->addItem(playerCardsLayout,      4, 2, 1, 5);
    mainLayout->addItem(cpuCardsLayout,         0, 2, 1, 5);
    mainLayout->addItem(talonLayout,            2, 0, 1, 1);
    mainLayout->addItem(scoreLayout,            2, 0, 3, 1);
    mainLayout->addItem(dialogLayout,           2, 0, 1, 1);

    // Add the layouts within playingField.
    playingField->addItem(deckLayout,           1, 3, 1, 1);
    playingField->addItem(playerTrickLayout,    2, 3, 1, 1);
    playingField->addItem(cpuTrickLayout,       0, 3, 1, 1);
    playingField->addItem(previousTricksLayout, 1, 0, 1, 3);
    playingField->addItem(playerDiscardLayout,  2, 6, 1, 1);
    playingField->addItem(cpuDiscardLayout,     0, 6, 1, 1);
}
