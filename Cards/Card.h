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
#include <QPointF>


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

    enum Value
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
    Card(const QString& svgFileName, Suit theSuit, Value theValue);
    Card(Card&);
    ~Card(void);

    void                Initialize(void);

    Suit                GetSuit(void);
    Value               GetValue(void);
    QPointF             GetPosition(void);

    void                UpdateSelection(void);
    void                SetPosition(QPointF newPosition, int zPosition = -1);

private slots:
    void                UpdatePosition(bool noAnimation);
    void                FlipCard(void);

signals:
    void                CardMoved(bool noAnimation);
    void                InTalon(void);
    void                InPlayerHand(void);
    void                InCpuHand(void);
    void                InPlayerDiscards(void);
    void                InCpuDiscards(void);

private:
    QSvgRenderer*       renderer;
    QString             frontImage;
    QString             backImage;
    bool                facedown;
    Suit                suit;
    Value               value;
    QPointF             position;
    QStateMachine*      stateMachine;
    QPropertyAnimation* transitionAnimation;
    /* Transformation for flipping the card */
};

#endif // CARD_H
