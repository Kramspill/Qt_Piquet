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
    DeclarationPhase(QState* parent = 0);
    DeclarationPhase(DeclarationPhase&);
    ~DeclarationPhase(void);

    void           Initialize(QPushButton* button, QPushButton* button2);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private slots:
    void           PlayerPoint(void);
    void           PlayerSequence(void);
    void           PlayerSet(void);
    void           CpuPoint(void);
    void           CpuSequence(void);
    void           CpuSet(void);
    void           InitialTrick(void);

    void           CheckPoint(void);

signals:
    void           RequestCardsSelectable(bool, int);
    void           RequestCheckPoint(void);
    void           RequestCheckSequence(void);
    void           RequestCheckSet(void);
    void           DeclarationPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QPushButton*   declareButton;
};

#endif // DECLARATIONPHASE_H
