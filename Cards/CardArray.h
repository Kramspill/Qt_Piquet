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

    void AddCard(Card newCard);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType staggerType);

    unsigned int GetSize(void);

private:
    Card* cards;
    unsigned int size;
};

#endif // CARDARRAY_H
