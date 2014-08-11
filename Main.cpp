//------------------------------------------------------------------------------
// Filename: Main.cpp
// Description: Entry point for the application.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QApplication>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Managers/GameManager.h"


//------------------------------------------------------------------------------
// main - Entry point for the application.
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // Manages the GUI application's control flow and main settings.
    // For any GUI application using Qt, there is precisely one
    // QApplication object.
    QApplication piquetGame(argc, argv);

    // Top layer manager that starts off the initialization process.
    GameManager* gameManager = new GameManager();
    gameManager->Initialize();

    // Execute the application.
    return piquetGame.exec();
}
