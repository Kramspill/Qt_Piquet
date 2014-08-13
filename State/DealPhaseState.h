//------------------------------------------------------------------------------
// Filename: DealPhaseState.h
// Description: Header file for DealPhaseState.
//------------------------------------------------------------------------------

#ifndef DEALPHASESTATE_H
#define DEALPHASESTATE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QFinalState>
#include <QEvent>
#include <QStateMachine>
#include <QPushButton>
#include <QTimer>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Class: DealPhaseState
//------------------------------------------------------------------------------
class DealPhaseState : public QState
{
    Q_OBJECT
public:
    DealPhaseState(QState* parent = 0);
    DealPhaseState(DealPhaseState&);
    ~DealPhaseState(void);

    void           Initialize(QPushButton* button);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ResetDealCounter(void);

private slots:
    void           DealToPlayer(void);
    void           DealToCpu(void);
    void           DealTalon(void);

signals:
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType, int);
    void           BeginDealToPlayer(void);
    void           BeginDealToCpu(void);
    void           BeginDealTalon(void);
    void           DealTalonFinished(void);
    void           DealPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QTimer*        DealToPlayerTimer;
    QTimer*        DealToCpuTimer;
    QTimer*        DealTalonTimer;
    int            dealCounter;
};

#endif // DEALPHASESTATE_H
