#ifndef DEALPHASESTATE_H
#define DEALPHASESTATE_H

#include <QState>
#include <QEvent>

class DealPhaseState : public QState
{
public:
    DealPhaseState(QState* parent = 0);
    DealPhaseState(DealPhaseState& other);
    ~DealPhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // DEALPHASESTATE_H
