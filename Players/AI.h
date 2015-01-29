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
#include "Player.h"


//------------------------------------------------------------------------------
// Class: AI
//------------------------------------------------------------------------------
class AI : public Player
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

    void                   Initialize(PlayerNum num);
    void                   Destroy(void);
    void                   Reset(void);

    void                   ExecuteDeal(void);
    void                   ExecuteExchange(void);
    void                   AnnounceDeclaration(State phase);
    void                   Respond(State phase);
    void                   PlayTrick(void);
    void                   CarteBlanche(void);


    void                   UpdateKnowledgeBase(Card* card, int index,
                                             CardArray::Type location);
    void                   UpdateHand(CardArray* newCpuHand);

    void                   SelectCardsToDiscard(void);
    void                   SelectTrickToPlay(void);

protected:
    void                   ExecuteCarteBlanche(void);

private:
    void                   ConnectSignals(void);

signals:
    void                   RequestCardPositions(PlayerNum player);

private:
    KnowledgeBase*         knowledgeBase;
    CardArray*             cpuHand;
};

#endif // AI_H
