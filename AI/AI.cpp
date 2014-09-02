//------------------------------------------------------------------------------
// Filename: AI.cpp
// Description: Represents the opponent played by the cpu.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "AI.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
AI::AI(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
AI::AI(AI&) :
    QObject()
{

}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
AI::~AI(void)
{

}


//------------------------------------------------------------------------------
// Initialize - Initialize itself.
//------------------------------------------------------------------------------
void AI::Initialize(void)
{
    // Initialize the knowledge base.
    knowledgeBase = new KnowledgeBase();
    knowledgeBase->Initialize();

    // Connect signals.
    connect(knowledgeBase,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardArray::CardArrayType)),
            this,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardArray::CardArrayType)));
}


//------------------------------------------------------------------------------
// UpdateKnowledgeBase - Update the status of a card in the knowledge base.
//------------------------------------------------------------------------------
void AI::UpdateKnowledgeBase(Card* card, int index,
                             CardArray::CardArrayType location)
{
    Card::Suit  suit  = card->GetSuit();
    Card::Value value = card->GetValue();

    // Add the information to the knowledge base.
    knowledgeBase->UpdateCard(suit, value, index, location);
}


//------------------------------------------------------------------------------
// UpdateHand - Provide the ai with up-to-date information on it's cards.
//------------------------------------------------------------------------------
void AI::UpdateHand(CardArray* newCpuHand)
{
    cpuHand = newCpuHand;
}


//------------------------------------------------------------------------------
// SelectAIAction - Select the appropriate action to perform.
//------------------------------------------------------------------------------
void AI::SelectAIAction(AI::AIAction action)
{
    switch ( action )
    {
        case DISCARD:
            SelectCardsToDiscard();
            break;

        case POINT:
            DeclarePoint();
            break;

        case SEQUENCE:
            DeclareSequence();
            break;

        case SET:
            DeclareSet();
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// SelectCardsToDiscard - Select cards to discard for the Exchange phase.
//------------------------------------------------------------------------------
void AI::SelectCardsToDiscard(void)
{
    knowledgeBase->FlagDispensableCards(cpuHand);

    emit AIProcessingComplete();
}


//------------------------------------------------------------------------------
// DeclarePoint - Select cards for the Point declaration.
//------------------------------------------------------------------------------
void AI::DeclarePoint(void)
{

}


//------------------------------------------------------------------------------
// DeclareSequence - Select cards for the Sequence declaration.
//------------------------------------------------------------------------------
void AI::DeclareSequence(void)
{

}


//------------------------------------------------------------------------------
// DeclareSet - Select cards for the Set declaration.
//------------------------------------------------------------------------------
void AI::DeclareSet(void)
{

}
