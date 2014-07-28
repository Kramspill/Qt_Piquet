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

// Accessor for CardManager's deck member.
CardArray CardManager::GetDeck(void)
{
   return deck;
}

// Accessor for CardManager's talon member.
CardArray CardManager::GetTalon(void)
{
    return talon;
}

// Accessor for CardManager's playerHand member.
CardArray CardManager::GetPlayerHand(void)
{
    return playerHand;
}

// Accessor for CardManager's cpuHand member.
CardArray CardManager::GetCPUHand(void)
{
    return cpuHand;
}

// Accessor for CardManager's playerDiscards member.
CardArray CardManager::GetPlayerDiscards(void)
{
    return playerDiscards;
}

// Accessor for CardManager's cpuDiscards member.
CardArray CardManager::GetCPUDiscards(void)
{
    return cpuDiscards;
}

// Accessor for CardManager's previousTricks member.
CardArray CardManager::GetPreviousTricks(void)
{
    return previousTricks;
}

// Accessor for CardManager's currentTrick member.
Card CardManager::GetCurrentTrick(void)
{
    return currentTrick;
}
