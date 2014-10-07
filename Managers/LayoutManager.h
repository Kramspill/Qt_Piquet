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
#include "Layouts/CardLayout.h"


//------------------------------------------------------------------------------
// Class: LayoutManager
//------------------------------------------------------------------------------
class LayoutManager
{
public:
    enum Location
    {
        DECK,
        PLAYERHAND,
        CPUHAND,
        TALON,
        PLAYERDISCARDS,
        CPUDISCARDS,
        PREVTRICKS,
        CURRENTTRICK
    };

public:
    LayoutManager(void);
    LayoutManager(LayoutManager&);
    ~LayoutManager(void);

    void                   Initialize(void);

    void                   Transfer(QGraphicsLayoutItem* item,
                                    Location src, Location dest);
    CardLayout*            GetLayout(Location layout);

private:
    void                   PositionLayouts(void);

private:
    QGraphicsAnchorLayout* mainLayout;
    QGraphicsAnchorLayout* playingField;
    QGraphicsAnchorLayout* scoreLayout;
    QGraphicsAnchorLayout* dialogLayout;
    CardLayout*            deckLayout;
    CardLayout*            playerCardsLayout;
    CardLayout*            cpuCardsLayout;
    CardLayout*            talonLayout;
    CardLayout*            playerDiscardLayout;
    CardLayout*            cpuDiscardLayout;
    CardLayout*            previousTricksLayout;
    CardLayout*            currentTrickLayout;
};

#endif // LAYOUTMANAGER_H
