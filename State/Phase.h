#ifndef PHASE_H
#define PHASE_H

#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QTimer>

class Phase
{
public:
    virtual ~Phase(void) = 0;

    virtual void Initialize(void) = 0;
    virtual void Execute(void) = 0;

    virtual char* GetName(void) = 0;

protected:
    Phase(void);
    Phase(Phase&);

private:
    char* name;
};

#endif // PHASE_H
