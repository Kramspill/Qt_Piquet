//------------------------------------------------------------------------------
// Filename: ElderSelect.h
// Description: Header file for ElderSelect.
//------------------------------------------------------------------------------

#ifndef ELDERSELECT_H
#define ELDERSELECT_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QFinalState>
#include <QStateMachine>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"


//------------------------------------------------------------------------------
// Class: ElderSelect
//------------------------------------------------------------------------------
class ElderSelect : public QState
{
    Q_OBJECT
public:
    ElderSelect(QState* parent = 0);
    ElderSelect(ElderSelect&);
    ~ElderSelect(void);

    void           Initialize(void);

protected:
    void           onEntry(QEvent*);

private:
    void           ConnectSignals(void);

signals:
    void           ExecuteElderSelect(void);
    void           ElderSelectComplete(void);
    void           ElderSelectFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        awaitingSignal;
    QFinalState*   finalState;
};

#endif // ELDERSELECT_H
