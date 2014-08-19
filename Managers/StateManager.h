//------------------------------------------------------------------------------
// Filename: StateManager.h
// Description: Header file for StateManager.
//------------------------------------------------------------------------------

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>
#include <QPushButton>
#include <QStateMachine>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/DealPhaseState.h"
#include "State/ExchangePhaseState.h"
#include "State/DeclarationPhaseState.h"
#include "State/TrickPhaseState.h"


//------------------------------------------------------------------------------
// Class: StateManager
//------------------------------------------------------------------------------
class StateManager : public QObject
{
    Q_OBJECT
public:
    StateManager(void);
    StateManager(StateManager&);
    ~StateManager(void);

    void                   Initialize(QPushButton* button,
                                      QPushButton* button2);

    DealPhaseState*        GetDealPhaseState(void);
    ExchangePhaseState*    GetExchangePhaseState(void);
    DeclarationPhaseState* GetDeclarationPhaseState(void);
    TrickPhaseState*       GetTrickPhaseState(void);

private:
    void                   ConnectSignals(void);

signals:
    void                   SignalCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int);
    void                   SignalTransferSelectedCards(
                                                 CardArray::CardArrayType,
                                                 CardArray::CardArrayType);
    void                   SignalSetCardsSelectable(bool);
    void                   SignalTransferComplete(void);

private:
    QStateMachine*         stateMachine;
    DealPhaseState*        dealPhaseState;
    ExchangePhaseState*    exchangePhaseState;
    DeclarationPhaseState* declarationPhaseState;
    TrickPhaseState*       trickPhaseState;
};

#endif // STATEMANAGER_H
