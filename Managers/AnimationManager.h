#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Animation/PhaseAnimation.h"
#include "Animation/DealPhaseAnimation.h"
#include "Animation/ExchangePhaseAnimation.h"
#include "Animation/DeclarationPhaseAnimation.h"
#include "Animation/TrickPhaseAnimation.h"

class AnimationManager
{
public:
    AnimationManager(void);
    AnimationManager(AnimationManager&);
    ~AnimationManager(void);

    PhaseAnimation* GetDealPhaseAnimation(void);
    PhaseAnimation* GetExchangePhaseAnimation(void);
    PhaseAnimation* GetDeclarationPhaseAnimation(void);
    PhaseAnimation* GetTrickPhaseAnimation(void);

private:
    DealPhaseAnimation*        dealPhaseAnimation;
    ExchangePhaseAnimation*    exchangePhaseAnimation;
    DeclarationPhaseAnimation* declarationPhaseAnimation;
    TrickPhaseAnimation*       trickPhaseAnimation;
};

#endif // ANIMATIONMANAGER_H
