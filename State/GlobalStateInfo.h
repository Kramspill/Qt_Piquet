//------------------------------------------------------------------------------
// Filename: GlobalStateInfo.h
// Description: Header file for GlobalStateInfo.
//------------------------------------------------------------------------------

#ifndef GLOBALSTATEINFO_H
#define GLOBALSTATEINFO_H

//------------------------------------------------------------------------------
// Global Definitions
//------------------------------------------------------------------------------
enum PlayerNum
{
    PLAYER1 = 1,
    PLAYER2 = 2,
    NOPLAYER
};

enum State
{
    DEAL,
    EXCHANGE,
    POINT,
    SEQUENCE,
    SET,
    RESPOND,
    TRICK,
    BLANCHE
};

struct Declaration
{
    char* declaration = new char[20]; // REFACTOR
    char* response    = new char[20];
    int   numCards;
    int   value;
    int   score;
    bool  notSkipped;
};

struct Response
{
    bool good;
    bool even;
    bool hasQuestion;
    int  numCards;
    int  value;
    int  score;
};

struct DeclarationResults
{
    PlayerNum carteBlancheWinner = NOPLAYER;
    PlayerNum pointWinner;
    PlayerNum sequenceWinner;
    PlayerNum setWinner;
};

struct TrickResults
{
    int player1Wins = 0;
    int player2Wins = 0;
};

struct SpecialScores
{
    bool carteBlancheScored = false;
    bool repiqueScored = false;
    bool piqueScored   = false;
};

extern PlayerNum           elder;
extern PlayerNum           younger;
extern PlayerNum           trickWinner;
extern Declaration*        declaration;
extern Response*           response;
extern DeclarationResults* declarationResults;
extern TrickResults*       trickResults;
extern SpecialScores*      specialScores;
extern State               currentPhase;

#endif // GLOBALSTATEINFO_H
