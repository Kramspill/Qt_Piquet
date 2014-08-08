#ifndef EXCHANGEPHASESTATE_H
#define EXCHANGEPHASESTATE_H

#include <QState>
#include <QEvent>

class ExchangePhaseState : public QState
{
public:
    ExchangePhaseState(QState* parent = 0);
    ExchangePhaseState(ExchangePhaseState& other);
    ~ExchangePhaseState(void);

protected:
    void onEntry(QEvent*);
    void onExit(QEvent*);
};

#endif // EXCHANGEPHASESTATE_H
