#ifndef DEALPHASE_H
#define DEALPHASE_H

#include "Phase.h"

class DealPhase : public Phase
{
public:
    DealPhase(void);
    DealPhase(DealPhase& other);
    ~DealPhase(void);

    void Initialize(void);
    void Execute(void);

    char* GetName(void);

private:
    char* name;
    QStateMachine* dealPhaseStateMachine;
    QState*        dealToPlayer;
    QState*        dealToCPU;
    QFinalState*   dealTalon;
};

#endif // DEALPHASE_H
