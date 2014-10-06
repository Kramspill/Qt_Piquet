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
    LayoutManager(void);
    LayoutManager(LayoutManager&);
    ~LayoutManager(void);

    void                   Initialize(void);

private:
    void                   PositionLayouts(void);

private:
    QGraphicsAnchorLayout* mainLayout;
    QGraphicsAnchorLayout* playingField;
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
