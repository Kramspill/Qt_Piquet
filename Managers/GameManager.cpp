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
    // Initialize the LayoutManager.
    //layoutManager = new LayoutManager();
    //layoutManager->Initialize();

    // Initialize the top-level widget that will house everything else within
    // the graphics scene.
    //widget = new QGraphicsWidget();
    //widget->setLayout(LayoutManager->GetMainLayout());

    //scene->addItem(widget);

    // TEMP -----------------
    /*QPushButton* button = new QPushButton("Deal");
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
*/
    //= Dialog Test =//
    /*Dialog* dialog = new Dialog();
    Dialog::ButtonType buttonType = Dialog::DEAL;
    dialog->Initialize("Title", "This is a message", 1, &buttonType);
    dialog->exec();*/
    //===============//
    /*Card* a = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* b = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* c = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* d = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* e = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* f = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* g = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);
    Card* h = new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                       Card::CLUBS, Card::SEVEN);

    QGraphicsGridLayout* layout = new QGraphicsGridLayout();

    layout->setSpacing(0);

    layout->addItem(a, 0, 0);
    layout->addItem(b, 0, 1);
    layout->addItem(c, 0, 2);
    layout->addItem(d, 1, 0);
    layout->addItem(e, 1, 1);
    layout->addItem(f, 1, 2);
    layout->addItem(g, 2, 0);
    layout->addItem(h, 2, 1);*/
    /*QGraphicsLinearLayout* layout = new QGraphicsLinearLayout();
    layout->addItem(a);
    layout->addItem(b);
    layout->addItem(c);*/

    //-----------------------

    // Initialize the scene.
    scene = new Scene();
    scene->Initialize();

    // Initialize the CardManager with the scene object.
    cardManager = new CardManager();
    cardManager->Initialize(scene);

    // Initialize the AI.
    ai = new AI();
    ai->Initialize();

    // Initialize the StateManager.
    stateManager = new StateManager();
    stateManager->Initialize();

    // Initialize the ScoreManager.
    scoreManager = new ScoreManager();
    scoreManager->Initialize();

    // Initialize the view and display it.
    view = new View(scene);
    //view->resize(600, 600);
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
                     SIGNAL(RequestCardTransfer(CardLayout::Type,
                                                CardLayout::Type,
                                                int, bool)),
                     this,
                     SLOT(RequestCardTransfer(CardLayout::Type,
                                              CardLayout::Type,
                                              int, bool)));

    QObject::connect(stateManager,
                     SIGNAL(SetCardsSelectable(bool, int)),
                     cardManager,
                     SLOT(SetCardsSelectable(bool, int)));

    QObject::connect(stateManager,
                     SIGNAL(DeclareSelection(CardLayout::SelectionType)),
                     this,
                     SLOT(DeclareSelection(CardLayout::SelectionType)));

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
                                                     CardLayout::Type)),
                     cardManager,
                     SLOT(CardSelectionsChanged(Card*,
                                                CardLayout::Type)));

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
void GameManager::RequestCardTransfer(CardLayout::Type src,
                                      CardLayout::Type dest,
                                      int  numOfCards,
                                      bool transferSelectedCards)
{
    CardLayout* source      = cardManager->GetDesiredCardLayout(src);
    CardLayout* destination = cardManager->GetDesiredCardLayout(dest);

    if ( transferSelectedCards )
        cardManager->TransferSelectedCards(source, destination);
    else
        cardManager->TransferCards(source, destination, numOfCards);
}


//------------------------------------------------------------------------------
// DeclareSelection - Check the card selection and inform the younger hand to
//                    respond.
//------------------------------------------------------------------------------
void GameManager::DeclareSelection(CardLayout::SelectionType phase)
{
    /*if ( cardManager->CheckSelection(phase) )
    {
        ScoreManager::PhaseScore userScore;
        ScoreManager::Response   response;

        switch ( phase )
        {
            case CardLayout::POINT:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclarePoint(userScore);
                break;

            case CardLayout::SEQUENCE:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclareSequence(userScore);
                break;

            case CardLayout::SET:
                userScore = cardManager->GetSelectionScore(phase);
                response  = ai->DeclareSet(userScore);
                break;

            default:
                break;
        }
    }*/
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
    Card*       card;
    CardLayout* cardArray;
    int         size = 0;

    // Retrieve the cpu's hand and update the ai's knowledge base.
    cardArray = cardManager->GetDesiredCardLayout(CardLayout::CPUHAND);
    size      = cardArray->count();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->itemAt(index);
        ai->UpdateKnowledgeBase(card, index, CardLayout::CPUHAND);
    }

    // Provide the ai with a pointer to the cpu's hand.
    ai->UpdateHand(cardArray);

    // Retrieve the cpu's discards and update the ai's knowledge base.
    cardArray = cardManager->GetDesiredCardLayout(CardLayout::CPUDISCARDS);
    size      = cardArray->count();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->itemAt(index);
        ai->UpdateKnowledgeBase(card, index, CardLayout::CPUDISCARDS);
    }

    // Retrieve the previous tricks and update the ai's knowledge base.
    cardArray = cardManager->GetDesiredCardLayout(CardLayout::PREVIOUSTRICKS);
    size      = cardArray->count();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->itemAt(index);
        ai->UpdateKnowledgeBase(card, index, CardLayout::PREVIOUSTRICKS);
    }
}
