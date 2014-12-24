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
PlayerNum           elder              = PLAYER1;
PlayerNum           younger            = PLAYER2;
Declaration*        declaration        = new Declaration();
Response*           response           = new Response();
DeclarationResults* declarationResults = new DeclarationResults();
State               currentPhase       = DEAL;
