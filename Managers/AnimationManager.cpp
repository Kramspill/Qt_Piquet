#include "AnimationManager.h"

// Constructor.
AnimationManager::AnimationManager(void)
{
}

// Copy Constructor.
AnimationManager::AnimationManager(AnimationManager&)
{
}

// Destructor.
AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::Initialize(void)
{
    // Allocate memory to members and initialize them.
    dealPhaseAnimation = new DealPhaseAnimation();
    dealPhaseAnimation->Initialize();

    exchangePhaseAnimation = new ExchangePhaseAnimation();
    exchangePhaseAnimation->Initialize();

    declarationPhaseAnimation = new DeclarationPhaseAnimation();
    declarationPhaseAnimation->Initialize();

    trickPhaseAnimation = new TrickPhaseAnimation();
    trickPhaseAnimation->Initialize();
}

// Accessor for AnimationManager's dealPhaseAnimation member.
PhaseAnimation* AnimationManager::GetDealPhaseAnimation(void)
{
    return dealPhaseAnimation;
}

// Accessor for AnimationManager's exchangePhaseAnimation member.
PhaseAnimation* AnimationManager::GetExchangePhaseAnimation(void)
{
    return exchangePhaseAnimation;
}

// Accessor for AnimationManager's declarationPhaseAnimation member.
PhaseAnimation* AnimationManager::GetDeclarationPhaseAnimation(void)
{
    return declarationPhaseAnimation;
}

// Accessor for AnimationManager's trickPhaseAnimation member.
PhaseAnimation* AnimationManager::GetTrickPhaseAnimation(void)
{
    return trickPhaseAnimation;
}
