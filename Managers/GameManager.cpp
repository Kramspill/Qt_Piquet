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

    QObject::connect(cardManager,
                     SIGNAL(InformCardsMoveable(bool)),
                     scene,
                     SLOT(SetCardsMoveable(bool)));

    // Connect the signals from the state manager.
    QObject::connect(stateManager,
                     SIGNAL(RequestDialog(Dialog::DialogType)),
                     scene,
                     SLOT(CreateDialog(Dialog::DialogType)));

    QObject::connect(stateManager,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SLOT(SetUI(Scene::PhaseType)));

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
                     SIGNAL(SetCardsMoveable(bool)),
                     cardManager,
                     SLOT(SetCardsMoveable(bool)));

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

    QObject::connect(scene,
                     SIGNAL(ExecuteExchange()),
                     stateManager,
                     SIGNAL(ExecuteExchange()));

    QObject::connect(scene,
                     SIGNAL(DeclarePoint()),
                     this,
                     SLOT(DeclarePoint()));

    QObject::connect(scene,
                     SIGNAL(DeclareSequence()),
                     this,
                     SLOT(DeclareSequence()));

    QObject::connect(scene,
                     SIGNAL(DeclareSet()),
                     this,
                     SLOT(DeclareSet()));

    QObject::connect(scene,
                     SIGNAL(SkipDeclaration()),
                     this,
                     SLOT(SkipDeclaration())); // TODO

    QObject::connect(scene,
                     SIGNAL(SkipPoint()),
                     this,
                     SLOT(SkipPoint()));

    QObject::connect(scene,
                     SIGNAL(SkipSequence()),
                     this,
                     SLOT(SkipSequence()));

    QObject::connect(scene,
                     SIGNAL(SkipSet()),
                     this,
                     SLOT(SkipSet()));

    QObject::connect(scene,
                     SIGNAL(RequestACardTransfer(CardArray::CardArrayType,
                                                 CardArray::CardArrayType,
                                                 Card*)),
                     this,
                     SLOT(RequestACardTransfer(CardArray::CardArrayType,
                                               CardArray::CardArrayType,
                                               Card*)));
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
// RequestACardTransfer - Request a card to be transferred to a different
//                        CardArray.
//------------------------------------------------------------------------------
void GameManager::RequestACardTransfer(CardArray::CardArrayType src,
                                       CardArray::CardArrayType dest,
                                       Card* card)
{
    CardArray* source      = cardManager->GetDesiredCardArray(src);
    CardArray* destination = cardManager->GetDesiredCardArray(dest);

    cardManager->TransferCard(source, destination, card);
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


//------------------------------------------------------------------------------
// SetUI - Set the scene's ui.
//------------------------------------------------------------------------------
void GameManager::SetUI(Scene::PhaseType phase)
{
    scene->SetUI(phase);
}


//------------------------------------------------------------------------------
// DeclarePoint - Player declare's their Point.
//------------------------------------------------------------------------------
void GameManager::DeclarePoint(void)
{
    if ( cardManager->CheckSelection(CardArray::POINT) )
    {
        ScoreManager::PhaseScore userScore;

        userScore = cardManager->GetSelectionScore(CardArray::POINT);
        ai->DeclarePoint(userScore);
    }
}


//------------------------------------------------------------------------------
// DeclareSequence - Player declare's their Sequence.
//------------------------------------------------------------------------------
void GameManager::DeclareSequence(void)
{
    if ( cardManager->CheckSelection(CardArray::SEQUENCE) )
    {
        ScoreManager::PhaseScore userScore;

        userScore = cardManager->GetSelectionScore(CardArray::SEQUENCE);
        ai->DeclareSequence(userScore);
    }
}


//------------------------------------------------------------------------------
// DeclareSet - Player declare's their Set.
//------------------------------------------------------------------------------
void GameManager::DeclareSet(void)
{
    if ( cardManager->CheckSelection(CardArray::SET) )
    {
        ScoreManager::PhaseScore userScore;

        userScore = cardManager->GetSelectionScore(CardArray::SET);
        ai->DeclareSet(userScore);
    }
}


//------------------------------------------------------------------------------
// SkipDeclaration - Skip a declaration.
//------------------------------------------------------------------------------
void GameManager::SkipDeclaration(void)
{
    ScoreManager::PhaseScore userScore;

    userScore.numOfCards = 0;
    userScore.totalValue = 0;
    // TO DO:
}


//------------------------------------------------------------------------------
// SkipPoint - Skip the Point declaration.
//------------------------------------------------------------------------------
void GameManager::SkipPoint(void)
{
    ScoreManager::PhaseScore userScore;

    userScore.numOfCards = 0;
    userScore.totalValue = 0;

    ai->DeclarePoint(userScore);
}


//------------------------------------------------------------------------------
// SkipSequence - Skip the Sequence declaration.
//------------------------------------------------------------------------------
void GameManager::SkipSequence(void)
{
    ScoreManager::PhaseScore userScore;

    userScore.numOfCards = 0;
    userScore.totalValue = 0;

    ai->DeclareSequence(userScore);
}


//------------------------------------------------------------------------------
// SkipSet - Skip the Set declaration.
//------------------------------------------------------------------------------
void GameManager::SkipSet(void)
{
    ScoreManager::PhaseScore userScore;

    userScore.numOfCards = 0;
    userScore.totalValue = 0;

    ai->DeclareSet(userScore);
}
