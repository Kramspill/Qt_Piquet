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
GameManager::GameManager(GameManager&) :
    QObject()
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

    // Initialize the AI.
    ai = new AI();
    ai->Initialize();

    // Initialize the StateManager.
    stateManager = new StateManager();
    stateManager->Initialize(button, button2, button3, button4);

    // Initialize the ScoreManager.
    scoreManager = new ScoreManager();
    scoreManager->Initialize();

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
    QObject::connect(cardManager,
                     SIGNAL(SignalValidSelection()),
                     stateManager,
                     SIGNAL(SignalValidSelection()));

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
                     SIGNAL(SignalCheckSelection(CardArray::SelectionType)),
                     cardManager,
                     SLOT(CallCheckSelection(CardArray::SelectionType)));
    QObject::connect(stateManager,
                     SIGNAL(SignalAI(AI::AIAction)),
                     ai,
                     SLOT(SelectAIAction(AI::AIAction)));

    // Connect the signals from the scene.
    QObject::connect(scene,
                     SIGNAL(SignalCardSelectionsChanged(Card*)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*)));
}


//------------------------------------------------------------------------------
// UpdateAI - Update the game's ai with current knowledge.
//------------------------------------------------------------------------------
void GameManager::UpdateAI(void)
{
    Card*      card;
    CardArray* cardArray;
    int        size = 0;

    // Retrieve the cpu's hand and update the ai's knowledge base.
    cardArray = cardManager->GetCpuHand();
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUHAND);
    }

    // Provide the ai with a pointer to the cpu's hand.
    ai->UpdateHand(cardArray);

    // Retrieve the cpu's discards and update the ai's knowledge base.
    cardArray = cardManager->GetCpuDiscards();
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUDISCARDS);
    }

    // Retrieve the previous tricks and update the ai's knowledge base.
    cardArray = cardManager->GetPreviousTricks();
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::PREVIOUSTRICKS);
    }
}
