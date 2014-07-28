#ifndef EXCHANGEPHASEANIMATION_H
#define EXCHANGEPHASEANIMATION_H

#include "PhaseAnimation.h"

class ExchangePhaseAnimation : public PhaseAnimation
{
public:
    ExchangePhaseAnimation(void);
    ExchangePhaseAnimation(ExchangePhaseAnimation&);
    ~ExchangePhaseAnimation(void);

    void ExecuteAnimation(void);
};

#endif // EXCHANGEPHASEANIMATION_H
