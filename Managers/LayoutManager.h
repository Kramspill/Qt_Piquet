//------------------------------------------------------------------------------
// Filename: LayoutManager.h
// Description: Header file for LayoutManager.
//------------------------------------------------------------------------------

#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsAnchorLayout>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Layout/CardLayout.h"


//------------------------------------------------------------------------------
// Class: LayoutManager
//------------------------------------------------------------------------------
class LayoutManager
{
public:
    LayoutManager(void);
    LayoutManager(LayoutManager&);
    ~LayoutManager(void);

private:
    QGraphicsAnchorLayout* mainLayout;
    CardLayout*            deckCards;
    CardLayout*            playerCards;
    CardLayout*            cpuCards;
    CardLayout*            talonCards;
    CardLayout*            playerDiscardCards;
    CardLayout*            cpuDiscardCards;
    CardLayout*            previousTricksCards;
    CardLayout*            currentTrickCard;
};

#endif // LAYOUTMANAGER_H
