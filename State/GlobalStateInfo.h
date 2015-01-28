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
    ELDERSELECT,
    DEAL,
    EXCHANGE,
    POINT,
    SEQUENCE,
    SET,
    RESPOND,
    TRICK,
    SUMMARY,
    BLANCHE
};

struct Declaration
{
    char* declaration;
    char* response;
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
    PlayerNum carteBlancheWinner;
    PlayerNum pointWinner;
    PlayerNum sequenceWinner;
    PlayerNum setWinner;
};

struct TrickResults
{
    int player1Wins;
    int player2Wins;
};

struct SpecialScores
{
    bool carteBlancheScored;
    bool repiqueScored;
    bool piqueScored;
};

struct PartieResults
{
    int currentDeal;
    int deal[2][6];
};

extern PlayerNum           elder;
extern PlayerNum           younger;
extern PlayerNum           trickWinner;
extern Declaration*        declaration;
extern Declaration*        pointDeclaration;
extern Declaration*        seqDeclaration;
extern Declaration*        setDeclaration;
extern Response*           response;
extern DeclarationResults* declarationResults;
extern TrickResults*       trickResults;
extern SpecialScores*      specialScores;
extern PartieResults*      partieResults;
extern State               currentPhase;
extern bool                testingAi;

#endif // GLOBALSTATEINFO_H
