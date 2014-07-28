#ifndef CARD_H
#define CARD_H

class Card
{
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
    Card(void);
    Card(Card&);
    ~Card(void);

    Suit  GetSuit(void);
    Value GetValue(void);

private:
    Suit  suit;
    Value value;
};

#endif // CARD_H
