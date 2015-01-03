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
#include "State/GlobalStateInfo.h"
#include "Cards/CardArray.h"
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: ScoreManager
//------------------------------------------------------------------------------
class ScoreManager : public QObject
{
    Q_OBJECT
public:
    ScoreManager(void);
    ScoreManager(ScoreManager&);
    ~ScoreManager(void);

    void      Initialize(void);

    void      CreateDeclaration(std::vector<Card*> cards, State phase);
    void      CreateResponse(std::vector<Card*> cards, State phase);
    void      ScoreDeclaration(State phase, PlayerNum player);
    PlayerNum ScoreTrick(PlayerNum player, Card* leadCard = 0, Card* followCard = 0);

    int       GetPlayerScore(void);
    int       GetCPUScore(void);

private:
    int       GetValue(std::vector<Card*> cards, State phase);
    void      GetDeclaration(std::vector<Card*> cards,
                             State phase,
                             char* destBuf);
    void      GetResponse(std::vector<Card*> cards,
                          State phase,
                          char* destBuf);

signals:
    void      UpdateScores(int, int);
    void      UpdateLog(QString);

private:
    int       playerScore;
    int       cpuScore;
};

#endif // SCOREMANAGER_H
