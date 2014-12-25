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

    // Initialize the players (default is player vs cpu).
    player1 = new Player();
    player1->Initialize(PLAYER1);
    player2 = new AI();
    player2->Initialize(PLAYER2);

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
    // OLD CODE //
    // Connect the signals from the card manager.
   /* QObject::connect(cardManager,
                     SIGNAL(TransferComplete()),
                     this,
                     SLOT(TransferComplete()));

    // Connect the signals from the state manager.
    QObject::connect(stateManager,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SLOT(SetUI(Scene::PhaseType)));
    QObject::connect(stateManager,
                     SIGNAL(BeginExchange(int)),
                     this,
                     SLOT(BeginExchange(int)));
    QObject::connect(stateManager,
                     SIGNAL(MakeDeclaration(CardArray::SelectionType,
                                            PlayerNum)),
                     this,
                     SLOT(MakeDeclaration(CardArray::SelectionType,
                                          PlayerNum)));

    // Connect the signals from player 1.
    QObject::connect(player1,
                     SIGNAL(DealComplete()),
                     stateManager,
                     SIGNAL(DealComplete()));
    QObject::connect(player1,
                     SIGNAL(ExchangeComplete()),
                     stateManager,
                     SIGNAL(ExchangeComplete()));
    QObject::connect(player1,
                     SIGNAL(AllExchangesComplete()),
                     stateManager,
                     SIGNAL(AllExchangesComplete()));
    QObject::connect(player1,
                     SIGNAL(AnnounceDeclaration(CardArray::SelectionType,
                                                PlayerNum)),
                     this,
                     SLOT(ProcessDeclaration(CardArray::SelectionType,
                                             PlayerNum)));
    QObject::connect(player1,
                     SIGNAL(SetCardsSelectable(bool)),
                     cardManager,
                     SLOT(SetCardsSelectable(bool)));
    QObject::connect(player1,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int)));
    QObject::connect(player1,
                     SIGNAL(SetUI(State)),
                     this,
                     SLOT(SetUI(State)));

    // Connect the signals from player 2.
    QObject::connect(player2,
                     SIGNAL(DealComplete()),
                     stateManager,
                     SIGNAL(DealComplete()));
    QObject::connect(player2,
                     SIGNAL(ExchangeComplete()),
                     stateManager,
                     SIGNAL(ExchangeComplete()));
    QObject::connect(player2,
                     SIGNAL(AllExchangesComplete()),
                     stateManager,
                     SIGNAL(AllExchangesComplete()));
    QObject::connect(player2,
                     SIGNAL(RequestCardPositions(PlayerNum)),
                     this,
                     SLOT(UpdateAI(PlayerNum)));
    QObject::connect(player2,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int)));
    QObject::connect(player2,
                     SIGNAL(SetUI(Scene::PhaseType)),
                     this,
                     SLOT(SetUI(Scene::PhaseType)));

    // Connect the signals from the scene.
    QObject::connect(scene,
                     SIGNAL(ExecuteDeal()),
                     this,
                     SLOT(ExecuteDeal()));
    QObject::connect(scene,
                     SIGNAL(ExecuteExchange()),
                     player1,
                     SLOT(ExecuteExchange()));
    */

    // NEW CODE //
    // Connect the signals from the card manager.
    QObject::connect(cardManager,
                     SIGNAL(InformCardsMoveable(bool)),
                     scene,
                     SLOT(SetCardsMoveable(bool)));
    QObject::connect(cardManager,
                     SIGNAL(ValidSelection(bool)),
                     scene,
                     SLOT(SetValidSelection(bool)));

    // Connect the signals from the state manager.
    QObject::connect(stateManager,
                     SIGNAL(ExecuteDeal()),
                     this,
                     SLOT(ExecuteDeal()));
    QObject::connect(stateManager,
                     SIGNAL(ExecuteExchange()),
                     this,
                     SLOT(ExecuteExchange()));
    QObject::connect(stateManager,
                     SIGNAL(AnnounceDeclaration(State, PlayerNum)),
                     this,
                     SLOT(AnnounceDeclaration(State, PlayerNum)));
    QObject::connect(stateManager,
                     SIGNAL(PlayTrick(PlayerNum)),
                     this,
                     SLOT(PlayTrick(PlayerNum)));

    // Connect the signals from player 1.
    QObject::connect(player1,
                     SIGNAL(DealComplete()),
                     stateManager,
                     SIGNAL(DealComplete()));
    QObject::connect(player1,
                     SIGNAL(ExchangeComplete()),
                     stateManager,
                     SIGNAL(ExchangeComplete()));
    QObject::connect(player1,
                     SIGNAL(SetCardsMoveable(bool)),
                     cardManager,
                     SLOT(SetCardsMoveable(bool)));
    QObject::connect(player1,
                     SIGNAL(DeselectCards()),
                     cardManager,
                     SLOT(DeselectUserCards()));
    QObject::connect(player1,
                     SIGNAL(SetUI(State)),
                     scene,
                     SLOT(SetUI(State)));
    QObject::connect(player1,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int)));

    // Connect the signals from player 2.
    QObject::connect(player2,
                     SIGNAL(DealComplete()),
                     stateManager,
                     SIGNAL(DealComplete()));
    QObject::connect(player2,
                     SIGNAL(ExchangeComplete()),
                     stateManager,
                     SIGNAL(ExchangeComplete()));
    QObject::connect(player2,
                     SIGNAL(SetUI(State)),
                     scene,
                     SLOT(SetUI(State)));
    QObject::connect(player2,
                     SIGNAL(RequestCardTransfer(CardArray::CardArrayType,
                                                CardArray::CardArrayType,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::CardArrayType,
                                              CardArray::CardArrayType,
                                              int)));
    QObject::connect(player2,
                     SIGNAL(RequestCardPositions(PlayerNum)),
                     this,
                     SLOT(UpdateAI(PlayerNum)));

    // Connect the signals from the scene.
    QObject::connect(scene,
                     SIGNAL(BeginDeal()),
                     player1,
                     SIGNAL(BeginDeal()));
    QObject::connect(scene,
                     SIGNAL(BeginExchange()),
                     player1,
                     SIGNAL(BeginExchange()));
    QObject::connect(scene,
                     SIGNAL(Declare()),
                     player1,
                     SIGNAL(Declare()));
    QObject::connect(scene,
                     SIGNAL(Skip()),
                     player1,
                     SIGNAL(Skip()));
    QObject::connect(scene,
                     SIGNAL(TrickPlayed()),
                     player1,
                     SIGNAL(TrickPlayed()));
    QObject::connect(scene,
                     SIGNAL(ValidateSelection()),
                     cardManager,
                     SLOT(ValidateSelection()));
}


//------------------------------------------------------------------------------
// ExecuteDeal - Inform the younger to begin dealing the cards.
//------------------------------------------------------------------------------
void GameManager::ExecuteDeal(void)
{
    if ( younger == PLAYER1 )
    {
        player1->ExecuteDeal();
        scene->UpdateLog("PLAYER 1: DEAL");
    }
    else
    {
        player2->ExecuteDeal();
        scene->UpdateLog("PLAYER 2: DEAL");
    }
}


//------------------------------------------------------------------------------
// ExecuteExchange - Inform the players to perform their exchanges.
//------------------------------------------------------------------------------
void GameManager::ExecuteExchange(void)
{
    if ( elder == PLAYER1 )
    {
        cardManager->SetCardsSelectable(true, PLAYER1);
        player1->ExecuteExchange();
        cardManager->SetCardsSelectable(false, PLAYER1);

        cardManager->SetCardsSelectable(true, PLAYER2);
        player2->ExecuteExchange();
        cardManager->SetCardsSelectable(false, PLAYER2);
    }
    else
    {
        cardManager->SetCardsSelectable(true, PLAYER2);
        player2->ExecuteExchange();
        cardManager->SetCardsSelectable(false, PLAYER2);

        cardManager->SetCardsSelectable(true, PLAYER1);
        player1->ExecuteExchange();
        cardManager->SetCardsSelectable(false, PLAYER1);
    }
}


//------------------------------------------------------------------------------
// AnnounceDeclaration - Inform the players to announce a declaration.
//------------------------------------------------------------------------------
void GameManager::AnnounceDeclaration(State phase, PlayerNum player)
{
    Player* elderPlayer;
    Player* youngerPlayer;

    // Determine who will be making declarations.
    if ( player == elder )
    {
        elderPlayer   = (player == PLAYER1) ? player1 : player2;
        youngerPlayer = (player == PLAYER1) ? player2 : player1;
    }
    else
    {
        elderPlayer   = (player == PLAYER1) ? player2 : player1;
        youngerPlayer = (player == PLAYER1) ? player1 : player2;
    }

    // Set the phase for user selection validation.
    currentPhase = phase;

    // If the elder is making declarations, the younger may respond.
    // There are no responses to the younger's declarations.
    if ( player == elder )
    {
        // Elder makes his declaration.
        cardManager->SetCardsSelectable(true, elder);
        elderPlayer->AnnounceDeclaration(phase);
        DeclareSelection(phase, elder);

        // Younger makes his response if needed.
        if ( declaration->notSkipped )
        {
            cardManager->SetCardsSelectable(true, younger);
            youngerPlayer->Respond(phase);
            ResolveResponse(phase, younger);
            cardManager->SetCardsSelectable(false, younger);

            // Score the declaration.
            scoreManager->ScoreDeclaration(phase, elder);

            // If elder won their declaration and this isn't the Point,
            // elder may make as many declarations as they like/can.
            if ( response->good && phase != POINT )
            {
                while ( declaration->notSkipped )
                {
                    elderPlayer->AnnounceDeclaration(phase);
                    DeclareSelection(phase, elder);
                    response->good = true;
                    scoreManager->ScoreDeclaration(phase, elder);
                }
            }
        }
        else
        {
            switch ( phase )
            {
                case POINT:
                    declarationResults->pointWinner = younger;
                    break;

                case SEQUENCE:
                    declarationResults->sequenceWinner = younger;
                    break;

                case SET:
                    declarationResults->setWinner = younger;
                    break;
            }
        }

        if ( dynamic_cast<AI*>(elderPlayer) )
            UpdateAI(elder);
        cardManager->SetCardsSelectable(false, elder);
    }
    else
    {
        // Younger announces their declarations and scores for it.
        cardManager->SetCardsSelectable(true, younger);
        youngerPlayer->AnnounceDeclaration(phase);
        DeclareSelection(phase, younger);
        response->good = true;
        scoreManager->ScoreDeclaration(phase, younger);

        if ( phase != POINT )
        {
            while ( declaration->notSkipped )
            {
                youngerPlayer->AnnounceDeclaration(phase);
                DeclareSelection(phase, younger);
                response->good = true;
                scoreManager->ScoreDeclaration(phase, younger);
            }
        }

        if ( dynamic_cast<AI*>(youngerPlayer) )
            UpdateAI(younger);
        cardManager->SetCardsSelectable(false, younger);
    }
}


//------------------------------------------------------------------------------
// DeclareSelection - Check the card selection and inform the younger hand to
//                    respond.
//------------------------------------------------------------------------------
void GameManager::DeclareSelection(State phase, PlayerNum player)
{
    // Get the player's selection.
    std::vector<Card*> selectedCards = cardManager->GetSelection(player);

    // Create a declaration from the selection and store it in the global state.
    scoreManager->CreateDeclaration(selectedCards, phase);

    // Output the declaration (if applicable).
    if ( declaration->notSkipped )
    {
        char* str = new char[30];
        snprintf(str, 30, "PLAYER %d: %s", player, declaration->declaration);

        scene->UpdateLog(str);
        delete[] str;
    }

    // Disable the selected cards.
    for ( int i = 0; i < selectedCards.size(); i++ )
        selectedCards[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
}


//------------------------------------------------------------------------------
// ResolveResponse - Resolve the response of the younger hand.
//------------------------------------------------------------------------------
void GameManager::ResolveResponse(State phase, PlayerNum player)
{
    // Get the player's selection.
    std::vector<Card*> selectedCards = cardManager->GetSelection(player);

    // Create a response from the selection and store it in the global state.
    scoreManager->CreateResponse(selectedCards, phase);

    char* str = new char[30];

    // Output the response.
    if ( response->hasQuestion )
    {
        snprintf(str, 30, "PLAYER %d: HOW HIGH?", player);
        scene->UpdateLog(str);

        snprintf(str, 30, "PLAYER %d: %s", elder, declaration->response);
        scene->UpdateLog(str);
    }

    if ( response->good )
    {
        snprintf(str, 30, "PLAYER %d: GOOD", player);
        scene->UpdateLog(str);
    }
    else if ( response->even )
    {
        snprintf(str, 30, "PLAYER %d: EVEN", player);
        scene->UpdateLog(str);
    }
    else
    {
        snprintf(str, 30, "PLAYER %d: NOT GOOD", player);
        scene->UpdateLog(str);
    }

    delete[] str;
}


//------------------------------------------------------------------------------
// PlayTrick - Reolve the response of the younger hand.
//------------------------------------------------------------------------------
void GameManager::PlayTrick(PlayerNum player)
{
    if ( player == PLAYER1 )
        player1->PlayTrick();
    else
        player2->PlayTrick();
}


//------------------------------------------------------------------------------
// RequestCardTransfer - Request a number of cards be transferred to a different
//                       CardArray.
//------------------------------------------------------------------------------
void GameManager::RequestCardTransfer(CardArray::CardArrayType src,
                                      CardArray::CardArrayType dest,
                                      int numCards)
{
    CardArray* source      = cardManager->GetDesiredCardArray(src);
    CardArray* destination = cardManager->GetDesiredCardArray(dest);

    cardManager->TransferCards(source, destination, numCards);
}


//------------------------------------------------------------------------------
// UpdateAI - Update the game's ai with current knowledge.
//------------------------------------------------------------------------------
void GameManager::UpdateAI(PlayerNum player)
{
    Card*      card;
    CardArray* cardArray;
    int        size = 0;

    // Select the chosen player.
    AI* ai = player == PLAYER1 ? (AI*)player1 : (AI*)player2;

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
