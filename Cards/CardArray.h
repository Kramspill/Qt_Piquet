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
    CardArray(CardArrayType arrayType, int x, int y);
    CardArray(CardArray&);
    ~CardArray(void);

    void               AddCard(Card* newCard, bool initialCardCreation = false);
    void               RemoveCard(Card* aCard);
    Card*              RemoveTopCard(void);
    Card*              GetCard(int index);

    void               Shuffle(void);
    void               Sort(void);
    void               Stagger(StaggerType staggerType);

    bool               UpdateCardSelections(Card* card);
    Card*              RemoveSelectedCard(void);

    int                GetSize(void);
    int                GetSelectedCardsSize(void);
    CardArrayType      GetCardArrayType(void);
    void               SetSelectionLimit(int newLimit);

private:
    void               UpdateCardPositions(Card* addedCard = 0,
                                           bool noAnimation = false);
    void               CleanUpCardPositions(bool newCardAdded);
    void               EmitCardMovedSignal(Card* card, bool noAnimation);
    void               ResetZPositions(void);

private:
    std::vector<Card*> cards;
    std::vector<Card*> selectedCards;
    int                selectionLimit;
    CardArrayType      cardArrayType;
    QPointF            initialCardPosition;
    QPointF            nextCardPosition;
};

#endif // CARDARRAY_H
