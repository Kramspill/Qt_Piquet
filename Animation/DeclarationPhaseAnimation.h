#ifndef DECLARATIONPHASEANIMATION_H
#define DECLARATIONPHASEANIMATION_H

#include "PhaseAnimation.h"

class DeclarationPhaseAnimation : public PhaseAnimation
{
public:
    DeclarationPhaseAnimation(void);
    DeclarationPhaseAnimation(DeclarationPhaseAnimation&);
    ~DeclarationPhaseAnimation(void);

    void Execute(void);
};

#endif // DECLARATIONPHASEANIMATION_H
