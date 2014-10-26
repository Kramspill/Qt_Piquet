//------------------------------------------------------------------------------
// Filename: CardManager.h
// Description: Header file for CardManager.
//------------------------------------------------------------------------------

#ifndef CARDMANAGER_H
#define CARDMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>
#include <QTimer>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Scene/Scene.h"
#include "ScoreManager.h"
#include "Layouts/CardLayout.h"
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: CardManager
//------------------------------------------------------------------------------
class CardManager : public QObject
{
    Q_OBJECT
public:
    CardManager(void);
    CardManager(CardManager&);
    ~CardManager(void);

    void                     Initialize(Scene* scene);

    void                     TransferCards(CardLayout* source,
                                           CardLayout* destination,
                                           int numberOfCards);
    void                     TransferSelectedCards(CardLayout* source,
                                                   CardLayout* destination);

    CardLayout*              GetDesiredCardLayout(CardLayout::Type type);
    Card                     GetCurrentTrick(void);

    ScoreManager::PhaseScore GetSelectionScore(CardLayout::SelectionType phase);

private:
    void                     AddLayoutsToScene(Scene* scene);
    void                     ConnectSignals(void);
    void                     InitializeCards(void);
    void                     ShuffleDeck(void);

public slots:
    void                     SetCardsSelectable(bool setSelectable, int limit,
                                                CardLayout::Type type = CardLayout::PLAYERHAND);
    void                     CardSelectionsChanged(Card* card,
                                                   CardLayout::Type type = CardLayout::PLAYERHAND);
    /*bool                     CheckSelection(CardLayout::SelectionType phase,
                                            CardLayout::Type type = CardLayout::PLAYERHAND);
*/
private slots:
    void                     SignalTransferComplete(void);

signals:
    void                     TransferComplete(int);
    //void       SignalValidSelection(void);

private:
    CardLayout*              deck;
    CardLayout*              talon;
    CardLayout*              playerHand;
    CardLayout*              cpuHand;
    CardLayout*              playerDiscards;
    CardLayout*              cpuDiscards;
    CardLayout*              previousTricks;
    CardLayout*              playerTrick;
    CardLayout*              cpuTrick;
    QTimer*                  transitionTimer;
    int                      numOfCardsTransferred;
};

#endif // CARDMANAGER_H
