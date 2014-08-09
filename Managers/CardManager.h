#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "Scene/Scene.h"
#include "Cards/CardArray.h"
#include "Cards/Card.h"

class CardManager
{
public:
    ~CardManager(void);

    static CardManager& GetSingleton(void);

    void Initialize(Scene* scene);

    void TransferCards(CardArray* source, CardArray* destination, int numberOfCards);

    CardArray* GetDeck(void);
    CardArray* GetTalon(void);
    CardArray* GetPlayerHand(void);
    CardArray* GetCpuHand(void);
    CardArray* GetPlayerDiscards(void);
    CardArray* GetCpuDiscards(void);
    CardArray* GetPreviousTricks(void);
    Card       GetCurrentTrick(void);

private:
    CardManager(void) {}
    CardManager(CardManager&);
    void operator=(CardManager&);

    void InitializeDeck(void);
    void AddCardsToScene(Scene* scene);
    void ResetDeck(void);

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
