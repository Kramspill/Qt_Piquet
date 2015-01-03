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

}


//------------------------------------------------------------------------------
// CreateDeclaration - Create a Declaration from a selection.
//------------------------------------------------------------------------------
void ScoreManager::CreateDeclaration(std::vector<Card*> cards, State phase)
{
    Declaration d;
    d.value = 0;

    // Check if player just skipped.
    if ( cards.size() != 0 )
    {
        // Set the number of cards.
        d.numCards    = cards.size();

        // Set the value.
        d.value       = GetValue(cards, phase);

        // Set the declaration text.
        GetDeclaration(cards, phase, d.declaration);
        GetResponse(cards, phase, d.response);

        d.notSkipped = true;

        switch ( phase )
        {
            case POINT:
                d.score = d.numCards;
                break;

            case SEQUENCE:
                d.score = (d.numCards < 5) ? d.numCards : d.numCards + 10;
                break;

            case SET:
                d.score = (d.numCards == 3) ? 3 : 14;
                break;
        }
    }
    else
    {
        d.notSkipped = false;
    }

    declaration->declaration = d.declaration;
    declaration->response = d.response;
    declaration->numCards = d.numCards;
    declaration->value = d.value;
    declaration->score = d.score;
    declaration->notSkipped = d.notSkipped;
}


//------------------------------------------------------------------------------
// CreateResponse - Create a Response from a selection.
//------------------------------------------------------------------------------
void ScoreManager::CreateResponse(std::vector<Card*> cards, State phase)
{
    Response r;
    r.value    = 0;
    r.numCards = 0;
    r.score    = 0;

    // Check if player responded 'Not Good'.
    if ( cards.size() >= declaration->numCards )
    {
        // Set the number of cards.
        r.numCards    = cards.size();

        // Set the value.
        r.value       = GetValue(cards, phase);

        switch ( phase )
        {
            case POINT:
                r.score = r.numCards;
                break;

            case SEQUENCE:
                r.score = (r.numCards < 5) ? r.numCards : r.numCards + 10;
                break;

            case SET:
                r.score = (r.numCards == 3) ? 3 : 14;
                break;
        }

        // Compare the scores to determine the exact response.
        if ( r.numCards > declaration->numCards )
        {
            r.good        = false;
            r.even        = false;
            r.hasQuestion = false;
        }
        else
        {
            r.hasQuestion = true;

            if ( r.value > declaration->value )
            {
                r.good = false;
                r.even = false;
            }
            else
            {
                if ( r.value == declaration->value )
                {
                    r.good = false;
                    r.even = true;
                }
                else
                {
                    r.good = true;
                    r.even = false;
                }
            }
        }
    }
    else
    {
        r.good        = true;
        r.even        = false;
        r.hasQuestion = false;
    }

    response->good = r.good;
    response->even = r.even;
    response->hasQuestion = r.hasQuestion;
    response->numCards = r.numCards;
    response->value = r.value;
    response->score = r.score;
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
                                playerScore += 60;
                                snprintf(str, 20, "PLAYER 2: REPIQUE");
                                emit UpdateLog(str);
                            }
                            break;

                        case SET:
                            if ( declarationResults->pointWinner != PLAYER1 &&
                                 declarationResults->sequenceWinner != PLAYER1 )
                            {
                                specialScores->repiqueScored = true;
                                playerScore += 60;
                                snprintf(str, 20, "PLAYER 2: REPIQUE");
                                emit UpdateLog(str);
                            }
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
    PlayerNum winner;

    if ( !leadCard && !followCard )
    {
        (player == PLAYER1) ? playerScore++ : cpuScore++;
    }
    else if ( leadCard->GetSuit() == followCard->GetSuit() &&
         leadCard->GetRank() <  followCard->GetRank() )
    {
        (player == PLAYER1) ? playerScore++ : cpuScore++;
        (player == PLAYER1) ? trickResults->player1Wins++ : trickResults->player2Wins++;
        winner = player;
    }
    else
    {
        (player == PLAYER1) ? trickResults->player2Wins++ : trickResults->player1Wins++;
        winner = (player == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    // Check for special case Pique.
    if ( !specialScores->repiqueScored && !specialScores->piqueScored )
    {
        if ( playerScore >= 30 && cpuScore == 0 ||
             cpuScore >= 30 && playerScore == 0 )
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
        (winner == PLAYER1) ? playerScore++ : cpuScore++;

        // Final check for Pique.
        if ( !specialScores->repiqueScored &&
             !specialScores->piqueScored )
        {
            char* str = new char[20];
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
            delete[] str;
        }

        char* str = new char[20];

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
        }

        emit UpdateLog(str);

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
int ScoreManager::GetValue(std::vector<Card*> cards, State phase)
{
    int value = 0;
    Card::Rank highestCard;

    switch ( phase )
    {
        case POINT:
            // Set the value for draws (total value).
            for ( int i = 0; i < cards.size(); i++ )
            {
                value += cards[i]->GetValue();
            }
            break;

        case SEQUENCE:
        case SET:
            highestCard = cards[0]->GetRank();
            value       = highestCard;

            // Set the value for draws (highest card).
            for ( int i = 1; i < cards.size(); i++ )
            {
                if ( cards[i]->GetRank() > highestCard )
                {
                    highestCard = cards[i]->GetRank();
                    value       = highestCard;
                }
            }
            break;
    }

    return value;
}


//------------------------------------------------------------------------------
// GetDeclaration - Helper for CreateDeclaration to return the Declaration text.
//------------------------------------------------------------------------------
void ScoreManager::GetDeclaration(std::vector<Card*> cards,
                                  State              phase,
                                  char*              destBuf)
{
    char* seqNames[6] = { "TIERCE",  "QUARTE",   "QUINTE",
                          "SIXIÉME", "SEPTIÉME", "HUITIÉME" };
    char* setNames[2] = { "TRIO", "QUATORZE" };

    switch ( phase )
    {
        case POINT:
            snprintf(destBuf, 20, "POINT OF %d", cards.size());
            break;

        case SEQUENCE:
            snprintf(destBuf, 20, "%s", seqNames[cards.size()-3]);
            break;

        case SET:
            snprintf(destBuf, 20, "%s", setNames[cards.size()-3]);
            break;
    }
}


//------------------------------------------------------------------------------
// GetResponse - Helper for CreateDeclaration to return the Response text.
//------------------------------------------------------------------------------
void ScoreManager::GetResponse(std::vector<Card*> cards,
                               State              phase,
                               char*              destBuf)
{
    int   value        = GetValue(cards, phase);
    char* cardNames[8] = { "SEVEN", "EIGHT", "NINE", "TEN",
                           "JACK", "QUEEN", "KING", "ACE" };

    switch ( phase )
    {
        case POINT:
            snprintf(destBuf, 20, "MAKING %d", value);
            break;

        case SEQUENCE:
            snprintf(destBuf, 20, "TO THE %s", cardNames[value-7]);
            break;

        case SET:
            snprintf(destBuf, 20, "%s's", cardNames[value-7]);
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
