//------------------------------------------------------------------------------
// Filename: CardArray.h
// Description: Header file for CardArray.
//------------------------------------------------------------------------------

#ifndef CARDARRAY_H
#define CARDARRAY_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QPointF>


//------------------------------------------------------------------------------
// System Header Files
//------------------------------------------------------------------------------
#include <ctime>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Card.h"


//------------------------------------------------------------------------------
// Class: CardArray
//------------------------------------------------------------------------------
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
        NOSTAGGER,
        DECKSTAGGER,
        HAND,
        PREVTRICKS
    };

public:
    CardArray(void);
    CardArray(CardArrayType arrayType);
    CardArray(CardArray&);
    ~CardArray(void);

    void               AddCard(Card* newCard, bool initialCardCreation = false);
    Card*              RemoveCard(int index);
    Card*              GetCard(int index);
    void               UpdateNextPosition(int x = -1, int y = -1);

    void               Shuffle(void);
    void               Sort(void);
    void               Stagger(StaggerType staggerType);

    int                GetSize(void);
    CardArrayType      GetCardArrayType(void);
    void               SetZPosOnly(bool zPosOnly);

private:
    void               UpdateCardProperties(Card* card, bool noAnimation);
    void               EmitCardMovedSignal(Card* card, bool noAnimation);
    void               UpdateCardPositions(void);

private:
    std::vector<Card*> cards;
    CardArrayType      cardArrayType;
    QPointF            nextCardPosition;
    bool               zPositionOnly;
};

#endif // CARDARRAY_H
