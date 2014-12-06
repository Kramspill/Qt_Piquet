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
                                           int numberOfCards);
    void                     TransferSelectedCards(CardArray* source,
                                                   CardArray* destination);
    void                     TransferCard(CardArray* source,
                                          CardArray* destination,
                                          Card* card);

    CardArray*               GetDesiredCardArray(
                                        CardArray::CardArrayType cardArrayType);

    ScoreManager::PhaseScore GetSelectionScore(CardArray::SelectionType phase);

private:
    void                     ConnectSignals(void);
    void                     InitializeCards(void);
    void                     AddCardsToScene(Scene* scene);
    void                     ShuffleDeck(void);

public slots:
    void                     SetCardsMoveable(bool setMoveable,
                                              CardArray::CardArrayType
                                         cardArrayType = CardArray::PLAYERHAND);
    void                     SetCardsSelectable(bool setSelectable, int limit,
                                                CardArray::CardArrayType
                                         cardArrayType = CardArray::PLAYERHAND);
    void                     CardSelectionsChanged(Card* card,
                                                   CardArray::CardArrayType
                                         cardArrayType = CardArray::PLAYERHAND);
    bool                     CheckSelection(CardArray::SelectionType phase,
                                            CardArray::CardArrayType
                                         cardArrayType = CardArray::PLAYERHAND);
    void                     CheckTrick(int player);

private slots:
    void                     SignalTransferComplete(void);

signals:
    void                     TransferComplete(int);
    void                     InformCardsMoveable(bool);
    void                     TrickResult(int);

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
