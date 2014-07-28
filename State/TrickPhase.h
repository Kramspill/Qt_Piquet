#ifndef TRICKPHASE_H
#define TRICKPHASE_H

#include "Phase.h"

class TrickPhase : public Phase
{
public:
    TrickPhase(void);
    TrickPhase(TrickPhase&);
    ~TrickPhase(void);

    char* GetName(void);
    void  Execute(void);

private:
    char* name;
};

#endif // TRICKPHASE_H
