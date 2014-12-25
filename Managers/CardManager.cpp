//------------------------------------------------------------------------------
// Filename: CardManager.cpp
// Description: Manager for the cards used in this game.
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
    // Get the center position for card array placement.
    QPointF p = scene->GetCenterPos();
    int x = (int)p.x();
    int y = (int)p.y();

    // Initialize the CardArray member variables.
    deck           = new CardArray(CardArray::DECK,            x-100,  y);
    talon          = new CardArray(CardArray::TALON,           x-370,  y-70);
    playerHand     = new CardArray(CardArray::PLAYERHAND,      x-130,  y+170);
    cpuHand        = new CardArray(CardArray::CPUHAND,         x-150,  y-295);
    playerDiscards = new CardArray(CardArray::PLAYERDISCARDS,  x+50,   y+20);
    cpuDiscards    = new CardArray(CardArray::CPUDISCARDS,     x+50,   y-150);
    playerTrick    = new CardArray(CardArray::PLAYERTRICK,     x-130,  y+20);
    cpuTrick       = new CardArray(CardArray::CPUTRICK,        x-130,  y-130);
    previousTricks = new CardArray(CardArray::PREVIOUSTRICKS,  x-300,  y-70);

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
// TransferCards - Transfer cards between one CardArray and another.
//------------------------------------------------------------------------------
void CardManager::TransferCards(CardArray* src, CardArray* dest,
                                int numCards)
{
    // Determine if we are transfering specific cards or not.
    if ( numCards == 0 )
    {
        // Check if our destination is a player's hand and perform a deal if so.
        if ( dest->GetType() == CardArray::PLAYERHAND ||
             dest->GetType() == CardArray::CPUHAND )
        {
            numCards = 12 - dest->GetSize();
            DealOutCards(src, dest, numCards);
        }
        else
        {
            // In this case, we are transferring cards that have been selected.
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

        card->setScale(0.4);
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
        dest->AddCard(card);
    }

    // Delay the signal of transfer completion for animation purposes.
    transitionTimer->start(100);

    // Wait for timer to finish.
    QEventLoop* loop = new QEventLoop();
    connect(transitionTimer, SIGNAL(timeout()), loop, SLOT(quit()));
    loop->exec();
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
                 selectedCards.size() > talon->GetSize() )
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
                while ( i < selectedCards.size() && valid )
                {
                    if ( selectedCards[i++]->GetSuit() != suit )
                        valid = false;
                }

                if ( younger == PLAYER1 && valid )
                {
                    // Check if we are responding or not as we need to at least
                    // match the opponents point.
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
                while ( i < selectedCards.size() && valid )
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

                    if ( j < selectedCards.size() )
                    {
                        valid = false;
                    }
                    else if ( younger == PLAYER1 )
                    {
                        // Check if we are responding or not as we need to at
                        // least match the opponents Sequence.
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

                while ( i < selectedCards.size() && valid )
                {
                    if ( selectedCards[i++]->GetRank() != rank )
                        valid = false;
                }

                if ( younger == PLAYER1 && valid )
                {
                    // Check if we are responding or not as we need to at
                    // least match the opponents Sequence.
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
