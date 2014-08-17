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
    deck           = new CardArray(CardArray::DECK);
    talon          = new CardArray(CardArray::TALON);
    playerHand     = new CardArray(CardArray::PLAYERHAND);
    cpuHand        = new CardArray(CardArray::CPUHAND);
    playerDiscards = new CardArray(CardArray::PLAYERDISCARDS);
    cpuDiscards    = new CardArray(CardArray::CPUDISCARDS);
    previousTricks = new CardArray(CardArray::PREVIOUSTRICKS);

    // Set the initial card positions for the CardArrays.
    SetInitialCardPositions();

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
        Card* card = source->RemoveCard(index);
        destination->AddCard(card);
    }
}


//------------------------------------------------------------------------------
// TransferSelectedCards - Transfer a cardArray's selected cards to another
//                         CardArray.
//------------------------------------------------------------------------------
void CardManager::TransferSelectedCards(CardArray* source,
                                        CardArray* destination)
{
    int size = source->GetSelectedCardsSize();

    for (int index = 0; index < size; index++)
    {
        // Remove the card from the source array, and add it to the destination.
        Card* card = source->RemoveSelectedCard();
        destination->AddCard(card);
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
// SetInitialCardPositions - Set the initial positions for cards added to the
//                           various CardArrays held by CardManager.
//------------------------------------------------------------------------------
void CardManager::SetInitialCardPositions(void)
{
    deck->SetZPosOnly(true);
    deck->UpdateNextPosition(-150, 0);

    talon->SetZPosOnly(true); // Shifted if exposed.
    talon->UpdateNextPosition(-300, -100);

    playerHand->SetZPosOnly(false);
    playerHand->UpdateNextPosition(-50, 190);

    cpuHand->SetZPosOnly(false);
    cpuHand->UpdateNextPosition(-50, -350);

    playerDiscards->SetZPosOnly(true); // Shifted if exposed.
    playerDiscards->UpdateNextPosition(210, 20);

    cpuDiscards->SetZPosOnly(true);
    cpuDiscards->UpdateNextPosition(210, -180);

    //previousTricks->SetZPosOnly(false);
    //previousTricks->UpdateNextPosition(-50, 0);
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

        card->setFlag(QGraphicsItem::ItemIsMovable, true);
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
    CardArray* returnedArray;

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
// CallTransferCards - Helper function for TransferCards.
//------------------------------------------------------------------------------
void CardManager::CallTransferCards(CardArray::CardArrayType src,
                                    CardArray::CardArrayType dest,
                                    int numOfCards)
{
    CardArray* source      = GetDesiredCardArray(src);
    CardArray* destination = GetDesiredCardArray(dest);

    TransferCards(source, destination, numOfCards);
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
// EnableCardSelection - Enable a CardArray's cards to be selected.
//------------------------------------------------------------------------------
void CardManager::EnableCardSelection(CardArray::CardArrayType cardArrayType)
{
    Card*      card;
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    // Loop through the array setting the ItemIsSelectable property.
    for ( int index = 0; index < cardArray->GetSize(); index++ )
    {
        card = cardArray->GetCard(index);

        card->setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
}


//------------------------------------------------------------------------------
// DisableCardSelection - Disable a CardArray's cards to be selected.
//------------------------------------------------------------------------------
void CardManager::DisableCardSelection(CardArray::CardArrayType cardArrayType)
{
    Card*      card;
    CardArray* cardArray = GetDesiredCardArray(cardArrayType);

    // Loop through the array setting the ItemIsSelectable property.
    for ( int index = 0; index < cardArray->GetSize(); index++ )
    {
        card = cardArray->GetCard(index);

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
