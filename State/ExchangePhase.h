#ifndef EXCHANGEPHASE_H
#define EXCHANGEPHASE_H

#include "Phase.h"

class ExchangePhase : public Phase
{
public:
    ExchangePhase(void);
    ExchangePhase(ExchangePhase&);
    ~ExchangePhase(void);

    char* GetName(void);
    void  Execute(void);

private:
    char* name;
};

#endif // EXCHANGEPHASE_H
