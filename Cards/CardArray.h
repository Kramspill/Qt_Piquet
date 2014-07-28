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

    unsigned int GetSize(void);

    void Shuffle(void);
    void Sort(void);
    void Stagger(StaggerType staggerType);

private:
    Card* cards;
    unsigned int size;
};

#endif // CARDARRAY_H
