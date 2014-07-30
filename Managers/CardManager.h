#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QPixmap>

#include "Cards/CardArray.h"
#include "Cards/Card.h"

class CardManager
{
public:
    CardManager(void);
    CardManager(CardManager&);
    ~CardManager(void);

    void Initialize(void);

    CardArray* GetDeck(void);
    CardArray* GetTalon(void);
    CardArray* GetPlayerHand(void);
    CardArray* GetCPUHand(void);
    CardArray* GetPlayerDiscards(void);
    CardArray* GetCPUDiscards(void);
    CardArray* GetPreviousTricks(void);
    Card       GetCurrentTrick(void);

private:
    void InitializeAllCards(void);
    void AddAllCards(CardArray& cardArray);

private:
    CardArray* allCards;
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
