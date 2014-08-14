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
        NOSUIT,
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES
    };

    enum Value
    {
        NOVALUE,
        SEVEN   = 7,
        EIGHT   = 8,
        NINE    = 9,
        TEN     = 10,
        JACK    = 10,
        QUEEN   = 10,
        KING    = 10,
        ACE     = 11
    };

public:
    Card(void);
    Card(const QString& svgFileName, Suit theSuit, Value theValue);
    Card(Card&);
    ~Card(void);

    void                Initialize(void);

    QGraphicsSvgItem*   GetBackImage(void);
    Suit                GetSuit(void);
    Value               GetValue(void);

    void                SetPosition(QPointF newPosition);

private slots:
    void                UpdatePosition(bool noAnimation);

signals:
    void                CardMoved(bool noAnimation);
    void                InPlayerHand(void);
    void                InCpuHand(void);
    void                InTalon(void);

private:
    QGraphicsSvgItem*   backImage;
    Suit                suit;
    Value               value;
    QPointF             position;
    QStateMachine*      stateMachine;
    QPropertyAnimation* transitionAnimation;
    /* Transformation for flipping the card */
};

#endif // CARD_H
