//------------------------------------------------------------------------------
// Filename: Card.h
// Description: Header file for Card.
//------------------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QStateMachine>
#include <QPropertyAnimation>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/CardStates.h"


//------------------------------------------------------------------------------
// Class: Card
//------------------------------------------------------------------------------
class Card : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    enum Suit
    {
        CLUBS    = 0,
        DIAMONDS = 1,
        HEARTS   = 2,
        SPADES   = 3
    };

    enum Rank
    {
        SEVEN   = 7,
        EIGHT   = 8,
        NINE    = 9,
        TEN     = 10,
        JACK    = 11,
        QUEEN   = 12,
        KING    = 13,
        ACE     = 14
    };

    enum { Type = UserType + 1 };
    int type(void) const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

public:
    Card(void);
    Card(const QString& svgFileName, Suit theSuit, Rank theRank);
    Card(Card&);
    ~Card(void);

    void                   Destroy(void);

    Suit                   GetSuit(void);
    Rank                   GetRank(void);
    int                    GetValue(void);
    QPointF                GetPosition(void);

    void                   SetSuit(Suit newSuit);
    void                   SetRank(Rank newRank);

    void                   UpdateSelection(void);
    void                   SetPosition(QPointF newPosition, int zPosition = -1);
    void                   UpdateAnimation(bool noAnimation);

protected:
    void                   mousePressEvent(QGraphicsSceneMouseEvent*);
    void                   mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    void                   Initialize(void);
    void                   SetValue(void);

private slots:
    void                   FlipCard(void);
    void                   Display(void);

signals:
    void                   InDeck(void);
    void                   InTalon(void);
    void                   InPlayerHand(void);
    void                   InCpuHand(void);
    void                   InPlayerDiscards(void);
    void                   InCpuDiscards(void);
    void                   InPlayerTrick(void);
    void                   InCpuTrick(void);
    void                   InPreviousTricks(void);

private:
    QSvgRenderer*          renderer;
    QString                frontImage;
    QString                backImage;
    bool                   facedown;
    Suit                   suit;
    Rank                   rank;
    int                    value;
    QPointF                position;
    QPointF                origPosition;
    QStateMachine*         stateMachine;
    InDeckState*           inDeckState;
    InTalonState*          inTalonState;
    InPlayerHandState*     inPlayerHandState;
    InCpuHandState*        inCpuHandState;
    InPlayerDiscardsState* inPlayerDiscardsState;
    InCpuDiscardsState*    inCpuDiscardsState;
    InPlayerTrickState*    inPlayerTrickState;
    InCpuTrickState*       inCpuTrickState;
    InPreviousTricksState* inPreviousTricksState;
    QPropertyAnimation*    transitionAnimation;
};

#endif // CARD_H
