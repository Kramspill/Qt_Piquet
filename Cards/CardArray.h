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
    CardArray(int newSize);
    CardArray(CardArray&);
    ~CardArray(void);

    void  AddCard(Card* newCard);
    Card* RemoveCard(int index);
    Card* GetCard(int index);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType);

    int  GetSize(void);

private:
    std::vector<Card*> cards;
};

#endif // CARDARRAY_H
