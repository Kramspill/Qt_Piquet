#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Card : public QGraphicsPixmapItem
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
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    };

public:
    Card(const QPixmap& pixmap, Suit theSuit, Value theValue);
    Card(Card&);
    ~Card(void);

    Suit  GetSuit(void);
    Value GetValue(void);

private:
    Suit    suit;
    Value   value;
    QPixmap cardImage;
    QPixmap backImage;
};

#endif // CARD_H
