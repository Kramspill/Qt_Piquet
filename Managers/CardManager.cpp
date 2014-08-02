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
void CardManager::Initialize(void)
{
    // Initialize all the cards used in the game.
    InitializeAllCards();

    // Allocate space for members.
    deck           = new CardArray();
    talon          = new CardArray();
    playerHand     = new CardArray();
    cpuHand        = new CardArray();
    playerDiscards = new CardArray();
    cpuDiscards    = new CardArray();
    previousTricks = new CardArray();

    // Add all cards to the deck and shuffle the deck.
    ResetDeck();
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
void CardManager::InitializeAllCards(void)
{
    // Allocate space for the CardArray.
    allCards = new CardArray();

    // Create and add all cards to the CardArray.
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/7C.svg"), Card::CLUBS, Card::SEVEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/8C.svg"), Card::CLUBS, Card::EIGHT));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/9C.svg"), Card::CLUBS, Card::NINE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/10C.svg"), Card::CLUBS, Card::TEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/JC.svg"), Card::CLUBS, Card::JACK));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/QC.svg"), Card::CLUBS, Card::QUEEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/KC.svg"), Card::CLUBS, Card::KING));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Clubs/Resources/Clubs/AC.svg"), Card::CLUBS, Card::ACE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/7D.svg"), Card::DIAMONDS, Card::SEVEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/8D.svg"), Card::DIAMONDS, Card::EIGHT));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/9D.svg"), Card::DIAMONDS, Card::NINE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/10D.svg"), Card::DIAMONDS, Card::TEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/JD.svg"), Card::DIAMONDS, Card::JACK));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/QD.svg"), Card::DIAMONDS, Card::QUEEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/KD.svg"), Card::DIAMONDS, Card::KING));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Diamonds/Resources/Diamonds/AD.svg"), Card::DIAMONDS, Card::ACE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/7H.svg"), Card::HEARTS, Card::SEVEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/8H.svg"), Card::HEARTS, Card::EIGHT));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/9H.svg"), Card::HEARTS, Card::NINE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/10H.svg"), Card::HEARTS, Card::TEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/JH.svg"), Card::HEARTS, Card::JACK));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/QH.svg"), Card::HEARTS, Card::QUEEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/KH.svg"), Card::HEARTS, Card::KING));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Hearts/Resources/Hearts/AH.svg"), Card::HEARTS, Card::ACE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/7S.svg"), Card::SPADES, Card::SEVEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/8S.svg"), Card::SPADES, Card::EIGHT));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/9S.svg"), Card::SPADES, Card::NINE));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/10S.svg"), Card::SPADES, Card::TEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/JS.svg"), Card::SPADES, Card::JACK));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/QS.svg"), Card::SPADES, Card::QUEEN));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/KS.svg"), Card::SPADES, Card::KING));
    allCards->AddCard(new Card(new QGraphicsSvgItem(":/Cards/Spades/Resources/Spades/AS.svg"), Card::SPADES, Card::ACE));
}

// Add all cards to the deck and shuffle the deck.
void CardManager::ResetDeck(void)
{
    for (int index = 0; index < allCards->GetSize(); index++)
    {
        deck->AddCard(allCards->GetCard(index));
    }

    deck->Shuffle();
}
