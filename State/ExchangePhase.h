#ifndef EXCHANGEPHASE_H
#define EXCHANGEPHASE_H

#include "Phase.h"

class ExchangePhase : public Phase
{
public:
    ExchangePhase(void);
    ExchangePhase(ExchangePhase& other);
    ~ExchangePhase(void);

    void Initialize(void);
    void Execute(void);

    char* GetName(void);

private:
    char* name;
};

#endif // EXCHANGEPHASE_H
