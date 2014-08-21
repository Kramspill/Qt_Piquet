//------------------------------------------------------------------------------
// Filename: ExchangePhase.h
// Description: Header file for ExchangePhase.
//------------------------------------------------------------------------------

#ifndef EXCHANGEPHASE_H
#define EXCHANGEPHASE_H

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
// Class: ExchangePhase
//------------------------------------------------------------------------------
class ExchangePhase : public QState
{
    Q_OBJECT
public:
    ExchangePhase(QState* parent = 0);
    ExchangePhase(ExchangePhase&);
    ~ExchangePhase(void);

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
    void           PlayerDiscard(void);
    void           PlayerDraw(void);
    void           CpuDiscard(void);
    void           CpuDraw(void);

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

#endif // EXCHANGEPHASE_H
