#ifndef DECLARATIONPHASESTATE_H
#define DECLARATIONPHASESTATE_H

#include <QState>
#include <QEvent>

class DeclarationPhaseState : public QState
{
public:
    DeclarationPhaseState(QState* parent = 0);
    DeclarationPhaseState(DeclarationPhaseState& other);
    ~DeclarationPhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // DECLARATIONPHASESTATE_H
