#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QPushButton>
#include <QStateMachine>

#include "Cards/CardArray.h"
#include "State/DealPhaseState.h"
#include "State/ExchangePhaseState.h"
#include "State/DeclarationPhaseState.h"
#include "State/TrickPhaseState.h"

class StateManager
{
public:
    StateManager(void);
    StateManager(StateManager&);
    ~StateManager(void);

    void Initialize(CardArray* deck, QPushButton* button);

    DealPhaseState*        GetDealPhase(void);
    ExchangePhaseState*    GetExchangePhase(void);
    DeclarationPhaseState* GetDeclarationPhase(void);
    TrickPhaseState*       GetTrickPhase(void);

private:
    QStateMachine*         stateMachine;
    DealPhaseState*        dealPhaseState;
    ExchangePhaseState*    exchangePhaseState;
    DeclarationPhaseState* declarationPhaseState;
    TrickPhaseState*       trickPhaseState;
};

#endif // STATEMANAGER_H
