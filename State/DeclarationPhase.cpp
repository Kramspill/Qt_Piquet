#include "DeclarationPhase.h"

// Constructor.
DeclarationPhase::DeclarationPhase(void)
{
}

// Copy Constructor.
DeclarationPhase::DeclarationPhase(DeclarationPhase& other) : Phase(other)
{
}

// Destructor.
DeclarationPhase::~DeclarationPhase(void)
{
}

void DeclarationPhase::Initialize(void)
{

}

// Execute the phase.
void DeclarationPhase::Execute(void)
{

}

// Accessor for DeclarationPhase's name member.
char* DeclarationPhase::GetName(void)
{
    return name;
}
