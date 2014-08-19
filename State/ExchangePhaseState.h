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
#include <QFinalState>
#include <QStateMachine>
#include <QEvent>
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

public slots:
    void           CallTransferComplete(void);
    void           SetNumCardsTransferred(int numCardsTransferred);

private slots:
    void           SignalEnableCardsSelectable(void);
    void           SignalDisableCardsSelectable(void);
    void           PlayerDiscards(void);
    void           PlayerDrawFromTalon(void);
    void           CpuDiscards(void);
    void           CpuDrawFromTalon(void);

signals:
    void           RequestCardsSelectable(bool);
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType, int);
    void           RequestSelectedCardsTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType);
    void           TransferComplete(void);
    void           ExchangePhaseFinished(void);

private:
    QStateMachine* stateMachine;
    int            cardsTransferred;
};

#endif // EXCHANGEPHASESTATE_H
