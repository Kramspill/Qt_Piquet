#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QPushButton>

#include "Scene/Scene.h"
#include "View/View.h"
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

    ScoreManager* GetScoreManager(void);

private:
    Scene*            scene;
    View*             view;
    WindowManager*    windowManager;
    ScoreManager*     scoreManager;
};

#endif // GAMEMANAGER_H
