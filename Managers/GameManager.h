#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include "WindowManager.h"
#include "StateManager.h"
#include "AnimationManager.h"
#include "CardManager.h"
#include "ScoreManager.h"

class GameManager
{
public:
    GameManager(void);
    GameManager(GameManager&);
    ~GameManager(void);

    void Initialize(void);

    StateManager*     GetStateManager(void);
    AnimationManager* GetAnimationManager(void);
    CardManager*      GetCardManager(void);
    ScoreManager*     GetScoreManager(void);

private:
    QGraphicsScene*   scene;
    QGraphicsView*    view;
    WindowManager*    windowManager;
    StateManager*     stateManager;
    AnimationManager* animationManager;
    CardManager*      cardManager;
    ScoreManager*     scoreManager;
};

#endif // GAMEMANAGER_H
