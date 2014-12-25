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
    TRICK
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
    PlayerNum pointWinner;
    PlayerNum sequenceWinner;
    PlayerNum setWinner;
};

extern PlayerNum           elder;
extern PlayerNum           younger;
extern PlayerNum           trickWinner;
extern Declaration*        declaration;
extern Response*           response;
extern DeclarationResults* declarationResults;
extern State               currentPhase;

#endif // GLOBALSTATEINFO_H
