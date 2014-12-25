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
#include <QEventLoop>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"
#include "Scene/Scene.h"
#include "ScoreManager.h"
#include "Cards/CardArray.h"
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

    void                     TransferCards(CardArray* source,
                                           CardArray* destination,
                                           int        numberOfCards);
    void                     DealOutCards(CardArray* source,
                                          CardArray* destination,
                                          int        numberOfCards);
    void                     TransferSelectedCards(CardArray* source,
                                                   CardArray* destination);
    void                     TransferCard(CardArray* source,
                                          CardArray* destination,
                                          Card*      card);

    CardArray*               GetCardArray(CardArray::Type Type);
    std::vector<Card*>       GetSelection(PlayerNum player);

private:
    void                     ConnectSignals(void);
    void                     InitializeCards(void);
    void                     AddCardsToScene(Scene* scene);
    void                     ShuffleDeck(void);

public slots:
    void                     SetCardsMoveable(bool setMoveable);
    void                     SetCardsSelectable(bool setSelectable,
                                                PlayerNum player);
    void                     PrepUserForTrick(void);
    void                     CardSelectionsChanged(Card* card,
                                                   CardArray::Type
                                         Type = CardArray::PLAYERHAND);
    bool                     CheckSelection(CardArray::SelectionType phase,
                                            CardArray::Type
                                         Type = CardArray::PLAYERHAND);
    void                     CheckTrick(int player);
    void                     ValidateSelection(void);
    void                     DeselectUserCards(void);

private slots:
    void                     SignalTransferComplete(void);

signals:
    void                     TransferComplete(void);
    void                     InformCardsMoveable(bool);
    void                     TrickResult(int);
    void                     ValidSelection(bool);

private:
    CardArray*               deck;
    CardArray*               talon;
    CardArray*               playerHand;
    CardArray*               cpuHand;
    CardArray*               playerDiscards;
    CardArray*               cpuDiscards;
    CardArray*               previousTricks;
    CardArray*               playerTrick;
    CardArray*               cpuTrick;
    QTimer*                  transitionTimer;
    int                      numOfCardsTransferred;
};

#endif // CARDMANAGER_H
