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

    // TEMP -----------------
    QPushButton* button = new QPushButton("Deal");
    scene->addWidget(button);
    QPushButton* button2 = new QPushButton("Exchange");
    scene->addWidget(button2);
    button2->setGeometry(0, -30, 75, 23);
    QPushButton* button3 = new QPushButton("Declare");
    scene->addWidget(button3);
    button3->setGeometry(75, -30, 75, 23);
    QPushButton* button4 = new QPushButton("Sink");
    scene->addWidget(button4);
    button4->setGeometry(75, 0, 75, 23);
    //-----------------------

    // Initialize the CardManager with the scene object.
    cardManager = new CardManager();
    cardManager->Initialize(scene);

    // Initialize the StateManager.
    stateManager = new StateManager();
    stateManager->Initialize(button, button2, button3, button4);

    /*
    // Initialize the ScoreManager.
    scoreManager = new ScoreManager();
    scoreManager->Initialize();
    */

    // Initialize the view and display it.
    view = new View(scene);
    view->show();

    // Connect the various signals to their managers.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to their managers.
//------------------------------------------------------------------------------
void GameManager::ConnectSignals(void)
{
    // Connect the signals from the card manager.
    QObject::connect(cardManager,
                     SIGNAL(SignalTransferComplete()),
                     stateManager,
                     SIGNAL(SignalTransferComplete()));
    QObject::connect(cardManager,
                     SIGNAL(SignalNumOfCardsTransferred(int)),
                     stateManager,
                     SIGNAL(SignalNumOfCardsTransferred(int)));

    // Connect the signals from the state manager.
    QObject::connect(stateManager,
                     SIGNAL(SignalCardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               int)),
                     cardManager,
                     SLOT(CallTransferCards(CardArray::CardArrayType,
                                            CardArray::CardArrayType,
                                            int)));
    QObject::connect(stateManager,
                     SIGNAL(SignalTransferSelectedCards(
                                CardArray::CardArrayType,
                                CardArray::CardArrayType)),
                     cardManager,
                     SLOT(CallTransferSelectedCards(
                              CardArray::CardArrayType,
                              CardArray::CardArrayType)));
    QObject::connect(stateManager,
                     SIGNAL(SignalSetCardsSelectable(bool, int)),
                     cardManager,
                     SLOT(SetCardsSelectable(bool, int)));
    QObject::connect(stateManager,
                     SIGNAL(SignalCheckPoint()),
                     scoreManager,
                     SLOT(CheckPoint()));
    QObject::connect(stateManager,
                     SIGNAL(SignalCheckSequence()),
                     scoreManager,
                     SLOT(CheckSequence()));
    QObject::connect(stateManager,
                     SIGNAL(SignalCheckSet()),
                     scoreManager,
                     SLOT(CheckSet()));

    // Connect the signals from the scene.
    QObject::connect(scene,
                     SIGNAL(SignalCardSelectionsChanged(Card*)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*)));
}
