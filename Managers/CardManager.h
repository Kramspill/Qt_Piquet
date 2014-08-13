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

    CardArray* GetDeck(void);
    CardArray* GetTalon(void);
    CardArray* GetPlayerHand(void);
    CardArray* GetCpuHand(void);
    CardArray* GetPlayerDiscards(void);
    CardArray* GetCpuDiscards(void);
    CardArray* GetPreviousTricks(void);
    Card       GetCurrentTrick(void);

private:
    void       InitializeCards(void);
    void       SetInitialCardPositions(void);
    void       AddCardsToScene(Scene* scene);
    void       ShuffleDeck(void);
    void       EmitCardMovedSignal(Card* card,
                                   CardArray::CardArrayType cardArrayType);
    CardArray* GetDesiredCardArray(CardArray::CardArrayType cardArrayType);

public slots:
    void       CallTransferCards(CardArray::CardArrayType src,
                                 CardArray::CardArrayType dest,
                                 int numOfCards);

private:
    CardArray* deck;
    CardArray* talon;
    CardArray* playerHand;
    CardArray* cpuHand;
    CardArray* playerDiscards;
    CardArray* cpuDiscards;
    CardArray* previousTricks;
    Card       currentTrick;
};

#endif // CARDMANAGER_H
