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
    // Initialize the CardArray member variables.
    deck           = new CardArray(CardArray::DECK,           -150,     0);
    talon          = new CardArray(CardArray::TALON,          -300,  -100);
    playerHand     = new CardArray(CardArray::PLAYERHAND,     - 50,   190);
    cpuHand        = new CardArray(CardArray::CPUHAND,        - 50,  -350);
    playerDiscards = new CardArray(CardArray::PLAYERDISCARDS,  210,    20);
    cpuDiscards    = new CardArray(CardArray::CPUDISCARDS,     210,  -180);
    previousTricks = new CardArray(CardArray::PREVIOUSTRICKS, - 50,     0);

    // Initialize the timer to allow animation to finish before informing of
    // state changes.
    transitionTimer = new QTimer();
    transitionTimer->setSingleShot(true);

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
    int size = source->GetSelectedCardsSize();

    if ( size > 0 )
    {
        for (int index = 0; index < size; index++)
        {
            // Remove the card from the source array, and add it to the
            // destination.
            Card* card = source->RemoveSelectedCard();
            destination->AddCard(card);
        }

        // Delay the signal of transfer completion for animation purposes.
        transitionTimer->start(100);

        // Report back how many cards were transferred.
        emit SignalNumOfCardsTransferred(size);
    }
}


//------------------------------------------------------------------------------
// GetDeck - Accessor for CardManager's deck member variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetDeck(void)
{
   return deck;
}


//------------------------------------------------------------------------------
// GetTalon - Accessor for CardManager's talon member variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetTalon(void)
{
    return talon;
}


//------------------------------------------------------------------------------
// GetPlayerHand - Accessor for CardManager's playerHand member variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetPlayerHand(void)
{
    return playerHand;
}


//------------------------------------------------------------------------------
// GetCpuHand - Accessor for CardManager's cpuHand member variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetCpuHand(void)
{
    return cpuHand;
}


//------------------------------------------------------------------------------
// GetPlayerDiscards - Accessor for CardManager's playerDiscards member
//                     variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetPlayerDiscards(void)
{
    return playerDiscards;
}


//------------------------------------------------------------------------------
// GetCpuDiscards - Accessor for CardManager's cpuDiscards member variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetCpuDiscards(void)
{
    return cpuDiscards;
}


//------------------------------------------------------------------------------
// GetPreviousTricks - Accessor for CardManager's previousTricks member
//                     variable.
//------------------------------------------------------------------------------
CardArray* CardManager::GetPreviousTricks(void)
{
    return previousTricks;
}


//------------------------------------------------------------------------------
// GetCurrentTrick - Accessor for CardManager's currentTrick member variable.
//------------------------------------------------------------------------------
Card CardManager::GetCurrentTrick(void)
{
    return currentTrick;
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
// GetDesiredCardArray - Return the CardArray associated with a given type.
//------------------------------------------------------------------------------
CardArray* CardManager::GetDesiredCardArray(
        CardArray::CardArrayType cardArrayType)
{
    CardArray* returnedArray = 0;

    switch ( cardArrayType )
    {
        case CardArray::DECK:
            returnedArray = GetDeck();
            break;

        case CardArray::TALON:
            returnedArray = GetTalon();
            break;

        case CardArray::PLAYERHAND:
            returnedArray = GetPlayerHand();
            break;

        case CardArray::CPUHAND:
            returnedArray = GetCpuHand();
            break;

        case CardArray::PLAYERDISCARDS:
            returnedArray = GetPlayerDiscards();
            break;

        case CardArray::CPUDISCARDS:
            returnedArray = GetCpuDiscards();
            break;

        case CardArray::PREVIOUSTRICKS:
            returnedArray = GetPreviousTricks();
            break;

        default:
            break;
    }

    return returnedArray;
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to/from this class.
//------------------------------------------------------------------------------
void CardManager::ConnectSignals(void)
{
    connect(transitionTimer, SIGNAL(timeout()), this,
            SIGNAL(TransferComplete()));

    connect(playerHand, SIGNAL(SignalValidSelection()), this,
            SIGNAL(SignalValidSelection()));
}


//------------------------------------------------------------------------------
// CallTransferSelectedCards - Helper function for TransferSelectedCards.
//------------------------------------------------------------------------------
void CardManager::CallTransferSelectedCards(CardArray::CardArrayType src,
                                            CardArray::CardArrayType dest)
{
    CardArray* source      = GetDesiredCardArray(src);
    CardArray* destination = GetDesiredCardArray(dest);

    TransferSelectedCards(source, destination);
}


//------------------------------------------------------------------------------
// CallCheckSelection - Check the selection in the CardArray is correct for
//                      the phase the game is in.
//------------------------------------------------------------------------------
void CardManager::CallCheckSelection(CardArray::SelectionType phase,
                                     CardArray::CardArrayType cardArrayType)
{
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);
    cardArray->CheckSelection(phase);
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
