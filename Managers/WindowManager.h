#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "AppWindows/MainWindow.h"

class WindowManager
{
public:
    WindowManager(void);
    WindowManager(WindowManager&);
    ~WindowManager(void);

    void Initialize(void);

private:
    MainWindow* mainWindow;
};

#endif // WINDOWMANAGER_H
