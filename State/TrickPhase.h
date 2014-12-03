//------------------------------------------------------------------------------
// Filename: TrickPhase.h
// Description: Header file for TrickPhase.
//------------------------------------------------------------------------------

#ifndef TRICKPHASE_H
#define TRICKPHASE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>
#include <QFinalState>
#include <QStateMachine>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"
#include "AI/AI.h"


//------------------------------------------------------------------------------
// Class: TrickPhase
//------------------------------------------------------------------------------
class TrickPhase : public QState
{
    Q_OBJECT
public:
    TrickPhase(QState* parent = 0);
    TrickPhase(TrickPhase&);
    ~TrickPhase(void);

    void           Initialize(void);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ConnectSignals(void);

public slots:
    void           PlayerMoveFinished(int numOfCardsTransferred);

private slots:
    void           ScoreTrick(void);
    void           PlayerTrick(void);
    void           ExitPlayerTrick(void);
    void           CpuTrick(void);

    void           TrickResult(bool winningPlayer);

signals:
    void           TrickPhaseFinished(void);
    void           UpdateAI(void);
    void           SignalAI(AI::AIAction);
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType,
                                       int, bool);
    void           TransferComplete(void);
    void           SetCardsMoveable(bool);
    void           CheckTrick(bool);

    void           PlayersTurn(void);
    void           CpusTurn(void);

private:
    QStateMachine* stateMachine;
    QState*        playerTrick;
    QState*        cpuTrick;
    QState*        scoreTrick;
    bool           player;
};

#endif // TRICKPHASE_H
