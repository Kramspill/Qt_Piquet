#include "GameManager.h"

// Constructor.
GameManager::GameManager(void)
{
}

// Copy Constructor.
GameManager::GameManager(GameManager&)
{
}

// Destructor.
GameManager::~GameManager(void)
{
}

// Initialize all other managers.
void GameManager::Initialize(void)
{
    windowManager = new WindowManager;
    windowManager->Initialize();
}

// Accessor for GameManager's stateManager member.
StateManager* GameManager::GetStateManager(void)
{
    return stateManager;
}

// Accessor for GameManager's animationManager member.
AnimationManager* GameManager::GetAnimationManager(void)
{
    return animationManager;
}

// Accessor for GameManager's cardManager member.
CardManager* GameManager::GetCardManager(void)
{
    return cardManager;
}

// Accessor for GameManager's scoreManager member.
ScoreManager* GameManager::GetScoreManager(void)
{
    return scoreManager;
}
