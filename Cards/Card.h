#ifndef CARD_H
#define CARD_H

#include <QGraphicsSvgItem>

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
    Card(QGraphicsSvgItem* svgItem, Suit theSuit, Value theValue);
    Card(Card&);
    ~Card(void);

    QGraphicsSvgItem* GetCardImage(void);
    QGraphicsSvgItem* GetBackImage(void);
    Suit              GetSuit(void);
    Value             GetValue(void);

private:
    QGraphicsSvgItem* cardImage;
    QGraphicsSvgItem* backImage;
    Suit              suit;
    Value             value;
};

#endif // CARD_H
