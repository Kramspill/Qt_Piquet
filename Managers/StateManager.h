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
#include "State/ElderSelect.h"
#include "State/DealPhase.h"
#include "State/ExchangePhase.h"
#include "State/DeclarationPhase.h"
#include "State/TrickPhase.h"
#include "State/Summary.h"


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
    void              ExecuteElderSelect(void);
    void              ElderSelectComplete(void);

    void              ExecuteDeal(void);
    void              DealComplete(void);

    void              ExecuteExchange(void);
    void              ExchangeComplete(void);

    void              AnnounceDeclaration(State, PlayerNum);

    void              PlayTrick(PlayerNum);

    void              ExecuteSummary(void);
    void              SummaryComplete(void);

private:
    QStateMachine*    stateMachine;
    ElderSelect*      elderSelect;
    DealPhase*        dealPhase;
    ExchangePhase*    exchangePhase;
    DeclarationPhase* declarationPhase;
    TrickPhase*       trickPhase;
    Summary*          summary;
};

#endif // STATEMANAGER_H
