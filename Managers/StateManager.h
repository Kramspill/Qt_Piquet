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

signals:
    void              ExecuteDeal(void);
    void              DealComplete(void);

    void              ExecuteExchange(void);
    void              ExchangeComplete(void);

    void              AnnounceDeclaration(State, PlayerNum);

    void              PlayTrick(PlayerNum, bool);

private:
    QStateMachine*    stateMachine;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhase*       trickPhase;
};

#endif // STATEMANAGER_H
