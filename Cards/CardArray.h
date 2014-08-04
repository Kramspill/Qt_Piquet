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

    void  AddCard(Card* newCard);
    void RemoveCard(int index);
    Card* GetCard(int index);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType);

    int  GetSize(void);

private:
    Card* cards[32];
    int   size;
};

#endif // CARDARRAY_H
