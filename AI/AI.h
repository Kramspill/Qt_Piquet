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

    void           Initialize(void);

    void           UpdateKnowledgeBase(Card* card, int index,
                                       CardArray::CardArrayType location);
    void           UpdateHand(CardArray* newCpuHand);
    void           SelectAIAction(AIAction action);

private:
    void           SelectCardsToDiscard(void);
    void           DeclarePoint(void);
    void           DeclareSequence(void);
    void           DeclareSet(void);

signals:
    void           SignalCardSelectionsChanged(Card*, CardArray::CardArrayType);
    void           AIProcessingComplete(void);

private:
    KnowledgeBase* knowledgeBase;
    CardArray*     cpuHand;
};

#endif // AI_H
