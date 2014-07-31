#include "ScoreManager.h"

// Constructor.
ScoreManager::ScoreManager(void)
{
}

// Copy Constructor.
ScoreManager::ScoreManager(ScoreManager&)
{
}

// Destructor.
ScoreManager::~ScoreManager(void)
{
}

void ScoreManager::Initialize(void)
{

}

// Accessor for ScoreManager's playerScore member.
unsigned int ScoreManager::GetPlayerScore(void)
{
    return playerScore;
}

// Accessor for ScoreManager's cpuScore member.
unsigned int ScoreManager::GetCPUScore(void)
{
    return cpuScore;
}
