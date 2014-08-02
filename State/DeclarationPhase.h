#ifndef DECLARATIONPHASE_H
#define DECLARATIONPHASE_H

#include "Phase.h"

class DeclarationPhase : public Phase
{
public:
    DeclarationPhase(void);
    DeclarationPhase(DeclarationPhase& other);
    ~DeclarationPhase(void);

    void Initialize(void);
    void Execute(void);

    char* GetName(void);

private:
    char* name;
};

#endif // DECLARATIONPHASE_H
