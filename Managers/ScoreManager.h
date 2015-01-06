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
    void      Reset(void);

    void      CreateDeclaration(State phase, std::vector<Card*> cards);
    void      CreateResponse(   State phase, std::vector<Card*> cards);
    void      ScoreDeclaration( State phase, PlayerNum player);
    PlayerNum ScoreTrick(PlayerNum player,
                         Card*     leadCard = 0,
                         Card*     followCard = 0);

    int       GetPlayerScore(void);
    int       GetCPUScore(void);

private:
    int       GetValue(      State phase, std::vector<Card*> cards);
    void      GetDeclaration(State phase, int numCards);
    void      GetResponse(   State phase, int value);

public slots:
    void      ScoreCarteBlanche(void);

signals:
    void      UpdateScores(int, int);
    void      UpdateLog(QString);

private:
    int       playerScore;
    int       cpuScore;
};

#endif // SCOREMANAGER_H
