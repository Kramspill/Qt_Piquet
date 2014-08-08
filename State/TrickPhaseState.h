#ifndef TRICKPHASESTATE_H
#define TRICKPHASESTATE_H

#include <QState>
#include <QEvent>

class TrickPhaseState : public QState
{
public:
    TrickPhaseState(QState* parent = 0);
    TrickPhaseState(TrickPhaseState& other);
    ~TrickPhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // TRICKPHASESTATE_H
