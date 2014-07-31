#ifndef TRICKPHASEANIMATION_H
#define TRICKPHASEANIMATION_H

#include "PhaseAnimation.h"

class TrickPhaseAnimation : public PhaseAnimation
{
public:
    TrickPhaseAnimation(void);
    TrickPhaseAnimation(TrickPhaseAnimation&);
    ~TrickPhaseAnimation(void);

    void Initialize(void);
    void Execute(void);
};

#endif // TRICKPHASEANIMATION_H
