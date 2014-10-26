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
    // Acquire the coordinates of the center of the available display.
    QDesktopWidget* desktop = QApplication::desktop();

    int width  = 800;
    int height = 600;
    int xPos   = (desktop->width()  - width)  / 2;
    int yPos   = (desktop->height() - height) / 2;

    // Initialize the scene.
    scene = new Scene(xPos, yPos, width, height);
    scene->Initialize();

    // TEMP -----------------
    QPushButton* button = new QPushButton("Deal");
    scene->addWidget(button);
    button->setGeometry(xPos+500, yPos+300, 75, 23);
    QPushButton* button2 = new QPushButton("Exchange");
    scene->addWidget(button2);
    button2->setGeometry(xPos+500, yPos+277, 75, 23);
    QPushButton* button3 = new QPushButton("Declare");
    scene->addWidget(button3);
    button3->setGeometry(xPos+575, yPos+300, 75, 23);
    QPushButton* button4 = new QPushButton("Sink");
    scene->addWidget(button4);
    button4->setGeometry(xPos+575, yPos+277, 75, 23);
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
                     SIGNAL(TransferComplete(int)),
                     stateManager,
                     SLOT(SignalTransferComplete(int)));

   /* QObject::connect(cardManager,
                     SIGNAL(SignalValidSelection()),
                     stateManager,
                     SIGNAL(SignalValidSelection()));*/

    // Connect the signals from the state manager.
    QObject::connect(stateManager,
                     SIGNAL(RequestDialog(Dialog::DialogType)),
                     scene,
                     SLOT(CreateDialog(Dialog::DialogType)));

    QObject::connect(stateManager,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int, bool)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int, bool)));

    QObject::connect(stateManager,
                     SIGNAL(SetCardsSelectable(bool, int)),
                     cardManager,
                     SLOT(SetCardsSelectable(bool, int)));

    QObject::connect(stateManager,
                     SIGNAL(DeclareSelection(CardArray::SelectionType)),
                     this,
                     SLOT(DeclareSelection(CardArray::SelectionType)));

    QObject::connect(stateManager,
                     SIGNAL(SignalAI(AI::AIAction)),
                     this,
                     SLOT(SelectAIAction(AI::AIAction)));

    QObject::connect(stateManager,
                     SIGNAL(UpdateAI()),
                     this,
                     SLOT(UpdateAI()));

    // Connect the signals from the ai.
    QObject::connect(ai,
                     SIGNAL(AIProcessingComplete()),
                     stateManager,
                     SLOT(AIProcessingComplete()));

    QObject::connect(ai,
                     SIGNAL(SignalCardSelectionsChanged(Card*,
                                                     CardArray::CardArrayType)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*,
                                                CardArray::CardArrayType)));

    // Connect the signals from the scene.
    QObject::connect(scene,
                     SIGNAL(SignalCardSelectionsChanged(Card*)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*)));

    QObject::connect(scene,
                     SIGNAL(ExecuteDeal()),
                     stateManager,
                     SIGNAL(ExecuteDeal()));
}


//------------------------------------------------------------------------------
// RequestCardTransfer - Request a number of cards be transferred to a different
//                       CardArray.
//------------------------------------------------------------------------------
void GameManager::RequestCardTransfer(CardArray::CardArrayType src,
                                      CardArray::CardArrayType dest,
                                      int  numOfCards,
                                      bool transferSelectedCards)
{
    CardArray* source      = cardManager->GetDesiredCardArray(src);
    CardArray* destination = cardManager->GetDesiredCardArray(dest);

    if ( transferSelectedCards )
        cardManager->TransferSelectedCards(source, destination);
    else
        cardManager->TransferCards(source, destination, numOfCards);
}


//------------------------------------------------------------------------------
// DeclareSelection - Check the card selection and inform the younger hand to
//                    respond.
//------------------------------------------------------------------------------
void GameManager::DeclareSelection(CardArray::SelectionType phase)
{
    if ( cardManager->CheckSelection(phase) )
    {
        ScoreManager::PhaseScore userScore;
        ScoreManager::Response   response;

        switch ( phase )
        {
            case CardArray::POINT:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclarePoint(userScore);
                break;

            case CardArray::SEQUENCE:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclareSequence(userScore);
                break;

            case CardArray::SET:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclareSet(userScore);
                break;

            default:
                break;
        }
    }
}


//------------------------------------------------------------------------------
// CallSelectAIAction - Call an action within the ai class.
//------------------------------------------------------------------------------
void GameManager::SelectAIAction(AI::AIAction action)
{
    switch ( action )
    {
        case AI::DISCARD:
            ai->SelectCardsToDiscard();
            break;

        case AI::TRICK:
            break;

        default:
            break;
    }
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
    cardArray = cardManager->GetDesiredCardArray(CardArray::CPUHAND);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUHAND);
    }

    // Provide the ai with a pointer to the cpu's hand.
    ai->UpdateHand(cardArray);

    // Retrieve the cpu's discards and update the ai's knowledge base.
    cardArray = cardManager->GetDesiredCardArray(CardArray::CPUDISCARDS);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUDISCARDS);
    }

    // Retrieve the previous tricks and update the ai's knowledge base.
    cardArray = cardManager->GetDesiredCardArray(CardArray::PREVIOUSTRICKS);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::PREVIOUSTRICKS);
    }
}
