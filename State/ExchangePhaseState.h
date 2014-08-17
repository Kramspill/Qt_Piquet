//------------------------------------------------------------------------------
// Filename: ExchangePhaseState.h
// Description: Header file for ExchangePhaseState.
//------------------------------------------------------------------------------

#ifndef EXCHANGEPHASESTATE_H
#define EXCHANGEPHASESTATE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QStateMachine>
#include <QFinalState>
#include <QEvent>
#include <QTimer>
#include <QPushButton>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Class: ExchangePhaseState
//------------------------------------------------------------------------------
class ExchangePhaseState : public QState
{
    Q_OBJECT
public:
    ExchangePhaseState(QState* parent = 0);
    ExchangePhaseState(ExchangePhaseState&);
    ~ExchangePhaseState(void);

    void           Initialize(QPushButton* button);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private slots:
    void           CheckSelection(void);
    void           TransferPlayerCards(void);
    void           ExecuteCpuExchange(void);
    void           TransferCpuCards(void);

signals:
    void           SignalEnableCardSelection(void);
    void           SignalDisableCardSelection(void);
    void           ValidSelection(void);
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType, int);
    void           RequestSelectedCardsTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType);
    void           PlayerDiscardFinished(void);
    void           CpuExchangeFinished(void);
    void           ExchangePhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QTimer*        playerDiscardTimer;
    QTimer*        playerDrawTimer;
    QTimer*        cpuDiscardTimer;
    QTimer*        cpuDrawTimer;
};

#endif // EXCHANGEPHASESTATE_H
