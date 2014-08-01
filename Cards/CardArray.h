#ifndef CARDARRAY_H
#define CARDARRAY_H

#include "Card.h"

class CardArray
{
public:
    enum StaggerType
    {
        HAND,
        PREVIOUSTRICKS
    };

public:
    CardArray(void);
    CardArray(CardArray&);
    ~CardArray(void);

    void AddCard(Card* newCard);
    bool RemoveTopCard(void);
    Card* GetCard(int);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType);

    int GetSize(void);

private:
    Card* topCard;
    Card* cards;
    int size;
};

#endif // CARDARRAY_H
