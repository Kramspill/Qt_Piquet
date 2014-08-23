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

private:
    void SelectCardsToDiscard(void);
    void DeclarePoint(void);
    void DeclareSequence(void);
    void DeclareSet(void);

public slots:
    void SelectAIAction(AIAction action);
};

#endif // AI_H
