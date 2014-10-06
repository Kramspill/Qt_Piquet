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
// PositionLayouts - Set the positions of the layouts contained by mainLayout.
//------------------------------------------------------------------------------
void LayoutManager::PositionLayouts(void)
{
    mainLayout->addAnchor(playerCardsLayout, Qt::AnchorTop,
                          mainLayout,        Qt::AnchorTop);
}
