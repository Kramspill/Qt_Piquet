#ifndef TRICKPHASE_H
#define TRICKPHASE_H

#include "Phase.h"

class TrickPhase : public Phase
{
public:
    TrickPhase(void);
    TrickPhase(TrickPhase& other);
    ~TrickPhase(void);

    void Initialize(void);
    void Execute(void);

    char* GetName(void);

private:
    char* name;
};

#endif // TRICKPHASE_H
