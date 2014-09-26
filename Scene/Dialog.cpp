//------------------------------------------------------------------------------
// Filename: Dialog.cpp
// Description: Represents a dialog for communication and interaction.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Dialog.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
Dialog::Dialog(Dialog&) :
    QDialog()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Dialog::~Dialog(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the contents of this dialog.
//------------------------------------------------------------------------------
void Dialog::Initialize(char* title, char* msg, int numOfBtns,
                        ButtonType* buttonTypes)
{
    // Set the title of the dialog.
    setWindowTitle(title);

    // Initialize the message and set to read only.
    message = new QTextEdit(msg);
    message->setReadOnly(true);

    layout = new QGridLayout();
    layout->addWidget(message);

    setLayout(layout);
    setFixedHeight(sizeHint().height());

    // Remove the help button in the top right corner of the dialog.
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}
