#ifndef DECLARATIONPHASE_H
#define DECLARATIONPHASE_H

#include "Phase.h"

class DeclarationPhase : public Phase
{
public:
    DeclarationPhase(void);
    DeclarationPhase(DeclarationPhase&);
    ~DeclarationPhase(void);

    char* GetName(void);
    void  Execute(void);

private:
    char* name;
};

#endif // DECLARATIONPHASE_H
