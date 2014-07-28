#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State/Phase.h"
#include "State/DealPhase.h"
#include "State/ExchangePhase.h"
#include "State/DeclarationPhase.h"
#include "State/TrickPhase.h"

class StateManager
{
public:
    StateManager(void);
    StateManager(StateManager&);
    ~StateManager(void);

    Phase* GetCurrentPhase(void);
    Phase* GetDealPhase(void);
    Phase* GetExchangePhase(void);
    Phase* GetDeclarationPhase(void);
    Phase* GetTrickPhase(void);

private:
    void   CycleCurrentPhase(void);

private:
    Phase*            currentPhase;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhase*       trickPhase;
};

#endif // STATEMANAGER_H
