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

        // Inform the card that it has moved.
        EmitCardMovedSignal(card, destination->GetCardArrayType());
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
                           Card::CLUBS, Card::SEVEN));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/8C.svg",
                           Card::CLUBS, Card::EIGHT));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/9C.svg",
                           Card::CLUBS, Card::NINE));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/10C.svg",
                           Card::CLUBS, Card::TEN));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/JC.svg",
                           Card::CLUBS, Card::JACK));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/QC.svg",
                           Card::CLUBS, Card::QUEEN));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/KC.svg",
                           Card::CLUBS, Card::KING));
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/AC.svg",
                           Card::CLUBS, Card::ACE));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/7D.svg",
                           Card::DIAMONDS, Card::SEVEN));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/8D.svg",
                           Card::DIAMONDS, Card::EIGHT));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/9D.svg",
                           Card::DIAMONDS, Card::NINE));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/10D.svg",
                           Card::DIAMONDS, Card::TEN));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/JD.svg",
                           Card::DIAMONDS, Card::JACK));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/QD.svg",
                           Card::DIAMONDS, Card::QUEEN));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/KD.svg",
                           Card::DIAMONDS, Card::KING));
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/AD.svg",
                           Card::DIAMONDS, Card::ACE));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/7H.svg",
                           Card::HEARTS, Card::SEVEN));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/8H.svg",
                           Card::HEARTS, Card::EIGHT));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/9H.svg",
                           Card::HEARTS, Card::NINE));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/10H.svg",
                           Card::HEARTS, Card::TEN));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/JH.svg",
                           Card::HEARTS, Card::JACK));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/QH.svg",
                           Card::HEARTS, Card::QUEEN));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/KH.svg",
                           Card::HEARTS, Card::KING));
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/AH.svg",
                           Card::HEARTS, Card::ACE));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/7S.svg",
                           Card::SPADES, Card::SEVEN));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/8S.svg",
                           Card::SPADES, Card::EIGHT));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/9S.svg",
                           Card::SPADES, Card::NINE));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/10S.svg",
                           Card::SPADES, Card::TEN));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/JS.svg",
                           Card::SPADES, Card::JACK));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/QS.svg",
                           Card::SPADES, Card::QUEEN));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/KS.svg",
                           Card::SPADES, Card::KING));
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                           Card::SPADES, Card::ACE));
}


//------------------------------------------------------------------------------
// SetInitialCardPositions - Set the initial positions for cards added to the
//                           various CardArrays held by CardManager.
//------------------------------------------------------------------------------
void CardManager::SetInitialCardPositions(void)
{
    //deck->SetZPosOnly(true);
    //deck->UpdateNextPosition(0, 0);

    talon->SetZPosOnly(true); // Shifted if exposed.
    talon->UpdateNextPosition(-300, -100);

    playerHand->SetZPosOnly(false);
    playerHand->UpdateNextPosition(-150, 190);

    cpuHand->SetZPosOnly(false);
    cpuHand->UpdateNextPosition(-150, -350);

    //playerDiscards->SetZPosOnly(true); // Shifted if exposed.
    //playerDiscards->UpdateNextPosition(100, 50);

    //cpuDiscards->SetZPosOnly(true);
    //cpuDiscards->UpdateNextPosition(100, -50);

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
        card->setPos(QPointF(-300 + (index*2), -350));

        scene->addItem(card);
    }
}


//------------------------------------------------------------------------------
// ShuffleDeck - Shuffle the deck.
//------------------------------------------------------------------------------
void CardManager::ShuffleDeck(void)
{
    deck->Shuffle();
}


//------------------------------------------------------------------------------
// EmitCardMovedSignal - Send a signal to the card, informing it that it has
//                       moved.
//------------------------------------------------------------------------------
void CardManager::EmitCardMovedSignal(Card* card,
                                      CardArray::CardArrayType cardArrayType)
{
    // Emit a signal to update the animation regardless of
    // where the card is going.
    emit card->CardMoved();

    // Emit a signal to tell the card to change states.
    switch ( cardArrayType )
    {
        case CardArray::PLAYERHAND:
            emit card->InPlayerHand();
            break;

        case CardArray::CPUHAND:
            emit card->InCpuHand();
            break;

        case CardArray::TALON:
            emit card->InTalon();
            break;

        default:
            break;
    }
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
