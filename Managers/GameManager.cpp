#include "GameManager.h"

// Constructor.
GameManager::GameManager(void)
{
}

// Copy Constructor.
GameManager::GameManager(GameManager&)
{
}

// Destructor.
GameManager::~GameManager(void)
{
}

// Initialize all other managers.
void GameManager::Initialize(void)
{
    // Initialize the scene.
    scene = new Scene(-350, -350, 700, 700);

    // TEMP
    QPushButton* button = new QPushButton();
    scene->addWidget(button);
    //

    // Initialize the CardManager with the scene object.
    CardManager::GetSingleton().Initialize(scene);

    // Initialize the StateManager with the Cards.
    StateManager::GetSingleton().Initialize(button);

    //stateManager->GetDealPhase()->Execute();

    view = new View(scene);
    view->show();

    //stateManager->GetDealPhase()->Execute();

    /* Progressively add these.
    windowManager = new WindowManager();
    windowManager->Initialize();

    stateManager = new StateManager();
    stateManager->Initialize();

    cardManager = new CardManager();
    cardManager->Initialize();

    scoreManager = new ScoreManager();
    scoreManager->Initialize();
    */
}

// Accessor for GameManager's scoreManager member.
ScoreManager* GameManager::GetScoreManager(void)
{
    return scoreManager;
}
