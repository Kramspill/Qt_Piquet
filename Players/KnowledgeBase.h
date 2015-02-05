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
#include "State/GlobalStateInfo.h"
#include "Managers/ScoreManager.h"
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Variables/Constants
//------------------------------------------------------------------------------
const int DEPTH = 4;


//------------------------------------------------------------------------------
// Class: KnowledgeBase
//------------------------------------------------------------------------------
class KnowledgeBase : public QObject
{
    Q_OBJECT
public:
    struct Node
    {
        int                payoff;
        bool               myTurnNext;
        std::vector<Node*> children;
        CardArray::Type**  state;
        bool               piquetGiven;
        int                myWins;
        int                oppWins;
        int                myScore;
        int                oppScore;
    };

    struct KnowledgeItem
    {
        CardArray::Type location;
        int             index;
        int             rank;
        bool            selected;
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
    void                     SelectMMTrick(CardArray* cpuHand, PlayerNum n);

    void                     SelectPoint(CardArray* hand);
    void                     SelectSequence(CardArray* hand);
    void                     SelectSet(CardArray* hand);
    void                     SetScores(int myScore, int oppScore);

private:
    void                     RankCards(CardArray* cpuHand);
    void                     CalculateSuitValues(CardArray* cpuHand);
    void                     RankStoppers(void);
    void                     RankSets(void);
    void                     RankSequences(void);
    void                     FinishRanking(void);
    int                      ImpMinimax(Node* n, int depth, bool myMove, PlayerNum p);
    void                     GenerateMoves(Node* parent, PlayerNum p);
    void                     FreeTree(Node* root);

private:
    KnowledgeItem*           cardStatus[4][8];
    int                      cardRanks[12];
    int                      currentRank;
    int                      suitValues[4];
    int                      suitRanks[4];
    int                      pointValues[8];
    int                      myScore;
    int                      oppScore;
};

#endif // KNOWLEDGEBASE_H
