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
#include "State/TrickPhase.h"


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

    void              Initialize(QPushButton* button, QPushButton* button2,
                                 QPushButton* button3, QPushButton* button4);

    DealPhase*        GetDealPhase(void);
    ExchangePhase*    GetExchangePhase(void);
    DeclarationPhase* GetDeclarationPhase(void);
    TrickPhase*       GetTrickPhase(void);

private:
    void              ConnectSignals(void);

signals:
    void              SignalCardTransfer(CardArray::CardArrayType,
                                         CardArray::CardArrayType, int);
    void              SignalTransferSelectedCards(CardArray::CardArrayType,
                                                  CardArray::CardArrayType);
    void              SignalSetCardsSelectable(bool, int);
    void              SignalTransferComplete(void);
    void              SignalNumOfCardsTransferred(int);

private:
    QStateMachine*    stateMachine;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhase*       trickPhase;
};

#endif // STATEMANAGER_H
