//------------------------------------------------------------------------------
// Filename: CardArray.h
// Description: Header file for CardArray.
//------------------------------------------------------------------------------

#ifndef CARDARRAY_H
#define CARDARRAY_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>


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
class CardArray : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        UNKNOWN,
        DECK,
        PLAYERHAND,
        CPUHAND,
        TALON,
        PLAYERDISCARDS,
        CPUDISCARDS,
        PLAYERTRICK,
        CPUTRICK,
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
    CardArray(Type arrayType, int x, int y);
    CardArray(CardArray&);
    ~CardArray(void);

    void               Destroy(void);

    void               AddCard(Card* newCard,
                               bool initialCardCreation = false,
                               bool doNothing = false);
    void               RemoveCard(Card* aCard, bool doNothing = false);
    Card*              RemoveTopCard(void);
    Card*              GetCard(int index);

    void               Shuffle(void);
    void               Sort(void);
    void               Stagger(StaggerType staggerType);

    int                GetSize(void);
    Type               GetType(void);

private:
    void               UpdateCardPositions(Card* addedCard  = 0,
                                           bool noAnimation = false);
    void               CleanUpCardPositions(bool newCardAdded);
    void               UpdateCardState(Card* card, bool noAnimation);
    void               ResetZPositions(void);

private:
    std::vector<Card*> cards;
    Type               type;
    QPointF            initialCardPosition;
    QPointF            nextCardPosition;
};

#endif // CARDARRAY_H
