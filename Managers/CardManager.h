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

    void       Initialize(Scene* scene);

    void       TransferCards(CardArray* source, CardArray* destination,
                             int numberOfCards);
    void       TransferSelectedCards(CardArray* source,
                                     CardArray* destination);

    CardArray* GetDeck(void);
    CardArray* GetTalon(void);
    CardArray* GetPlayerHand(void);
    CardArray* GetCpuHand(void);
    CardArray* GetPlayerDiscards(void);
    CardArray* GetCpuDiscards(void);
    CardArray* GetPreviousTricks(void);
    Card       GetCurrentTrick(void);

    CardArray* GetDesiredCardArray(CardArray::CardArrayType cardArrayType);

private:
    void       ConnectSignals(void);
    void       InitializeCards(void);
    void       AddCardsToScene(Scene* scene);
    void       ShuffleDeck(void);

public slots:
    void       CallTransferSelectedCards(CardArray::CardArrayType src,
                                         CardArray::CardArrayType dest);
    void       CallCheckSelection(CardArray::SelectionType phase,
                                  CardArray::CardArrayType
                                  cardArrayType = CardArray::PLAYERHAND);
    void       SetCardsSelectable(bool setSelectable, int limit,
                                  CardArray::CardArrayType
                                  cardArrayType = CardArray::PLAYERHAND);
    void       CardSelectionsChanged(Card* card, CardArray::CardArrayType
                                     cardArrayType = CardArray::PLAYERHAND);

signals:
    void       TransferComplete(void);
    void       SignalNumOfCardsTransferred(int);
    void       SignalValidSelection(void);

private:
    CardArray* deck;
    CardArray* talon;
    CardArray* playerHand;
    CardArray* cpuHand;
    CardArray* playerDiscards;
    CardArray* cpuDiscards;
    CardArray* previousTricks;
    Card       currentTrick;
    QTimer*    transitionTimer;
};

#endif // CARDMANAGER_H
