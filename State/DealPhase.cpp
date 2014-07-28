#include "DealPhase.h"

// Constructor.
DealPhase::DealPhase(void)
{
}

// Copy Constructor.
DealPhase::DealPhase(DealPhase& other) : Phase(other)
{
}

// Destructor.
DealPhase::~DealPhase(void)
{
}

// Accessor for DealPhase's name member.
char* DealPhase::GetName(void)
{
    return name;
}

// Execute the phase.
void DealPhase::Execute(void)
{

}
