//------------------------------------------------------------------------------
// Filename: LayoutManager.h
// Description: Header file for LayoutManager.
//------------------------------------------------------------------------------

#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsGridLayout>


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
        PLAYERTRICK,
        CPUTRICK
    };

public:
    LayoutManager(void);
    LayoutManager(LayoutManager&);
    ~LayoutManager(void);

    void                 Initialize(void);

    void                 Transfer(QGraphicsLayoutItem* item,
                                  Location src, Location dest);
    CardLayout*          GetLayout(Location layout);
    QGraphicsGridLayout* GetMainLayout(void) { return mainLayout; }

private:
    void                 PositionLayouts(void);

private:
    QGraphicsGridLayout* mainLayout;
    QGraphicsGridLayout* playingField;
    QGraphicsGridLayout* scoreLayout;
    QGraphicsGridLayout* dialogLayout;
    CardLayout*          deckLayout;
    CardLayout*          playerCardsLayout;
    CardLayout*          cpuCardsLayout;
    CardLayout*          talonLayout;
    CardLayout*          playerDiscardLayout;
    CardLayout*          cpuDiscardLayout;
    CardLayout*          previousTricksLayout;
    CardLayout*          playerTrickLayout;
    CardLayout*          cpuTrickLayout;
};

#endif // LAYOUTMANAGER_H
