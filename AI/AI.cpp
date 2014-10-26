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

    // Connect the signals.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// UpdateKnowledgeBase - Update the status of a card in the knowledge base.
//------------------------------------------------------------------------------
void AI::UpdateKnowledgeBase(Card* card, int index,
                             CardLayout::Type location)
{
    Card::Suit  suit  = card->GetSuit();
    Card::Rank rank = card->GetRank();

    // Add the information to the knowledge base.
    knowledgeBase->UpdateCard(suit, rank, index, location);
}


//------------------------------------------------------------------------------
// UpdateHand - Provide the ai with up-to-date information on it's cards.
//------------------------------------------------------------------------------
void AI::UpdateHand(CardLayout* newCpuHand)
{
    cpuHand = newCpuHand;
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
ScoreManager::Response AI::DeclarePoint(ScoreManager::PhaseScore userScore)
{
    if ( /*elderHand*/ 0 )
    {

    }
    else
    {
        ScoreManager::PhaseScore score = knowledgeBase->CalculatePoint();
    }
}


//------------------------------------------------------------------------------
// DeclareSequence - Select cards for the Sequence declaration.
//------------------------------------------------------------------------------
ScoreManager::Response AI::DeclareSequence(ScoreManager::PhaseScore userScore)
{
    if ( /*elderHand*/ 0 )
    {

    }
    else
    {
        ScoreManager::PhaseScore score = knowledgeBase->CalculateSequence();
    }
}


//------------------------------------------------------------------------------
// DeclareSet - Select cards for the Set declaration.
//------------------------------------------------------------------------------
ScoreManager::Response AI::DeclareSet(ScoreManager::PhaseScore userScore)
{
    if ( /*elderHand*/ 0 )
    {

    }
    else
    {
        ScoreManager::PhaseScore score = knowledgeBase->CalculateSet();
    }
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void AI::ConnectSignals(void)
{
    connect(knowledgeBase,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardLayout::Type)),
            this,
            SIGNAL(SignalCardSelectionsChanged(Card*,
                                               CardLayout::Type)));
}
