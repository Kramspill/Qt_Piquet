#include "WindowManager.h"

// Constructor.
WindowManager::WindowManager(void)
{
}

// Copy Constructor.
WindowManager::WindowManager(WindowManager&)
{
}

// Destructor.
WindowManager::~WindowManager(void)
{
}

// Initialize and display the main window.
void WindowManager::Initialize(void)
{
    mainWindow = new MainWindow;
    mainWindow->show();
}
