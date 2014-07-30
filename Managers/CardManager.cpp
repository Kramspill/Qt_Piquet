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
    AddAllCards(deck);
    deck.Shuffle();
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
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/7C.svg"), CLUBS, SEVEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/8C.svg"), CLUBS, EIGHT));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/9C.svg"), CLUBS, NINE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/10C.svg"), CLUBS, TEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/JC.svg"), CLUBS, JACK));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/QC.svg"), CLUBS, QUEEN);
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/KC.svg"), CLUBS, KING));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/AC.svg"), CLUBS, ACE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/7D.svg"), DIAMONDS, SEVEN);
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/8D.svg"), DIAMONDS, EIGHT));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/9D.svg"), DIAMONDS, NINE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/10D.svg"), DIAMONDS, TEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/JD.svg"), DIAMONDS, JACK));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/QD.svg"), DIAMONDS, QUEEN);
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/KD.svg"), DIAMONDS, KING));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/AD.svg"), DIAMONDS, ACE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/7H.svg"), HEARTS, SEVEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/8H.svg"), HEARTS, EIGHT));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/9H.svg"), HEARTS, NINE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/10H.svg"), HEARTS, TEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/JH.svg"), HEARTS, JACK));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/QH.svg"), HEARTS, QUEEN);
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/KH.svg"), HEARTS, KING));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/AH.svg"), HEARTS, ACE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/7S.svg"), SPADES, SEVEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/8S.svg"), SPADES, EIGHT));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/9S.svg"), SPADES, NINE));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/10S.svg"), SPADES, TEN));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/JS.svg"), SPADES, JACK));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/QS.svg"), SPADES, QUEEN);
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/KS.svg"), SPADES, KING));
    allCards->AddCard(Card(QPixmap(":/Cards/Clubs/AS.svg"), SPADES, ACE));
}

// Add all cards to a given CardArray.
void CardManager::AddAllCards(CardArray& cardArray)
{
    for (int index = 0; index < allCards->GetSize(); index++)
    {
        cardArray->AddCard(allCards->GetCards[index]);
    }
}
