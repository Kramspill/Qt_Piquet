#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

class ScoreManager
{
public:
    ScoreManager(void);
    ScoreManager(ScoreManager&);
    ~ScoreManager(void);

    void Initialize(void);

    unsigned int GetPlayerScore(void);
    unsigned int GetCPUScore(void);

private:
    unsigned int playerScore;
    unsigned int cpuScore;
};

#endif // SCOREMANAGER_H
