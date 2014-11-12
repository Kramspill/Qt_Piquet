//------------------------------------------------------------------------------
// Filename: AI.h
// Description: Header file for AI.
//------------------------------------------------------------------------------

#ifndef AI_H
#define AI_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Managers/ScoreManager.h"
#include "Cards/CardArray.h"
#include "KnowledgeBase.h"


//------------------------------------------------------------------------------
// Class: AI
//------------------------------------------------------------------------------
class AI : public QObject
{
    Q_OBJECT
public:
    enum AIAction
    {
        DISCARD,
        TRICK
    };

public:
    AI(void);
    AI(AI&);
    ~AI(void);

    void                   Initialize(void);

    void                   UpdateKnowledgeBase(Card* card, int index,
                                             CardArray::CardArrayType location);
    void                   UpdateHand(CardArray* newCpuHand);

    void                   SelectCardsToDiscard(void);
    ScoreManager::Response DeclarePoint(ScoreManager::PhaseScore userScore);
    ScoreManager::Response DeclareSequence(ScoreManager::PhaseScore userScore);
    ScoreManager::Response DeclareSet(ScoreManager::PhaseScore userScore);

private:
    void                   ConnectSignals(void);

signals:
    void                   SignalCardSelectionsChanged(Card*,
                                                      CardArray::CardArrayType);
    void                   AIProcessingComplete(void);

    void                   GoodResponse(void);
    void                   NotGoodResponse(void);
    void                   HowHighWinResponse(void);
    void                   HowHighLossResponse(void);
    void                   HowHighEvenResponse(void);

private:
    KnowledgeBase*         knowledgeBase;
    CardArray*             cpuHand;
};

#endif // AI_H
