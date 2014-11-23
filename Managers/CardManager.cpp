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
    previousTricks = new CardArray(CardArray::PREVIOUSTRICKS,  x-100,  y);

    // Initialize the timer to allow animation to finish before informing of
    // state changes.
    transitionTimer = new QTimer();
    transitionTimer->setSingleShot(true);

    // Initialize the member that keeps track of the number of cards transferred
    // from the most recent card transaction.
    numOfCardsTransferred = 0;

    // Connect signals to/from this class.
    ConnectSignals();

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
void CardManager::TransferCards(CardArray* source, CardArray* destination,
                                int numberOfCards)
{
    for (int index = 0; index < numberOfCards; index++)
    {
        // Remove the card from the source array, and add it to the destination.
        Card* card = source->RemoveTopCard();
        destination->AddCard(card);
    }

    // Update the number of cards transferred.
    numOfCardsTransferred = numberOfCards;

    // Delay the signal of transfer completion for animation purposes.
    transitionTimer->start(100);
}


//------------------------------------------------------------------------------
// TransferSelectedCards - Transfer a cardArray's selected cards to another
//                         CardArray.
//------------------------------------------------------------------------------
void CardManager::TransferSelectedCards(CardArray* source,
                                        CardArray* destination)
{
    int numberOfCards = source->GetSelectedCardsSize();

    if ( numberOfCards > 0 )
    {
        for (int index = 0; index < numberOfCards; index++)
        {
            // Remove the card from the source array, and add it to the
            // destination.
            Card* card = source->RemoveSelectedCard();
            destination->AddCard(card);
        }

        // Update the number of cards transferred.
        numOfCardsTransferred = numberOfCards;

        // Delay the signal of transfer completion for animation purposes.
        transitionTimer->start(100);
    }
}


//------------------------------------------------------------------------------
// GetDesiredCardArray - Return the CardArray associated with a given type.
//------------------------------------------------------------------------------
CardArray* CardManager::GetDesiredCardArray(
        CardArray::CardArrayType cardArrayType)
{
    CardArray* returnedArray = 0;

    switch ( cardArrayType )
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

        case CardArray::PREVIOUSTRICKS:
            returnedArray = previousTricks;
            break;

        default:
            break;
    }

    return returnedArray;
}


//------------------------------------------------------------------------------
// GetCurrentTrick - Accessor for CardManager's currentTrick member variable.
//------------------------------------------------------------------------------
Card CardManager::GetCurrentTrick(void)
{
    return currentTrick;
}


//------------------------------------------------------------------------------
// GetSelectionScore - Get the score of the user's current selection.
//------------------------------------------------------------------------------
ScoreManager::PhaseScore CardManager::GetSelectionScore(CardArray::SelectionType
                                                        phase)
{
    return playerHand->GetSelectionScore(phase);
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to/from this class.
//------------------------------------------------------------------------------
void CardManager::ConnectSignals(void)
{
    connect(transitionTimer, SIGNAL(timeout()), this,
            SLOT(SignalTransferComplete()));
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
// SetCardsMoveable - Enable/Disable a CardArray's cards to be moveable.
//------------------------------------------------------------------------------
void CardManager::SetCardsMoveable(bool setMoveable,
                                   CardArray::CardArrayType cardArrayType)
{
    Card*      card;
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    // Loop through the array setting the ItemIsMovable property.
    for ( int index = 0; index < cardArray->GetSize(); index++ )
    {
        card = cardArray->GetCard(index);

        if ( setMoveable )
        {
            card->setFlag(QGraphicsItem::ItemIsMovable, true);
            emit InformCardsMoveable(true);
        }
        else
        {
            card->setFlag(QGraphicsItem::ItemIsMovable, false);
            InformCardsMoveable(false);
        }
    }
}


//------------------------------------------------------------------------------
// SetCardsSelectable - Enable/Disable a CardArray's cards to be selected.
//------------------------------------------------------------------------------
void CardManager::SetCardsSelectable(bool setSelectable, int limit,
                                     CardArray::CardArrayType cardArrayType)
{
    Card*      card;
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    // Set the limit of how many cards can be selected at once.
    cardArray->SetSelectionLimit(limit);

    // Loop through the array setting the ItemIsSelectable property.
    for ( int index = 0; index < cardArray->GetSize(); index++ )
    {
        card = cardArray->GetCard(index);

        if ( setSelectable )
            card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        else
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}


//------------------------------------------------------------------------------
// CardSelectionsChanged - Inform the card and CardArray that it's selection has
//                         changed.
//------------------------------------------------------------------------------
void CardManager::CardSelectionsChanged(Card* card,
                                        CardArray::CardArrayType cardArrayType)
{
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    // Update the card selections array in the CardArray.
    if ( cardArray->UpdateCardSelections(card) )
    {
        // Update the position of the card based on if it's selected or not.
        card->UpdateSelection();
    }
}


//------------------------------------------------------------------------------
// CallCheckSelection - Check the selection in the CardArray is correct for
//                      the phase the game is in.
//------------------------------------------------------------------------------
bool CardManager::CheckSelection(CardArray::SelectionType phase,
                                 CardArray::CardArrayType cardArrayType)
{
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    return cardArray->CheckSelection(phase);
}


//------------------------------------------------------------------------------
// SignalTransferComplete - Inform the gameManager that a card transfer has
//                          finished.
//------------------------------------------------------------------------------
void CardManager::SignalTransferComplete(void)
{
    emit TransferComplete(numOfCardsTransferred);
}
