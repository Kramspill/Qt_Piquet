#ifndef DEALPHASE_H
#define DEALPHASE_H

#include "Phase.h"

class DealPhase : public Phase
{
public:
    DealPhase(void);
    DealPhase(DealPhase& other);
    ~DealPhase(void);

    char* GetName(void);
    void  Execute(void);

private:
    char* name;
};

#endif // DEALPHASE_H
