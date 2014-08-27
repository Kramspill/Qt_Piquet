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
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Class: AI
//------------------------------------------------------------------------------
class AI : public QObject
{
    Q_OBJECT
public:
    enum AIAction
    {
        UPDATE,
        DISCARD,
        POINT,
        SEQUENCE,
        SET
    };

    struct KnowledgeItem
    {
        CardArray::CardArrayType location;
        int index;
        int rank;
    };

public:
    AI(void);
    AI(AI&);
    ~AI(void);

    void           Initialize(void);

    void           UpdateKnowledgeBase(Card* card, int index,
                                       CardArray::CardArrayType location);
    void           UpdateHand(CardArray* newCpuHand);
    void           SelectAIAction(AIAction action);

private:
    void           SelectCardsToDiscard(void);
    void           RankCards(void);
    void           CalculateSuitValues(void);
    void           RankStoppers(void);
    void           RankSets(void);
    void           RankSequences(void);
    void           FinishRanking(void);

    void           DeclarePoint(void);
    void           DeclareSequence(void);
    void           DeclareSet(void);

signals:
    void           SignalCardSelectionsChanged(Card*, CardArray::CardArrayType);
    void           AIProcessingComplete(void);

private:
    KnowledgeItem* knowledgeBase[4][8];
    CardArray*     cpuHand;
    int            cardRanks[12];
    int            currentRank;
    int            suitValues[4];
    int            suitRanks[4];
    int            pointValues[8];
};

#endif // AI_H
