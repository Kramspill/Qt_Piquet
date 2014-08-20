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
#include "State/DealPhase.h"
#include "State/ExchangePhase.h"
#include "State/DeclarationPhase.h"
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

    DealPhase*        GetDealPhase(void);
    ExchangePhase*    GetExchangePhase(void);
    DeclarationPhase* GetDeclarationPhase(void);
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
    void                   SignalNumOfCardsTransferred(int);

private:
    QStateMachine*         stateMachine;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhaseState*       trickPhaseState;
};

#endif // STATEMANAGER_H
