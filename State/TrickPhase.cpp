#include "TrickPhase.h"

// Constructor.
TrickPhase::TrickPhase(void)
{
}

// Copy Constructor.
TrickPhase::TrickPhase(TrickPhase& other) : Phase(other)
{
}

// Destructor.
TrickPhase::~TrickPhase(void)
{
}

void TrickPhase::Initialize(void)
{

}

// Execute the phase.
void TrickPhase::Execute(void)
{

}

// Accessor for TrickPhase's name member.
char* TrickPhase::GetName(void)
{
    return name;
}
