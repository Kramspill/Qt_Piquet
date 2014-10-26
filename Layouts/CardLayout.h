//------------------------------------------------------------------------------
// Filename: CardLayout.h
// Description: Header file for CardLayout.
//------------------------------------------------------------------------------

#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsLayout>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: CardLayout
//------------------------------------------------------------------------------
class CardLayout : public QGraphicsLayout
{
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
        PREVIOUSTRICKS,
        PLAYERTRICK,
        CPUTRICK
    };

    enum StaggerType
    {
        NOSTAGGER,
        DECKSTAGGER,
        HAND,
        PREVTRICKS
    };

    enum SelectionType
    {
        POINT,
        SEQUENCE,
        SET
    };

public:
    CardLayout(Type aType, QGraphicsLayoutItem* parent = 0);
    CardLayout(CardLayout&);
    ~CardLayout(void);

    void         AddCard(Card* card, bool temp = false);
    Card*        RemoveCard(Card* card = 0);
    int          GetCardIndex(Card* card);

    void         setGeometry(const QRectF& rect);
    QSizeF       sizeHint(Qt::SizeHint which,
                          const QSizeF& constraint = QSizeF()) const;
    int          count(void) const;
    Card*        itemAt(int index) const;
    void         removeAt(int index);

    void         Shuffle(void);
    void         Sort(void);

private:
    void         ResetZPositions(void);

private:
    QList<Card*> cards;
    Type         type;
};

#endif // CARDLAYOUT_H
