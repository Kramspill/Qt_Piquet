#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QPushButton>
#include <QStateMachine>

#include "State/DealPhaseState.h"
#include "State/ExchangePhaseState.h"
#include "State/DeclarationPhaseState.h"
#include "State/TrickPhaseState.h"

class StateManager
{
public:
    ~StateManager(void);

    static StateManager& GetSingleton(void);

    void Initialize(QPushButton* button);

    DealPhaseState*        GetDealPhase(void);
    ExchangePhaseState*    GetExchangePhase(void);
    DeclarationPhaseState* GetDeclarationPhase(void);
    TrickPhaseState*       GetTrickPhase(void);

private:
    StateManager(void) {}
    StateManager(StateManager&);
    void operator=(StateManager&);

private:
    QStateMachine*         stateMachine;
    DealPhaseState*        dealPhaseState;
    ExchangePhaseState*    exchangePhaseState;
    DeclarationPhaseState* declarationPhaseState;
    TrickPhaseState*       trickPhaseState;
};

#endif // STATEMANAGER_H
