#include "CardManager.h"

// Constructor.
CardManager::CardManager(void)
{
}

// Copy Constructor.
CardManager::CardManager(CardManager&)
{
}

// Destructor.
CardManager::~CardManager(void)
{
}

// Allocate space for each card, initialize the deck to
// contain all the cards and shuffle the deck.
void CardManager::Initialize(QGraphicsScene* scene)
{
    // Initialize all the cards used in the game
    // to begin in the deck.
    InitializeDeck();

    // Add the cards (initially in the deck) to the scene.
    AddCardsToScene(scene);

    // Allocate space for other members.
    talon          = new CardArray();
    playerHand     = new CardArray();
    cpuHand        = new CardArray();
    playerDiscards = new CardArray();
    cpuDiscards    = new CardArray();
    previousTricks = new CardArray();
}

// Accessor for CardManager's deck member.
CardArray* CardManager::GetDeck(void)
{
   return deck;
}

// Accessor for CardManager's talon member.
CardArray* CardManager::GetTalon(void)
{
    return talon;
}

// Accessor for CardManager's playerHand member.
CardArray* CardManager::GetPlayerHand(void)
{
    return playerHand;
}

// Accessor for CardManager's cpuHand member.
CardArray* CardManager::GetCPUHand(void)
{
    return cpuHand;
}

// Accessor for CardManager's playerDiscards member.
CardArray* CardManager::GetPlayerDiscards(void)
{
    return playerDiscards;
}

// Accessor for CardManager's cpuDiscards member.
CardArray* CardManager::GetCPUDiscards(void)
{
    return cpuDiscards;
}

// Accessor for CardManager's previousTricks member.
CardArray* CardManager::GetPreviousTricks(void)
{
    return previousTricks;
}

// Accessor for CardManager's currentTrick member.
Card CardManager::GetCurrentTrick(void)
{
    return currentTrick;
}

// Initialize a CardArray that will contain all cards used
// in the game.
void CardManager::InitializeDeck(void)
{
    // Allocate space for the CardArray.
    deck = new CardArray();

    // Create and add all cards to the CardArray.
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/7C.svg"), Card::CLUBS, Card::SEVEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/8C.svg"), Card::CLUBS, Card::EIGHT));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/9C.svg"), Card::CLUBS, Card::NINE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/10C.svg"), Card::CLUBS, Card::TEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/JC.svg"), Card::CLUBS, Card::JACK));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/QC.svg"), Card::CLUBS, Card::QUEEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/KC.svg"), Card::CLUBS, Card::KING));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/AC.svg"), Card::CLUBS, Card::ACE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/7D.svg"), Card::DIAMONDS, Card::SEVEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/8D.svg"), Card::DIAMONDS, Card::EIGHT));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/9D.svg"), Card::DIAMONDS, Card::NINE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/10D.svg"), Card::DIAMONDS, Card::TEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/JD.svg"), Card::DIAMONDS, Card::JACK));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/QD.svg"), Card::DIAMONDS, Card::QUEEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/KD.svg"), Card::DIAMONDS, Card::KING));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/AD.svg"), Card::DIAMONDS, Card::ACE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/7H.svg"), Card::HEARTS, Card::SEVEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/8H.svg"), Card::HEARTS, Card::EIGHT));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/9H.svg"), Card::HEARTS, Card::NINE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/10H.svg"), Card::HEARTS, Card::TEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/JH.svg"), Card::HEARTS, Card::JACK));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/QH.svg"), Card::HEARTS, Card::QUEEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/KH.svg"), Card::HEARTS, Card::KING));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/AH.svg"), Card::HEARTS, Card::ACE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/7S.svg"), Card::SPADES, Card::SEVEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/8S.svg"), Card::SPADES, Card::EIGHT));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/9S.svg"), Card::SPADES, Card::NINE));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/10S.svg"), Card::SPADES, Card::TEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/JS.svg"), Card::SPADES, Card::JACK));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/QS.svg"), Card::SPADES, Card::QUEEN));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/KS.svg"), Card::SPADES, Card::KING));
    deck->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/AS.svg"), Card::SPADES, Card::ACE));
}

void CardManager::AddCardsToScene(QGraphicsScene* scene)
{
    QGraphicsSvgItem* cardImage;
    for (int index = 0; index < deck->GetSize(); index++)
    {
        cardImage = deck->GetCard(index)->GetCardImage();

        cardImage->setFlag(QGraphicsItem::ItemIsMovable, true);
        cardImage->setScale(0.5);
        cardImage->setPos(QPointF(-350 + (index*2), -530));

        scene->addItem(cardImage);
    }
}

// Add all cards to the deck and shuffle the deck.
void CardManager::ResetDeck(void)
{
    deck->Shuffle();
}
