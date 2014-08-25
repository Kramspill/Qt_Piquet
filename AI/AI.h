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

public:
    AI(void);
    AI(AI&);
    ~AI(void);

    void Initialize(void);

    void UpdateKnowledgeBase(Card* card, CardArray::CardArrayType location);

private:
    void SelectCardsToDiscard(void);
    void RankCards(void);
    void CalculateSuitValues(void);
    void RankStoppers(void);
    void RankSets(void);
    void RankSequences(void);
    void FinishRanking(void);

    void DeclarePoint(void);
    void DeclareSequence(void);
    void DeclareSet(void);

public slots:
    void SelectAIAction(AIAction action);

private:
    int  knowledgeBase[4][8];
    int  cardRanks[12];
    int  suitValues[4];
    int  pointValues[8];
};

#endif // AI_H
