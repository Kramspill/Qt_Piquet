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

    char* GetName(void);
    void  Execute(void);

private:
    char* name;
};

#endif // PHASE_H
