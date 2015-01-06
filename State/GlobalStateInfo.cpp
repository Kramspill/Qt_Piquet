//------------------------------------------------------------------------------
// Filename: GlobalStateInfo.cpp
// Description: Holds global variables relating to the state of the game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "GlobalStateInfo.h"


//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------
PlayerNum           elder;
PlayerNum           younger;
PlayerNum           trickWinner;
Declaration*        declaration;
Declaration*        pointDeclaration;
Declaration*        seqDeclaration ;
Declaration*        setDeclaration;
Response*           response;
DeclarationResults* declarationResults;
TrickResults*       trickResults;
SpecialScores*      specialScores;
PartieResults*      partieResults;
State               currentPhase;
