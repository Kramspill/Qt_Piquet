//------------------------------------------------------------------------------
// Filename: ScoreManager.h
// Description: Header file for ScoreManager.
//------------------------------------------------------------------------------

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: ScoreManager
//------------------------------------------------------------------------------
class ScoreManager : public QObject
{
    Q_OBJECT
public:
    enum Response
    {
        GOOD,
        NOTGOOD,
        EVEN,
        QUESTION
    };

    enum SequenceScoring
    {
        THREE = 3,
        FOUR  = 4,
        FIVE  = 15,
        SIX   = 16,
        SEVEN = 17,
        EIGHT = 18
    };

    struct PhaseScore
    {
        int numOfCards;
        int totalValue;
    };

public:
    ScoreManager(void);
    ScoreManager(ScoreManager&);
    ~ScoreManager(void);

    void Initialize(void);

    int  GetPlayerScore(void);
    int  GetCPUScore(void);

public slots:
    void CheckPoint(void);
    void CheckSequence(void);
    void CheckSet(void);

private:
    int  playerScore;
    int  cpuScore;
};

#endif // SCOREMANAGER_H
