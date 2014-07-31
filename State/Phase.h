#ifndef PHASE_H
#define PHASE_H

#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QTimer>

class Phase
{
public:
    Phase(void);
    Phase(Phase&);
    ~Phase(void);

    void Initialize(void);
    void Execute(void);

    char* GetName(void);

private:
    char* name;
};

#endif // PHASE_H
