//------------------------------------------------------------------------------
// Filename: GameManager.cpp
// Description: Manages the other Managers in the game.
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
    // Setup the display rect.
    QRectF rect;
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(1366);
    rect.setHeight(768);

    // Initialize the global state info.
    InitGlobalState();

    // Initialize the Scene.
    scene = new Scene(rect);
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

    // Initialize the View and display it.
    view = new View(scene);
    view->show();

    // Connect the various signals to their managers.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void GameManager::Destroy(void)
{
    scene->Destroy();
    cardManager->Destroy();
    player1->Destroy();
    player2->Destroy();
    stateManager->Destroy();

    delete scene;           scene        = 0;
    delete cardManager;     cardManager  = 0;
    delete player1;         player1      = 0;
    delete player2;         player2      = 0;
    delete stateManager;    stateManager = 0;
    delete scoreManager;    scoreManager = 0;
    delete view;            view         = 0;

    DestroyGlobalState();
}


//------------------------------------------------------------------------------
// InitGlobalState - Initialize the global state info.
//------------------------------------------------------------------------------
void GameManager::InitGlobalState(void)
{
    elder                                  = PLAYER1;
    younger                                = PLAYER2;
    trickWinner                            = PLAYER1;

    declaration                            = new Declaration();
    declaration->declaration               = new char[20];
    declaration->response                  = new char[20];

    pointDeclaration                       = new Declaration();
    seqDeclaration                         = new Declaration();
    setDeclaration                         = new Declaration();
    response                               = new Response();

    declarationResults                     = new DeclarationResults();
    declarationResults->carteBlancheWinner = NOPLAYER;

    trickResults                           = new TrickResults();
    trickResults->player1Wins              = 0;
    trickResults->player2Wins              = 0;

    specialScores                          = new SpecialScores();
    specialScores->carteBlancheScored      = false;
    specialScores->repiqueScored           = false;
    specialScores->piqueScored             = false;

    partieResults                          = new PartieResults();
    partieResults->currentDeal             = 0;

    currentPhase                           = DEAL;
    testingAi                              = false;
}


//------------------------------------------------------------------------------
// DestroyGlobalState - Free up the memory associated the global state.
//------------------------------------------------------------------------------
void GameManager::DestroyGlobalState(void)
{
    delete declaration->declaration;    declaration->declaration = 0;
    delete declaration->response;       declaration->response    = 0;
    delete declaration;                 declaration              = 0;

    delete pointDeclaration;            pointDeclaration         = 0;
    delete seqDeclaration;              seqDeclaration           = 0;
    delete setDeclaration;              setDeclaration           = 0;
    delete response;                    response                 = 0;

    delete declarationResults;          declarationResults       = 0;

    delete trickResults;                trickResults             = 0;

    delete specialScores;               specialScores            = 0;

    delete partieResults;               partieResults            = 0;
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to their managers.
//------------------------------------------------------------------------------
void GameManager::ConnectSignals(void)
{
    // Connect the signals from the Scene.
    QObject::connect(scene,
                     SIGNAL(BeginElderSelect()),
                     player1,
                     SIGNAL(BeginElderSelect()));
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
                     SIGNAL(Yes()),
                     player1,
                     SLOT(CarteBlancheYes()));
    QObject::connect(scene,
                     SIGNAL(No()),
                     player1,
                     SLOT(CarteBlancheNo()));
    QObject::connect(scene,
                     SIGNAL(TrickPlayed()),
                     player1,
                     SIGNAL(TrickPlayed()));
    QObject::connect(scene,
                     SIGNAL(Continue()),
                     player1,
                     SIGNAL(Continue()));
    QObject::connect(scene,
                     SIGNAL(NewGame()),
                     this,
                     SLOT(NewGame()));
    QObject::connect(scene,
                     SIGNAL(TestAi()),
                     this,
                     SLOT(TestAi()));
    QObject::connect(scene,
                     SIGNAL(ValidateSelection()),
                     cardManager,
                     SLOT(ValidateSelection()));

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
                     SIGNAL(PrepForTrick()),
                     cardManager,
                     SLOT(PrepForTrick()));
    QObject::connect(player1,
                     SIGNAL(SetCardsMoveable(bool)),
                     cardManager,
                     SLOT(SetCardsMoveable(bool)));
    QObject::connect(player1,
                     SIGNAL(SetCardsSelectable(bool,PlayerNum)),
                     cardManager,
                     SLOT(SetCardsSelectable(bool,PlayerNum)));
    QObject::connect(player1,
                     SIGNAL(DeselectCards()),
                     cardManager,
                     SLOT(DeselectCards()));
    QObject::connect(player1,
                     SIGNAL(SetUI(State)),
                     scene,
                     SLOT(SetUI(State)));
    QObject::connect(player1,
                     SIGNAL(RequestCardTransfer(CardArray::Type,
                                                CardArray::Type,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::Type,
                                              CardArray::Type,
                                              int)));
    QObject::connect(player1,
                     SIGNAL(ScoreCarteBlanche()),
                     scoreManager,
                     SLOT(ScoreCarteBlanche()));
    QObject::connect(player1,
                     SIGNAL(RequestCardPositions(PlayerNum)),
                     this,
                     SLOT(UpdateAI(PlayerNum)));

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
                     SIGNAL(RequestCardTransfer(CardArray::Type,
                                                CardArray::Type,
                                                int)),
                     this,
                     SLOT(RequestCardTransfer(CardArray::Type,
                                              CardArray::Type,
                                              int)));
    QObject::connect(player2,
                     SIGNAL(RequestCardPositions(PlayerNum)),
                     this,
                     SLOT(UpdateAI(PlayerNum)));
    QObject::connect(player2,
                     SIGNAL(ScoreCarteBlanche()),
                     scoreManager,
                     SLOT(ScoreCarteBlanche()));

    // Connect the signals from the CardManager.
    QObject::connect(cardManager,
                     SIGNAL(InformCardsMoveable(bool)),
                     scene,
                     SLOT(SetCardsMoveable(bool)));
    QObject::connect(cardManager,
                     SIGNAL(ValidSelection(bool)),
                     scene,
                     SLOT(SetValidSelection(bool)));

    // Connect the signals from the StateManager.
    QObject::connect(stateManager,
                     SIGNAL(ExecuteElderSelect()),
                     this,
                     SLOT(ExecuteElderSelect()));
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
    QObject::connect(stateManager,
                     SIGNAL(ExecuteSummary()),
                     this,
                     SLOT(ExecuteSummary()));
    QObject::connect(stateManager,
                     SIGNAL(ExitLoop()),
                     player1,
                     SIGNAL(ExitLoop()));

    // Connect the signals from the ScoreManager.
    QObject::connect(scoreManager,
                     SIGNAL(UpdateScores(int,int)),
                     scene,
                     SLOT(UpdateScores(int,int)));
    QObject::connect(scoreManager,
                     SIGNAL(UpdateLog(QString)),
                     scene,
                     SLOT(UpdateLog(QString)));
}


//------------------------------------------------------------------------------
// ResetGame - Reset the game.
//------------------------------------------------------------------------------
void GameManager::ResetGame(bool newGame)
{
    // Reset global state info.
    declarationResults->carteBlancheWinner = NOPLAYER;
    declarationResults->pointWinner        = NOPLAYER;
    declarationResults->sequenceWinner     = NOPLAYER;
    declarationResults->setWinner          = NOPLAYER;
    trickResults->player1Wins              = 0;
    trickResults->player2Wins              = 0;
    specialScores->carteBlancheScored      = false;
    specialScores->repiqueScored           = false;
    specialScores->piqueScored             = false;

    // Reset managers.
    cardManager->Reset();

    if ( newGame )
    {
        partieResults->currentDeal = 0;
        scene->ResetTable();
        stateManager->Reset();
    }

    if ( !newGame )
    {
        if ( elder == PLAYER2 )
            scene->UpdateLog("PLAYER 1: YOUNGER\nPLAYER 2: ELDER");
        else
            scene->UpdateLog("PLAYER 1: ELDER\nPLAYER 2: YOUNGER");
    }

    scoreManager->Reset();
    scene->ClearLog();
    player2->Reset();
    player1->Reset();
}


//------------------------------------------------------------------------------
// ExecuteElderSelect - Select who will be the Elder hand.
//------------------------------------------------------------------------------
void GameManager::ExecuteElderSelect(void)
{
    // If player 1 is a user, allow them to click a button.
    //if ( !dynamic_cast<AI*>(player1) )
    //{
        player1->SelectElder();
    //}

    // Check for ai tests
    if ( testingAi && !dynamic_cast<AI*>(player1) )
    {
        delete player1;
        player1 = new AI();
        player1->Initialize(PLAYER1);
    }

    // Randomly select the elder.
    std::srand(std::time(0));
    int r = rand() % 10 + 1;

    if ( r < 6 )
    {
        elder   = PLAYER1;
        younger = PLAYER2;
        scene->UpdateLog("PLAYER 1: ELDER\nPLAYER 2: YOUNGER");
    }
    else
    {
        elder   = PLAYER2;
        younger = PLAYER1;
        scene->UpdateLog("PLAYER 1: YOUNGER\nPLAYER 2: ELDER");
    }

    emit stateManager->ElderSelectComplete();
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
// ExecuteExchange - Inform the players to perform their Exchanges.
//------------------------------------------------------------------------------
void GameManager::ExecuteExchange(void)
{
    // Check for potential Carte Blanche.
    PlayerNum carteBlanche = cardManager->CheckCarteBlanche();

    // Ask the player if they want to declare their Carte Blanche.
    if ( carteBlanche == PLAYER1 )
        player1->CarteBlanche();
    else if ( carteBlanche == PLAYER2 )
        player2->CarteBlanche();

    // Update the log if Carte Blanche was declared.
    if ( specialScores->carteBlancheScored )
    {
        char* str = new char[30];
        snprintf(str, 30, "PLAYER %d: CARTE BLANCHE",
                 declarationResults->carteBlancheWinner);

        scene->UpdateLog(str);
        delete[] str;
    }

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
// AnnounceDeclaration - Inform the players to announce a Declaration.
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
            if ( dynamic_cast<AI*>(elderPlayer) )
            {
                switch ( phase )
                {
                    case POINT:
                        pointDeclaration->numCards = declaration->numCards;
                        break;

                    case SEQUENCE:
                        seqDeclaration->numCards = declaration->numCards;
                        break;

                    case SET:
                        setDeclaration->numCards = declaration->numCards;
                        break;

                    default:
                        break;
                }
            }

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
            else if ( dynamic_cast<AI*>(elderPlayer) )
            {
                switch ( phase )
                {
                    case POINT:
                        pointDeclaration->numCards = response->numCards;
                        break;

                    case SEQUENCE:
                        seqDeclaration->numCards = response->numCards;
                        break;

                    case SET:
                        setDeclaration->numCards = response->numCards;
                        break;

                    default:
                        break;
                }
            }
        }
        else
        {
            switch ( phase )
            {
                case POINT:
                    declarationResults->pointWinner = younger;
                    pointDeclaration->numCards = 0;
                    break;

                case SEQUENCE:
                    declarationResults->sequenceWinner = younger;
                    seqDeclaration->numCards = 0;
                    break;

                case SET:
                    declarationResults->setWinner = younger;
                    setDeclaration->numCards = 0;
                    break;

                default:
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
    scoreManager->CreateDeclaration(phase, selectedCards);

    // Output the declaration (if applicable).
    if ( declaration->notSkipped )
    {
        char* str = new char[30];
        snprintf(str, 30, "PLAYER %d: %s", player, declaration->declaration);

        scene->UpdateLog(str);
        delete[] str;
    }

    // Disable the selected cards.
    for ( int i = 0; i < (int)selectedCards.size(); i++ )
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
    scoreManager->CreateResponse(phase, selectedCards);

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
// PlayTrick - Inform a player to play a Trick.
//------------------------------------------------------------------------------
void GameManager::PlayTrick(PlayerNum player)
{
    CardArray* leadTrick;
    CardArray* followTrick;

    if ( player == PLAYER1 )
    {
        if ( dynamic_cast<AI*>(player1) )
        {
            cardManager->SetCardsSelectable(true, player);
            player1->PlayTrick();
            cardManager->SetCardsSelectable(false, player);
        }
        else
        {
            player1->PlayTrick();
        }
    }
    else
    {
        if ( dynamic_cast<AI*>(player2) )
        {
            cardManager->SetCardsSelectable(true, player);
            player2->PlayTrick();
            cardManager->SetCardsSelectable(false, player);
        }
        else
        {
            player2->PlayTrick();
        }
    }

    if ( player == PLAYER1 )
    {
        leadTrick   = cardManager->GetCardArray(CardArray::CPUTRICK);
        followTrick = cardManager->GetCardArray(CardArray::PLAYERTRICK);
    }
    else
    {
        leadTrick   = cardManager->GetCardArray(CardArray::PLAYERTRICK);
        followTrick = cardManager->GetCardArray(CardArray::CPUTRICK);
    }

    if ( leadTrick->GetSize() > 0 && followTrick->GetSize() > 0 )
    {
        PlayerNum winner = scoreManager->ScoreTrick(player,
                                                    leadTrick->GetCard(0),
                                                    followTrick->GetCard(0));

        RequestCardTransfer(CardArray::PLAYERTRICK,
                            CardArray::PREVIOUSTRICKS, 1);
        RequestCardTransfer(CardArray::CPUTRICK,
                            CardArray::PREVIOUSTRICKS, 1);

        trickWinner = winner;
    }
    else
    {
        // Score the Trick.
        scoreManager->ScoreTrick(player);
    }

}


//------------------------------------------------------------------------------
// ExecuteSummary - Execute a summary of a game/partie.
//------------------------------------------------------------------------------
void GameManager::ExecuteSummary(void)
{
    // Post the results.
    partieResults->deal[0][partieResults->currentDeal] = scoreManager->GetPlayerScore();
    partieResults->deal[1][partieResults->currentDeal] = scoreManager->GetCPUScore();

    scene->PostScore(partieResults->currentDeal);

    // If this was the last partie, execute a game summary.
    if ( partieResults->currentDeal == 5 )
    {
        partieResults->currentDeal++;

        // If a user is playing, wait for them to select 'New Game'.
        if ( !dynamic_cast<AI*>(player1) )
        {
            player1->Summary();
            ResetGame(true);
        }
        else if ( 1 )
        {
            // If the ai still has game's to play.
            int x = 0;
        }
        else
        {
            // The ai is done.
            testingAi = false;

            delete player1;
            player1 = new Player();
            player1->Initialize(PLAYER1);
        }
    }
    else
    {
        partieResults->currentDeal++;

        // If a user is playing, wait for them to select 'Continue'.
        if ( !dynamic_cast<AI*>(player1) )
        {
            player1->Summary();
        }

        // Reset the state of the game to the deal phase and switch elder.
        elder   = (elder   == PLAYER1) ? PLAYER2 : PLAYER1;
        younger = (younger == PLAYER1) ? PLAYER2 : PLAYER1;

        ResetGame();
    }
}


//------------------------------------------------------------------------------
// NewGame - Reset the program and begin a new game.
//------------------------------------------------------------------------------
void GameManager::NewGame(void)
{
    testingAi = false;
    ResetGame(true);
}


//------------------------------------------------------------------------------
// TestAi - Test an ai by pitting it against another ai.
//------------------------------------------------------------------------------
void GameManager::TestAi(void)
{
    testingAi = true;
    ResetGame(true);
}


//------------------------------------------------------------------------------
// RequestCardTransfer - Request a number of cards be transferred to a different
//                       CardArray.
//------------------------------------------------------------------------------
void GameManager::RequestCardTransfer(CardArray::Type src,
                                      CardArray::Type dest,
                                      int numCards)
{
    CardArray* source      = cardManager->GetCardArray(src);
    CardArray* destination = cardManager->GetCardArray(dest);

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
    if ( player == PLAYER1 )
        cardArray = cardManager->GetCardArray(CardArray::PLAYERHAND);
    else
        cardArray = cardManager->GetCardArray(CardArray::CPUHAND);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUHAND);
    }

    // Provide the ai with a pointer to the cpu's hand.
    ai->UpdateHand(cardArray);

    // Retrieve the cpu's discards and update the ai's knowledge base.
    if ( player == PLAYER1 )
        cardArray = cardManager->GetCardArray(CardArray::PLAYERDISCARDS);
    else
        cardArray = cardManager->GetCardArray(CardArray::CPUDISCARDS);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::CPUDISCARDS);
    }

    // Retrieve the previous tricks and update the ai's knowledge base.
    cardArray = cardManager->GetCardArray(CardArray::PREVIOUSTRICKS);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::PREVIOUSTRICKS);
    }

    // Retrieve the current trick and update the ai's knowledge base.
    if ( player == PLAYER1 )
        cardArray = cardManager->GetCardArray(CardArray::CPUTRICK);
    else
        cardArray = cardManager->GetCardArray(CardArray::PLAYERTRICK);
    size      = cardArray->GetSize();

    for ( int index = 0; index < size; index++ )
    {
        card = cardArray->GetCard(index);
        ai->UpdateKnowledgeBase(card, index, CardArray::PLAYERTRICK);
    }
}
