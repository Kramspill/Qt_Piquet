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
// Class: ScoreManager
//------------------------------------------------------------------------------
class ScoreManager : public QObject
{
    Q_OBJECT
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
