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

    // Add all cards to the CardArray.
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/7C.svg"), Card::CLUBS, Card::SEVEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/8C.svg"), Card::CLUBS, Card::EIGHT));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/9C.svg"), Card::CLUBS, Card::NINE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/10C.svg"), Card::CLUBS, Card::TEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/JC.svg"), Card::CLUBS, Card::JACK));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/QC.svg"), Card::CLUBS, Card::QUEEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/KC.svg"), Card::CLUBS, Card::KING));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/AC.svg"), Card::CLUBS, Card::ACE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/7D.svg"), Card::DIAMONDS, Card::SEVEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/8D.svg"), Card::DIAMONDS, Card::EIGHT));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/9D.svg"), Card::DIAMONDS, Card::NINE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/10D.svg"), Card::DIAMONDS, Card::TEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/JD.svg"), Card::DIAMONDS, Card::JACK));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/QD.svg"), Card::DIAMONDS, Card::QUEEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/KD.svg"), Card::DIAMONDS, Card::KING));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/AD.svg"), Card::DIAMONDS, Card::ACE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/7H.svg"), Card::HEARTS, Card::SEVEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/8H.svg"), Card::HEARTS, Card::EIGHT));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/9H.svg"), Card::HEARTS, Card::NINE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/10H.svg"), Card::HEARTS, Card::TEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/JH.svg"), Card::HEARTS, Card::JACK));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/QH.svg"), Card::HEARTS, Card::QUEEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/KH.svg"), Card::HEARTS, Card::KING));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/AH.svg"), Card::HEARTS, Card::ACE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/7S.svg"), Card::SPADES, Card::SEVEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/8S.svg"), Card::SPADES, Card::EIGHT));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/9S.svg"), Card::SPADES, Card::NINE));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/10S.svg"), Card::SPADES, Card::TEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/JS.svg"), Card::SPADES, Card::JACK));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/QS.svg"), Card::SPADES, Card::QUEEN));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/KS.svg"), Card::SPADES, Card::KING));
    allCards->AddCard(new Card(QPixmap(":/Cards/Clubs/AS.svg"), Card::SPADES, Card::ACE));
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
