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
#include <QCoreApplication>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"


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

    void           Initialize(void);
    void           Destroy(void);

protected:
    void           onEntry(QEvent*);
    void           onExit(QEvent*);

private:
    void           ConnectSignals(void);

private slots:
    void           ElderDeclarations(void);
    void           ElderTrick(void);
    void           YoungerDeclarations(void);
    void           YoungerTrick(void);

signals:
    void           AnnounceDeclaration(State, PlayerNum);
    void           DeclarationsComplete(void);
    void           PlayTrick(PlayerNum);
    void           TrickComplete(void);
    void           DeclarationPhaseFinished(void);

private:
    QStateMachine* stateMachine;
    QState*        elderDeclarations;
    QState*        elderTrick;
    QState*        youngerDeclarations;
    QState*        youngerTrick;
    QFinalState*   finalState;
};

#endif // DECLARATIONPHASE_H
