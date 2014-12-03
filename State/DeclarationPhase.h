//------------------------------------------------------------------------------
// Filename: DeclarationPhase.h
// Description: Header file for DeclarationPhase.
//------------------------------------------------------------------------------

#ifndef DECLARATIONPHASE_H
#define DECLARATIONPHASE_H

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
#include "Scene/Scene.h"
#include "AI/AI.h"


//------------------------------------------------------------------------------
// Class: DeclarationPhase
//------------------------------------------------------------------------------
class DeclarationPhase : public QState
{
    Q_OBJECT
public:
    enum PhaseOutcome
    {
        PENDING,
        PLAYERWIN,
        CPUWIN,
        DRAW
    };

public:
    DeclarationPhase(QState* parent = 0);
    DeclarationPhase(DeclarationPhase&);
    ~DeclarationPhase(void);

    void           Initialize(void);

    void           PhaseComplete(void);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ConnectSignals(void);

private slots:
    void           PlayerPoint(void);
    void           PlayerSequence(void);
    void           PlayerSet(void);
    void           PlayerInitialTrick(void);
    void           ExitPlayerInitialTrick(void);
    void           CpuPoint(void);
    void           CpuSequence(void);
    void           CpuSet(void);
    void           CpuInitialTrick(void);

signals:
    void           RequestCardTransfer(CardArray::CardArrayType,
                                       CardArray::CardArrayType,
                                       int, bool);
    void           SetCardsSelectable(bool, int);
    void           SetCardsMoveable(bool);
    void           SignalAI(AI::AIAction);
    void           SetUI(Scene::PhaseType);
    void           UpdateAI(void);
    void           DeclareSelection(CardArray::SelectionType);
    void           DeclarationPhaseFinished(void);

    void           TransferComplete(void);
    void           PointComplete(void);
    void           SequenceComplete(void);
    void           SetComplete(void);
    void           NoLosses(void);
    void           Losses(void);

private:
    QStateMachine* stateMachine;
    QState*        playerPoint;
    QState*        playerSequence;
    QState*        playerSet;
    QState*        cpuPoint;
    QState*        cpuSequence;
    QState*        cpuSet;
    QState*        playerInitialTrick;
    QState*        cpuInitialTrick;
    QFinalState*   finalState;
    PhaseOutcome   phaseStatus[3];
};

#endif // DECLARATIONPHASE_H
