//------------------------------------------------------------------------------
// Filename: KnowledgeBase.h
// Description: Header file for KnowledgeBase.
//------------------------------------------------------------------------------

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Managers/ScoreManager.h"
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Class: KnowledgeBase
//------------------------------------------------------------------------------
class KnowledgeBase : public QObject
{
    Q_OBJECT
public:
    struct KnowledgeItem
    {
        CardArray::Type location;
        int  index;
        int  rank;
        bool selected;
    };

public:
    KnowledgeBase(void);
    KnowledgeBase(KnowledgeBase&);
    ~KnowledgeBase(void);

    void                     Initialize(void);
    void                     Destroy(void);
    void                     UpdateCard(Card::Suit suit, Card::Rank rank,
                                        int index,
                                        CardArray::Type location);
    void                     FlagDispensableCards(CardArray* cpuHand);
    void                     SelectTrick(CardArray* cpuHand);

    void                     SelectPoint(CardArray* hand);
    void                     SelectSequence(CardArray* hand);
    void                     SelectSet(CardArray* hand);

private:
    void                     RankCards(CardArray* cpuHand);
    void                     CalculateSuitValues(CardArray* cpuHand);
    void                     RankStoppers(void);
    void                     RankSets(void);
    void                     RankSequences(void);
    void                     FinishRanking(void);

private:
    KnowledgeItem*           cardStatus[4][8];
    int                      cardRanks[12];
    int                      currentRank;
    int                      suitValues[4];
    int                      suitRanks[4];
    int                      pointValues[8];
};

#endif // KNOWLEDGEBASE_H
