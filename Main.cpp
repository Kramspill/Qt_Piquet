#include <QApplication>
#include "Managers/GameManager.h"

int main(int argc, char *argv[])
{
    // Manages the GUI application's control flow and main settings.
    // For any GUI application using Qt, there is precisely one QApplication object.
    QApplication piquetGame(argc, argv);

    // Manages all other managers in the application.
    GameManager* gameManager = new GameManager;
    gameManager->Initialize();

    // Execute the application.
    return piquetGame.exec();
}
