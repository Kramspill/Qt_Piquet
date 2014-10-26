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

    void           Initialize(QPushButton* button, QPushButton* button2);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ConnectSignals(void);

public slots:
    void           ValidSelection(void);

private slots:
    void           PlayerPoint(void);
    void           PlayerSequence(void);
    void           PlayerSet(void);
    void           CpuPoint(void);
    void           CpuSequence(void);
    void           CpuSet(void);
    void           InitialTrick(void);

signals:
    void           SetCardsSelectable(bool, int);
    void           DeclareSelection(CardArray::SelectionType);
    void           SignalValidSelection(void);
    void           DeclarationPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        playerPoint;
    QState*        playerSequence;
    QState*        playerSet;
    QState*        cpuPoint;
    QState*        cpuSequence;
    QState*        cpuSet;
    QState*        initialTrick;
    QFinalState*   finalState;
    PhaseOutcome   phaseStatus[3];
    QPushButton*   declareButton;
};

#endif // DECLARATIONPHASE_H
