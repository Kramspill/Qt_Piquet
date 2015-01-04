//------------------------------------------------------------------------------
// Filename: Summary.h
// Description: Header file for Summary.
//------------------------------------------------------------------------------

#ifndef SUMMARY_H
#define SUMMARY_H

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
// Class: Summary
//------------------------------------------------------------------------------
class Summary : public QState
{
    Q_OBJECT
public:
    Summary(QState* parent = 0);
    Summary(Summary&);
    ~Summary(void);

    void           Initialize(void);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

signals:
    void           ExecuteSummary(void);
    void           SummaryComplete(void);
    void           NewGame(void);
    void           NextHand(void);

private:
    QStateMachine* stateMachine;
    QState*        awaitingSignal;
    QFinalState*   finalState;
};

#endif // SUMMARY_H
