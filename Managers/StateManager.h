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

    void              Initialize(void);

private:
    void              ConnectSignals(void);

private slots:
    void              SignalTransferComplete(int numOfCardsTransferred);
    void              AIProcessingComplete(void);

signals:
    void              RequestCardTransfer(CardLayout::Type,
                                          CardLayout::Type,
                                          int, bool);
    void              TransferComplete(int);

    void              SetCardsSelectable(bool, int);
    void              DeclareSelection(CardLayout::SelectionType);

    void              RequestDialog(Dialog::DialogType);
    void              ExecuteDeal(void);

    void              SignalAI(AI::AIAction);
    void              UpdateAI(void);

private:
    QStateMachine*    stateMachine;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhase*       trickPhase;
};

#endif // STATEMANAGER_H
