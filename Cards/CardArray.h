#ifndef CARDARRAY_H
#define CARDARRAY_H

#include <QPointF>

#include "Card.h"

class CardArray
{
public:
    enum CardArrayType
    {
        DECK,
        PLAYERHAND,
        CPUHAND,
        TALON,
        PLAYERDISCARDS,
        CPUDISCARDS,
        PREVIOUSTRICKS
    };

    enum StaggerType
    {
        HAND,
        PREVTRICKS
    };

public:
    CardArray(void);
    CardArray(CardArrayType arrayType);
    CardArray(int newSize);
    CardArray(CardArray&);
    ~CardArray(void);

    void  AddCard(Card* newCard);
    Card* RemoveCard(int index);
    Card* GetCard(int index);
    void  UpdateNextPosition(int x = -1, int y = -1);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType);

    int           GetSize(void);
    CardArrayType GetCardArrayType(void);
    void          SetZPosOnly(bool zPosOnly);

private:
    std::vector<Card*> cards;
    CardArrayType      cardArrayType;
    QPointF            nextCardPosition;
    bool               zPositionOnly;
};

#endif // CARDARRAY_H
