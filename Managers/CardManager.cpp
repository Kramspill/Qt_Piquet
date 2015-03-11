//------------------------------------------------------------------------------
// Filename: CardManager.cpp
// Description: Manager for the cards used in this game.
//
// Vectorized Playing Cards 1.3- http://code.google.com/p/vectorized-playing-cards/
// Copyright 2011 - Chris Aguilar
// Licensed under LGPL 3 - www.gnu.org/copyleft/lesser.html
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "CardManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CardManager::CardManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardManager::CardManager(CardManager&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardManager::~CardManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the Cards and CardArrays held by this manager.
//------------------------------------------------------------------------------
void CardManager::Initialize(Scene* scene)
{
    // Get Rects for card array placement.
    QRectF* rect   = scene->GetTrickArea();

    // Initialize the CardArray member variables.
    deck           = new CardArray(CardArray::DECK,
                                   rect->x()+rect->width()/2,
                                   rect->y()+rect->height()/2);
    talon          = new CardArray(CardArray::TALON,
                                   0,
                                   rect->y()+rect->height()*0.25);
    playerHand     = new CardArray(CardArray::PLAYERHAND,
                                   (rect->x()+rect->width())*0.57,
                                   scene->GetHeight()-170);
    cpuHand        = new CardArray(CardArray::CPUHAND,
                                   (rect->x()+rect->width())*0.57,
                                   10);
    playerDiscards = new CardArray(CardArray::PLAYERDISCARDS,
                                   rect->x()+rect->width()+30,
                                   rect->y()+rect->height()*0.65);
    cpuDiscards    = new CardArray(CardArray::CPUDISCARDS,
                                   rect->x()+rect->width()+30,
                                   rect->y()*0.4);
    playerTrick    = new CardArray(CardArray::PLAYERTRICK,
                                   (rect->x()+rect->width())*0.6,
                                   (rect->y()+rect->height())*0.7);
    cpuTrick       = new CardArray(CardArray::CPUTRICK,
                                   (rect->x()+rect->width())*0.6,
                                   (rect->y()+rect->height())*0.4);
    previousTricks = new CardArray(CardArray::PREVIOUSTRICKS,
                                   rect->x()*0.45,
                                   10);

    // Initialize the timer to allow animation to finish before informing of
    // state changes.
    transitionTimer = new QTimer();
    transitionTimer->setSingleShot(true);

    // Initialize all the cards used in the game and add them to the deck.
    InitializeCards();

    // Shuffle the deck.
    ShuffleDeck();

    // Add the cards (initially in the deck) to the scene.
    AddCardsToScene(scene);
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void CardManager::Destroy(void)
{
    // First remove any cards in the arrays.
    deck->Destroy();
    talon->Destroy();
    playerHand->Destroy();
    cpuHand->Destroy();
    playerDiscards->Destroy();
    cpuDiscards->Destroy();
    playerTrick->Destroy();
    cpuTrick->Destroy();
    previousTricks->Destroy();

    delete deck;                deck            = 0;
    delete talon;               talon           = 0;
    delete playerHand;          playerHand      = 0;
    delete cpuHand;             cpuHand         = 0;
    delete playerDiscards;      playerDiscards  = 0;
    delete cpuDiscards;         cpuDiscards     = 0;
    delete playerTrick;         playerTrick     = 0;
    delete cpuTrick;            cpuTrick        = 0;
    delete previousTricks;      previousTricks  = 0;
    delete transitionTimer;     transitionTimer = 0;
}


//------------------------------------------------------------------------------
// Reset - Return all cards to the deck.
//------------------------------------------------------------------------------
void CardManager::Reset(void)
{
    int size;

    if ( talon->GetSize() > 0 )
        TransferCards(talon, deck, talon->GetSize());

    TransferCards(cpuDiscards,    deck, cpuDiscards->GetSize());
    TransferCards(playerDiscards, deck, playerDiscards->GetSize());

    if ( cpuTrick->GetSize() > 0 )
        TransferCards(cpuTrick, deck, cpuTrick->GetSize());

    if ( playerTrick->GetSize() > 0 )
        TransferCards(playerTrick, deck, playerTrick->GetSize());

    size = playerHand->GetSize();

    // Remove cards from the player hand.
    for ( int i = 0; i < size/3; i++ )
    {
        TransferCards(playerHand, deck, 3);
    }

    if ( playerHand->GetSize() > 0 )
        TransferCards(playerHand, deck, playerHand->GetSize());

    size = cpuHand->GetSize();

    // Remove cards from the cpu hand.
    for ( int i = 0; i < size/3; i++ )
    {
        TransferCards(cpuHand, deck, 3);
    }

    if ( cpuHand->GetSize() > 0 )
        TransferCards(cpuHand, deck, cpuHand->GetSize());

    size = previousTricks->GetSize();

    // Remove cards from the previous tricks.
    for ( int i = 0; i < size/3; i++ )
    {
        TransferCards(previousTricks, deck, 3);
    }

    if ( previousTricks->GetSize() > 0 )
        TransferCards(previousTricks, deck, previousTricks->GetSize());

    ShuffleDeck();
}


//------------------------------------------------------------------------------
// TransferCards - Transfer cards between one CardArray and another.
//------------------------------------------------------------------------------
void CardManager::TransferCards(CardArray* src, CardArray* dest,
                                int numCards)
{
    // Determine if we are transfering specific cards or not.
    if ( numCards == 0 )
    {
        // If our destination is a player's hand and perform a deal.
        if ( dest->GetType() == CardArray::PLAYERHAND ||
             dest->GetType() == CardArray::CPUHAND )
        {
            numCards = 12 - dest->GetSize();
            DealOutCards(src, dest, numCards);
        }
        else
        {
            // Here, we are transferring cards that have been selected.
            TransferSelectedCards(src, dest);
        }
    }
    else
    {
        DealOutCards(src, dest, numCards);
    }
}


//------------------------------------------------------------------------------
// GetCardArray - Return the CardArray associated with a given type.
//------------------------------------------------------------------------------
CardArray* CardManager::GetCardArray(CardArray::Type type)
{
    CardArray* returnedArray = 0;

    switch ( type )
    {
        case CardArray::DECK:
            returnedArray = deck;
            break;

        case CardArray::TALON:
            returnedArray = talon;
            break;

        case CardArray::PLAYERHAND:
            returnedArray = playerHand;
            break;

        case CardArray::CPUHAND:
            returnedArray = cpuHand;
            break;

        case CardArray::PLAYERDISCARDS:
            returnedArray = playerDiscards;
            break;

        case CardArray::CPUDISCARDS:
            returnedArray = cpuDiscards;
            break;

        case CardArray::PLAYERTRICK:
            returnedArray = playerTrick;
            break;

        case CardArray::CPUTRICK:
            returnedArray = cpuTrick;
            break;

        case CardArray::PREVIOUSTRICKS:
            returnedArray = previousTricks;
            break;

        default:
            break;
    }

    return returnedArray;
}


//------------------------------------------------------------------------------
// GetSelection - Return the player's selected cards.
//------------------------------------------------------------------------------
std::vector<Card*> CardManager::GetSelection(PlayerNum player)
{
    std::vector<Card*> selectedCards;
    CardArray*         cards;

    // Retrieve the correct CardArray.
    if ( player == PLAYER1 )
        cards = playerHand;
    else
        cards = cpuHand;

    // Locate the selected cards.
    for ( int i = 0; i < cards->GetSize(); i++ )
    {
        Card* card = cards->GetCard(i);

        if ( card->isSelected() )
            selectedCards.push_back(card);
    }

    return selectedCards;
}


//------------------------------------------------------------------------------
// CheckCarteBlanche - Check if either play has a Carte Blanche.
//------------------------------------------------------------------------------
PlayerNum CardManager::CheckCarteBlanche(void)
{
    Card* card;
    bool  carteBlanche = true;
    PlayerNum p = NOPLAYER;

    for ( int i = 0; i < playerHand->GetSize(); i++ )
    {
        card = playerHand->GetCard(i);

        if ( card->GetRank() > 10 && card->GetRank() < 14 )
            carteBlanche = false;
    }

    if ( carteBlanche )
    {
        p = PLAYER1;
    }
    else
    {
        carteBlanche = true;
        for ( int i = 0; i < cpuHand->GetSize(); i++ )
        {
            card = cpuHand->GetCard(i);

            if ( card->GetRank() > 10 && card->GetRank() < 14 )
                carteBlanche = false;
        }

        if ( carteBlanche )
        {
            p = PLAYER2;
        }
    }

    return p;
}


//------------------------------------------------------------------------------
// InitializeCards - Create all the cards and add them to the deck.
//------------------------------------------------------------------------------
void CardManager::InitializeCards(void)
{
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                           Card::CLUBS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/8C.svg",
                           Card::CLUBS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/9C.svg",
                           Card::CLUBS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/10C.svg",
                           Card::CLUBS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/JC.svg",
                           Card::CLUBS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/QC.svg",
                           Card::CLUBS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/KC.svg",
                           Card::CLUBS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/AC.svg",
                           Card::CLUBS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/7D.svg",
                           Card::DIAMONDS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/8D.svg",
                           Card::DIAMONDS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/9D.svg",
                           Card::DIAMONDS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/10D.svg",
                           Card::DIAMONDS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/JD.svg",
                           Card::DIAMONDS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/QD.svg",
                           Card::DIAMONDS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/KD.svg",
                           Card::DIAMONDS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/AD.svg",
                           Card::DIAMONDS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/7H.svg",
                           Card::HEARTS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/8H.svg",
                           Card::HEARTS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/9H.svg",
                           Card::HEARTS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/10H.svg",
                           Card::HEARTS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/JH.svg",
                           Card::HEARTS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/QH.svg",
                           Card::HEARTS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/KH.svg",
                           Card::HEARTS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/AH.svg",
                           Card::HEARTS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/7S.svg",
                           Card::SPADES, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/8S.svg",
                           Card::SPADES, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/9S.svg",
                           Card::SPADES, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/10S.svg",
                           Card::SPADES, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/JS.svg",
                           Card::SPADES, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/QS.svg",
                           Card::SPADES, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/KS.svg",
                           Card::SPADES, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                           Card::SPADES, Card::ACE), true);
}


//------------------------------------------------------------------------------
// AddCardsToScene - Add all the cards to the scene.
//------------------------------------------------------------------------------
void CardManager::AddCardsToScene(Scene* scene)
{
    Card* card;
    for (int index = 0; index < deck->GetSize(); index++)
    {
        card = deck->GetCard(index);

        card->setScale(0.5);
        scene->addItem(card);
    }
}


//------------------------------------------------------------------------------
// ShuffleDeck - Shuffle the deck.
//------------------------------------------------------------------------------
void CardManager::ShuffleDeck(void)
{
    // Line up the cards in the deck before shuffling.
    deck->Stagger(CardArray::NOSTAGGER);
    deck->Shuffle();

    // Re-stagger the deck.
    deck->Stagger(CardArray::DECKSTAGGER);
}


//------------------------------------------------------------------------------
// DealOutCards - Deal out cards from one CardArray to another.
//------------------------------------------------------------------------------
void CardManager::DealOutCards(CardArray* src,
                               CardArray* dest,
                               int        numCards)
{
    for (int index = 0; index < numCards; index++)
    {
        // Remove the card from the source array, and add it to the destination.
        Card* card = src->RemoveTopCard();

        // Fix crash on quit.
        if ( card )
        {
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
            card->setFlag(QGraphicsItem::ItemIsMovable,    false);
            dest->AddCard(card);
        }
    }

    // Delay the signal of transfer completion for animation purposes.
    transitionTimer->start(100);

    // Wait for timer to finish.
    QEventLoop* loop = new QEventLoop();
    connect(transitionTimer, SIGNAL(timeout()), loop, SLOT(quit()));
    loop->exec();
    delete loop;
}


//------------------------------------------------------------------------------
// TransferSelectedCards - Transfer a cardArray's selected cards to another
//                         CardArray.
//------------------------------------------------------------------------------
void CardManager::TransferSelectedCards(CardArray* src,
                                        CardArray* dest)
{
    std::vector<Card*> cards;
    int size = src->GetSize();

    // Locate the selected cards.
    for ( int i = 0; i < size; i++ )
    {
        Card* card = src->GetCard(i);

        if ( card->isSelected() )
        {
            card->setSelected(false);
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
            card->setFlag(QGraphicsItem::ItemIsMovable,    false);
            cards.push_back(card);
        }
        else
        {
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
            card->setFlag(QGraphicsItem::ItemIsMovable,    false);
        }
    }

    // Set the number of cards to be transferred.
    size = cards.size();

    // Transfer the selected cards to the destination CardArray.
    if ( size > 0 )
    {
        for ( int i = 0; i < size; i++ )
        {
            src->RemoveCard(cards.back());
            dest->AddCard(cards.back());

            cards.pop_back();
        }
    }

    // Delay the signal of transfer completion for animation purposes.
    transitionTimer->start(100);

    // Wait for timer to finish.
    QEventLoop* loop = new QEventLoop();
    connect(transitionTimer, SIGNAL(timeout()), loop, SLOT(quit()));
    loop->exec();
    delete loop;
}


//------------------------------------------------------------------------------
// SetCardsMoveable - Enable/Disable a CardArray's cards to be moveable.
//------------------------------------------------------------------------------
void CardManager::SetCardsMoveable(bool setMoveable)
{
    Card* card;

    // Loop through the array setting the ItemIsMovable property.
    for ( int index = 0; index < playerHand->GetSize(); index++ )
    {
        card = playerHand->GetCard(index);

        if ( setMoveable )
        {
            card->setFlag(QGraphicsItem::ItemIsMovable, true);
            emit InformCardsMoveable(true);
        }
        else
        {
            card->setFlag(QGraphicsItem::ItemIsMovable, false);
            emit InformCardsMoveable(false);
        }
    }
}


//------------------------------------------------------------------------------
// SetCardsSelectable - Enable/Disable the user's cards to be selected.
//------------------------------------------------------------------------------
void CardManager::SetCardsSelectable(bool setSelectable, PlayerNum player)
{
    Card* card;
    CardArray* hand = (player == PLAYER1) ? playerHand : cpuHand;

    // Loop through the array setting the ItemIsSelectable property.
    for ( int index = 0; index < hand->GetSize(); index++ )
    {
        card = hand->GetCard(index);

        if ( setSelectable )
        {
            card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
        else
        {
            if ( card->isSelected() )
            {
                card->setFlag(QGraphicsItem::ItemIsSelectable, true);
                card->setSelected(false);
            }

            card->UpdateSelection();
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}


//------------------------------------------------------------------------------
// DeselectCards - Deselect all user cards, called when a skip is requested.
//------------------------------------------------------------------------------
void CardManager::DeselectCards(void)
{
    Card* card;

    for ( int i = 0; i < playerHand->GetSize(); i++ )
    {
        card = playerHand->GetCard(i);

        if ( card->isSelected() )
        {
            card->setSelected(false);
            card->UpdateSelection();
        }
    }
}


//------------------------------------------------------------------------------
// ValidateSelection - Inform the scene to enable/disable buttons based on
//                     whether the user's selection is valid or not.
//------------------------------------------------------------------------------
void CardManager::ValidateSelection(void)
{
    std::vector<Card*> selectedCards = GetSelection(PLAYER1);
    int  i     = 0;
    int  j     = 0;
    bool valid = true;
    Card::Suit suit;
    Card::Rank rank;
    bool  cardBuckets[8] = { false };

    switch ( currentPhase )
    {
        case EXCHANGE:
            if ( selectedCards.size() < 1 ||
                 selectedCards.size() > 5 ||
                 (int)selectedCards.size() > talon->GetSize() )
            {
                valid = false;
            }
            break;

        case POINT:
            if ( selectedCards.size() == 0 )
            {
                valid = false;
            }
            else
            {
                suit = selectedCards[i]->GetSuit();

                // First check it's a valid Point.
                while ( i < (int)selectedCards.size() && valid )
                {
                    if ( selectedCards[i++]->GetSuit() != suit )
                        valid = false;
                }

                if ( younger == PLAYER1 && valid )
                {
                    // Check if we are responding or not as we need to at least
                    // match the opponents point.
                    if ( (int)selectedCards.size() < pointDeclaration->numCards)
                        valid = false;
                }
            }
            break;

        case SEQUENCE:
            if ( selectedCards.size() < 3 )
            {
                valid = false;
            }
            else
            {
                // Perform a bucket sort then check the cards.
                suit = selectedCards[i]->GetSuit();

                // First check the cards are of the same suit.
                while ( i < (int)selectedCards.size() && valid )
                {
                    // Place the card in it's bucket.
                    cardBuckets[selectedCards[i]->GetRank()-7] = true;

                    if ( selectedCards[i++]->GetSuit() != suit )
                        valid = false;
                }

                if ( valid )
                {
                    i = 0;
                    j = 0;

                    // Now check if the cards are in sequence.
                    while ( i < 8 && !cardBuckets[i] ) { i++; }

                    while ( i < 8 && cardBuckets[i] )
                    {
                        i++;
                        j++;
                    }

                    if ( j < (int)selectedCards.size() )
                    {
                        valid = false;
                    }
                    else if ( younger == PLAYER1 )
                    {
                        // Check if we are responding or not as we need to at
                        // least match the opponents Sequence.
                        if ( (int)selectedCards.size() < seqDeclaration->numCards)
                            valid = false;
                    }
                }
            }
            break;

        case SET:
            if ( selectedCards.size() < 3 || selectedCards.size() > 4 )
            {
                valid = false;
            }
            else
            {
                rank = selectedCards[i]->GetRank();

                while ( i < (int)selectedCards.size() && valid )
                {
                    if ( selectedCards[i++]->GetRank() != rank )
                        valid = false;
                }

                if ( younger == PLAYER1 && valid )
                {
                    // Check if we are responding or not as we need to at
                    // least match the opponents Sequence.
                    if ( (int)selectedCards.size() < setDeclaration->numCards)
                        valid = false;
                }
            }
            break;

        default:
            break;
    }

    if ( valid )
        emit ValidSelection(true);
    else
        emit ValidSelection(false);
}


//------------------------------------------------------------------------------
// PrepForTrick - Ensure the user can onbly play valid Tricks.
//------------------------------------------------------------------------------
void CardManager::PrepForTrick(void)
{
    if ( cpuTrick->GetSize() > 0 )
    {
        Card* cpuCard    = cpuTrick->GetCard(0);
        bool  validCards = false;
        int   i          = 0;

        // Loop through the user's hand checking if there is a card
        // that can be played.
        while ( !validCards && i < playerHand->GetSize() )
        {
            if ( playerHand->GetCard(i++)->GetSuit() == cpuCard->GetSuit() )
                validCards = true;
        }

        // Now disable the other cards if valid ones were found.
        if ( validCards )
        {
            Card* card;

            for ( i = 0; i < playerHand->GetSize(); i++ )
            {
                card = playerHand->GetCard(i);

                if ( card->GetSuit() != cpuCard->GetSuit() )
                    card->setFlag(QGraphicsItem::ItemIsMovable, false);
            }
        }
    }
}
