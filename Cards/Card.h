#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Card : public QObject, public QGraphicsPixmapItem
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
    Card(const QPixmap& pixmap, Suit theSuit, Value theValue);
    Card(Card aCard);
    Card(Card&);
    ~Card(void);

    Suit    GetSuit(void);
    Value   GetValue(void);
    QPixmap GetCardImage(void);
    QPixmap GetBackImage(void);

private:
    Suit    suit;
    Value   value;
    QPixmap cardImage;
    QPixmap backImage;
};

#endif // CARD_H
