#ifndef EXCHANGEPHASEANIMATION_H
#define EXCHANGEPHASEANIMATION_H

#include "PhaseAnimation.h"

class ExchangePhaseAnimation : public PhaseAnimation
{
public:
    ExchangePhaseAnimation(void);
    ExchangePhaseAnimation(ExchangePhaseAnimation&);
    ~ExchangePhaseAnimation(void);

    void Execute(void);
};

#endif // EXCHANGEPHASEANIMATION_H
