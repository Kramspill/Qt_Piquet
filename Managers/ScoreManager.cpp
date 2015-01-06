//------------------------------------------------------------------------------
// Filename: ScoreManager.cpp
// Description: Manager that keeps track of the game score.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "ScoreManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ScoreManager::ScoreManager(void) :
    playerScore(0),
    cpuScore(0)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
ScoreManager::ScoreManager(ScoreManager&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
ScoreManager::~ScoreManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Does stuff.
//------------------------------------------------------------------------------
void ScoreManager::Initialize(void)
{
    playerScore = 0;
    cpuScore    = 0;
}


//------------------------------------------------------------------------------
// Reset - Reset the scores and post them to the score table.
//------------------------------------------------------------------------------
void ScoreManager::Reset(void)
{
    playerScore = 0;
    cpuScore    = 0;
    emit UpdateScores(0,0);
}


//------------------------------------------------------------------------------
// CreateDeclaration - Create a Declaration from a selection.
//------------------------------------------------------------------------------
void ScoreManager::CreateDeclaration(State phase, std::vector<Card*> cards)
{
    // Initialize the declaration.
    declaration->numCards   = 0;
    declaration->value      = 0;
    declaration->score      = 0;
    declaration->notSkipped = false;

    // Check if player just skipped.
    if ( cards.size() != 0 )
    {
        // Set the number of cards.
        declaration->numCards = cards.size();

        // Set the value.
        declaration->value = GetValue(phase, cards);

        // Set the declaration text.
        GetDeclaration(phase, cards.size());
        GetResponse(phase, declaration->value);

        declaration->notSkipped = true;

        // Set the score based on the phase we are declaring for.
        switch ( phase )
        {
            case POINT:
                declaration->score = declaration->numCards;
                break;

            case SEQUENCE:
                if ( declaration->numCards < 5 )
                    declaration->score  = declaration->numCards;
                else
                    declaration->score = declaration->numCards + 10;
                break;

            case SET:
                if ( declaration->numCards == 3 )
                    declaration->score = 3;
                else
                    declaration->score = 14;
                break;

            default:
                break;
        }
    }
}


//------------------------------------------------------------------------------
// CreateResponse - Create a Response from a selection.
//------------------------------------------------------------------------------
void ScoreManager::CreateResponse(State phase, std::vector<Card*> cards)
{
    // Initialize the response.
    response->good        = true;
    response->even        = false;
    response->hasQuestion = false;
    response->numCards    = 0;
    response->value       = 0;
    response->score       = 0;

    // Check if player responded 'Not Good'.
    if ( (int)cards.size() >= declaration->numCards )
    {
        // Set the number of cards.
        response->numCards = cards.size();

        // Set the value.
        response->value    = GetValue(phase, cards);

        switch ( phase )
        {
            case POINT:
                response->score = response->numCards;
                break;

            case SEQUENCE:
                if ( response->numCards < 5 )
                    response->score = response->numCards;
                else
                    response->score = response->numCards + 10;
                break;

            case SET:
                if ( response->numCards == 3 )
                    response->score =  3;
                else
                    response->score = 14;
                break;

            default:
                break;
        }

        // Compare the scores to determine the exact response.
        if ( response->numCards > declaration->numCards )
        {
            response->good        = false;
            response->even        = false;
            response->hasQuestion = false;
        }
        else
        {
            response->hasQuestion = true;

            if ( response->value > declaration->value )
            {
                response->good = false;
                response->even = false;
            }
            else
            {
                if ( response->value == declaration->value )
                {
                    response->good = false;
                    response->even = true;
                }
                else
                {
                    response->good = true;
                    response->even = false;
                }
            }
        }
    }
}


//------------------------------------------------------------------------------
// ScoreDeclaration - Score a player's Declaration.
//------------------------------------------------------------------------------
void ScoreManager::ScoreDeclaration(State phase, PlayerNum player)
{
    if ( response->good )
    {
        if ( player == PLAYER1 )
            playerScore += declaration->score;
        else
            cpuScore += declaration->score;

        // Store the victory status.
        switch ( phase )
        {
            case POINT:
                declarationResults->pointWinner = player;
                break;

            case SEQUENCE:
                declarationResults->sequenceWinner = player;
                break;

            case SET:
                declarationResults->setWinner = player;
                break;

            default:
                break;
        }
    }
    else
    {
        if ( response->even )
        {
            // Store the victory status.
            switch ( phase )
            {
                case POINT:
                    declarationResults->pointWinner = NOPLAYER;
                    break;

                case SEQUENCE:
                    declarationResults->sequenceWinner = NOPLAYER;
                    break;

                case SET:
                    declarationResults->setWinner = NOPLAYER;
                    break;

                default:
                    break;
            }
        }
        else
        {
            // Store the victory status.
            switch ( phase )
            {
                case POINT:
                    if ( player == PLAYER1 )
                        declarationResults->pointWinner = PLAYER2;
                    else
                        declarationResults->pointWinner = PLAYER1;
                    break;

                case SEQUENCE:
                    if ( player == PLAYER1 )
                        declarationResults->sequenceWinner = PLAYER2;
                    else
                        declarationResults->sequenceWinner = PLAYER1;
                    break;

                case SET:
                    if ( player == PLAYER1 )
                        declarationResults->setWinner = PLAYER2;
                    else
                        declarationResults->setWinner = PLAYER1;
                    break;

                default:
                    break;
            }
        }
    }

    // Check for special case Repique.
    if ( !specialScores->repiqueScored )
    {
        if ( playerScore >= 30 || cpuScore >= 30 )
        {
            char* str = new char[20];
            bool repiquePotential = true;

            if ( playerScore >= 30 )
            {
                if ( specialScores->carteBlancheScored &&
                     declarationResults->carteBlancheWinner == PLAYER2 )
                {
                    repiquePotential = false;
                }

                if ( repiquePotential )
                {
                    switch ( phase )
                    {
                        case SEQUENCE:
                            if ( declarationResults->pointWinner != PLAYER2 )
                            {
                                specialScores->repiqueScored = true;
                                playerScore += 60;
                                snprintf(str, 20, "PLAYER 1: REPIQUE");
                                emit UpdateLog(str);
                            }
                            break;

                        case SET:
                            if ( declarationResults->pointWinner != PLAYER2 &&
                                 declarationResults->sequenceWinner != PLAYER2 )
                            {
                                specialScores->repiqueScored = true;
                                playerScore += 60;
                                snprintf(str, 20, "PLAYER 1: REPIQUE");
                                emit UpdateLog(str);
                            }
                            break;

                        default:
                            break;
                    }
                }
            }
            else
            {
                if ( specialScores->carteBlancheScored &&
                     declarationResults->carteBlancheWinner == PLAYER1 )
                {
                    repiquePotential = false;
                }

                if ( repiquePotential )
                {
                    switch ( phase )
                    {
                        case SEQUENCE:
                            if ( declarationResults->pointWinner != PLAYER1 )
                            {
                                specialScores->repiqueScored = true;
                                cpuScore += 60;
                                snprintf(str, 20, "PLAYER 2: REPIQUE");
                                emit UpdateLog(str);
                            }
                            break;

                        case SET:
                            if ( declarationResults->pointWinner != PLAYER1 &&
                                 declarationResults->sequenceWinner != PLAYER1 )
                            {
                                specialScores->repiqueScored = true;
                                cpuScore += 60;
                                snprintf(str, 20, "PLAYER 2: REPIQUE");
                                emit UpdateLog(str);
                            }
                            break;

                        default:
                            break;
                    }
                }
            }

            delete[] str;
        }
    }

    // Update the score table.
    emit UpdateScores(playerScore, cpuScore);
}


//------------------------------------------------------------------------------
// ScoreTrick - Score the Tricks in play.
//------------------------------------------------------------------------------
PlayerNum ScoreManager::ScoreTrick(PlayerNum player,
                                   Card*     leadCard,
                                   Card*     followCard)
{
    PlayerNum winner = NOPLAYER;

    if ( !leadCard && !followCard )
    {
        (player == PLAYER1) ? playerScore++ : cpuScore++;
    }
    else if ( leadCard->GetSuit() == followCard->GetSuit() &&
         leadCard->GetRank() <  followCard->GetRank() )
    {
        (player == PLAYER1) ? playerScore++ : cpuScore++;
        (player == PLAYER1) ? trickResults->player1Wins++ :
                              trickResults->player2Wins++;
        winner = player;
    }
    else
    {
        (player == PLAYER1) ? trickResults->player2Wins++ :
                              trickResults->player1Wins++;
        winner = (player == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    // Check for special case Pique.
    if ( !specialScores->repiqueScored && !specialScores->piqueScored )
    {
        if ( (playerScore >= 30 && cpuScore == 0) ||
             (cpuScore >= 30 && playerScore == 0) )
        {
            char* str = new char[20];
            bool piquePotential = true;

            if ( playerScore >= 30 )
            {
                if ( specialScores->carteBlancheScored &&
                     declarationResults->carteBlancheWinner == PLAYER2 )
                {
                    piquePotential = false;
                }

                if ( piquePotential &&
                     declarationResults->pointWinner != PLAYER2 &&
                     declarationResults->sequenceWinner != PLAYER2 &&
                     declarationResults->setWinner != PLAYER2 )
                {
                        specialScores->piqueScored = true;
                        playerScore += 30;
                        snprintf(str, 20, "PLAYER 1: PIQUE");
                        emit UpdateLog(str);
                }
            }
            else
            {
                if ( specialScores->carteBlancheScored &&
                     declarationResults->carteBlancheWinner == PLAYER1 )
                {
                    piquePotential = false;
                }

                if ( piquePotential &&
                     declarationResults->pointWinner != PLAYER1 &&
                     declarationResults->sequenceWinner != PLAYER1 &&
                     declarationResults->setWinner != PLAYER1 )
                {
                        specialScores->piqueScored = true;
                        cpuScore += 30;
                        snprintf(str, 20, "PLAYER 2: PIQUE");
                        emit UpdateLog(str);
                }
            }

            delete[] str;
        }
    }

    // Final scoring (The cards/Capot).
    if ( trickResults->player1Wins + trickResults->player2Wins == 12 )
    {
        char* str = new char[20];

        (winner == PLAYER1) ? playerScore++ : cpuScore++;

        // Final check for Pique.
        if ( !specialScores->repiqueScored &&
             !specialScores->piqueScored )
        {
            if ( playerScore >= 30 && cpuScore == 0 )
            {
                specialScores->piqueScored = true;
                playerScore += 30;
                snprintf(str, 20, "PLAYER 1: PIQUE");
                emit UpdateLog(str);
            }
            else if ( cpuScore >= 30 && playerScore == 0 )
            {
                specialScores->piqueScored = true;
                cpuScore += 30;
                snprintf(str, 20, "PLAYER 2: PIQUE");
                emit UpdateLog(str);
            }
        }

        if ( trickResults->player1Wins > trickResults->player2Wins )
        {
            if ( trickResults->player2Wins == 0 )
            {
                snprintf(str, 20, "PLAYER 1: CAPOT");
                playerScore += 40;
            }
            else
            {
                snprintf(str, 20, "PLAYER 1: THE CARDS");
                playerScore += 10;
            }

            emit UpdateLog(str);
        }
        else if ( trickResults->player2Wins > trickResults->player1Wins )
        {
            if ( trickResults->player1Wins == 0 )
            {
                snprintf(str, 20, "PLAYER 2: CAPOT");
                cpuScore += 40;
            }
            else
            {
                snprintf(str, 20, "PLAYER 2: THE CARDS");
                cpuScore += 10;
            }

            emit UpdateLog(str);
        }

        delete[] str;
    }

    // Update the score table.
    emit UpdateScores(playerScore, cpuScore);

    return winner;
}


//------------------------------------------------------------------------------
// GetPlayerScore - Accessor for ScoreManager's playerScore member.
//------------------------------------------------------------------------------
int ScoreManager::GetPlayerScore(void)
{
    return playerScore;
}


//------------------------------------------------------------------------------
// GetCPUScore - Accessor for ScoreManager's cpuScore member.
//------------------------------------------------------------------------------
int ScoreManager::GetCPUScore(void)
{
    return cpuScore;
}


//------------------------------------------------------------------------------
// GetValue - Helper for CreateDeclaration to return the value.
//------------------------------------------------------------------------------
int ScoreManager::GetValue(State phase, std::vector<Card*> cards)
{
    int value = 0;
    Card::Rank highestCard;

    switch ( phase )
    {
        case POINT:
            // Set the value for draws (total value).
            for ( int i = 0; i < (int)cards.size(); i++ )
            {
                value += cards[i]->GetValue();
            }
            break;

        case SEQUENCE:
        case SET:
            highestCard = cards[0]->GetRank();
            value       = highestCard;

            // Set the value for draws (highest card).
            for ( int i = 1; i < (int)cards.size(); i++ )
            {
                if ( cards[i]->GetRank() > highestCard )
                {
                    highestCard = cards[i]->GetRank();
                    value       = highestCard;
                }
            }
            break;

        default:
            break;
    }

    return value;
}


//------------------------------------------------------------------------------
// GetDeclaration - Helper for CreateDeclaration to return the Declaration text.
//------------------------------------------------------------------------------
void ScoreManager::GetDeclaration(State phase, int numCards)
{
    const char* seqNames[6] = { "TIERCE",  "QUARTE",   "QUINTE",
                                "SIXIÉME", "SEPTIÉME", "HUITIÉME" };
    const char* setNames[2] = { "TRIO", "QUATORZE" };

    switch ( phase )
    {
        case POINT:
            snprintf(declaration->declaration, 20, "POINT OF %d", numCards);
            break;

        case SEQUENCE:
            snprintf(declaration->declaration, 20, "%s", seqNames[numCards-3]);
            break;

        case SET:
            snprintf(declaration->declaration, 20, "%s", setNames[numCards-3]);
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// GetResponse - Helper for CreateDeclaration to return the Response text.
//------------------------------------------------------------------------------
void ScoreManager::GetResponse(State phase, int value)
{
    const char* cards[8] = { "SEVEN", "EIGHT", "NINE", "TEN",
                             "JACK", "QUEEN", "KING", "ACE" };

    switch ( phase )
    {
        case POINT:
            snprintf(declaration->response, 20, "MAKING %d", value);
            break;

        case SEQUENCE:
            snprintf(declaration->response, 20, "TO THE %s", cards[value-7]);
            break;

        case SET:
            snprintf(declaration->response, 20, "%s's", cards[value-7]);
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// ScoreCarteBlanche - Apply the Carte Blanche score.
//------------------------------------------------------------------------------
void ScoreManager::ScoreCarteBlanche(void)
{
    if ( declarationResults->carteBlancheWinner == PLAYER1 )
        playerScore += 10;
    else
        cpuScore += 10;

    // Update the score table.
    emit UpdateScores(playerScore, cpuScore);
}
