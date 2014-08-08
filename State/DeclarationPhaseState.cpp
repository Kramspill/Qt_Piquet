#include "DeclarationPhaseState.h"

// Constructor.
DeclarationPhaseState::DeclarationPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
DeclarationPhaseState::DeclarationPhaseState(DeclarationPhaseState& other) :
    QState(other)
{
}

// Destructor.
DeclarationPhaseState::~DeclarationPhaseState(void)
{
}

void DeclarationPhaseState::onEntry(QEvent*)
{

}

void DeclarationPhaseState::onExit(QEvent*)
{

}
