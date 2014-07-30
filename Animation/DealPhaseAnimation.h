#ifndef DEALPHASEANIMATION_H
#define DEALPHASEANIMATION_H

#include "PhaseAnimation.h"

class DealPhaseAnimation : public PhaseAnimation
{
public:
    DealPhaseAnimation(void);
    DealPhaseAnimation(DealPhaseAnimation&);
    ~DealPhaseAnimation(void);

    void Initialize(void);
    void Execute(void);
};

#endif // DEALPHASEANIMATION_H
