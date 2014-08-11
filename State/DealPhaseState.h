#ifndef DEALPHASESTATE_H
#define DEALPHASESTATE_H

#include <QState>
#include <QFinalState>
#include <QEvent>
#include <QStateMachine>
#include <QPushButton>

#include "Managers/CardManager.h"
#include "Cards/CardArray.h"

class DealPhaseState : public QState
{
    Q_OBJECT
public:
    DealPhaseState(QState* parent = 0);
    DealPhaseState(DealPhaseState&);
    ~DealPhaseState(void);

    void Initialize(QPushButton* button);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);

signals:
    void DealPhaseFinished(void);

private slots:
    void DealToPlayer(void);
    void DealToCpu(void);
    void DealTalon(void);

private:
    QStateMachine* stateMachine;
};

#endif // DEALPHASESTATE_H
