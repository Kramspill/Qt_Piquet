//------------------------------------------------------------------------------
// Filename: GameManager.cpp
// Description: Manages the other managers in the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "GameManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
GameManager::GameManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
GameManager::GameManager(GameManager&)
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
GameManager::~GameManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize all the other managers and display the scene.
//------------------------------------------------------------------------------
void GameManager::Initialize(void)
{
    // Initialize the scene.
    scene = new Scene(-350, -350, 700, 700);

    // TEMP
    QPushButton* button = new QPushButton();
    scene->addWidget(button);
    QPushButton* button2 = new QPushButton();
    scene->addWidget(button2);
    button2->setGeometry(0, -50, 50, 50);
    //

    // Initialize the CardManager with the scene object.
    cardManager = new CardManager();
    cardManager->Initialize(scene);

    // Initialize the StateManager.
    stateManager = new StateManager();
    stateManager->Initialize(button, button2);

    /* Progressively add these.

    // Initialize the ScoreManager.
    scoreManager = new ScoreManager();
    scoreManager->Initialize();

    // Initialize the WindowManager.
    windowManager = new WindowManager();
    windowManager->Initialize();

    */

    // Initialize the view and display it.
    view = new View(scene);
    view->show();

    // Connect the various signals to their managers.
    QObject::connect(stateManager->GetDealPhaseState(),
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     cardManager,
                     SLOT(CallTransferCards(CardArray::CardArrayType,
                                            CardArray::CardArrayType,
                                            int)));
    QObject::connect(stateManager->GetExchangePhaseState(),
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     cardManager,
                     SLOT(CallTransferCards(CardArray::CardArrayType,
                                            CardArray::CardArrayType,
                                            int)));
    QObject::connect(stateManager->GetExchangePhaseState(),
                     SIGNAL(RequestSelectedCardsTransfer(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)),
                     cardManager,
                     SLOT(CallTransferSelectedCards(
                              CardArray::CardArrayType,
                              CardArray::CardArrayType)));
    QObject::connect(stateManager->GetExchangePhaseState(),
                     SIGNAL(SignalEnableCardSelection()),
                     cardManager,
                     SLOT(EnableCardSelection()));
    QObject::connect(stateManager->GetExchangePhaseState(),
                     SIGNAL(SignalDisableCardSelection()),
                     cardManager,
                     SLOT(DisableCardSelection()));
    QObject::connect(scene,
                     SIGNAL(SignalCardSelectionsChanged(Card*)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*)));
}
