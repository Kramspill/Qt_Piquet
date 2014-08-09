#include "DeclarationPhaseState.h"

// Constructor.
DeclarationPhaseState::DeclarationPhaseState(QState* parent) :
    QState(parent)
{
}

// Copy Constructor.
DeclarationPhaseState::DeclarationPhaseState(DeclarationPhaseState&) :
    QState()
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
