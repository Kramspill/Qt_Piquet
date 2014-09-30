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
void Dialog::Initialize(DialogType dialogType)
{
    // Set the dialog to be the specified type.
    type = dialogType;

    // Initialize the layout.
    layout = new QGridLayout();

    // Set the title of the dialog.
    SetDialogTitle();

    // Initialize the message.
    SetInitialMessage();

    // Initialize the buttons that will appear on the dialog.
    InitializeButtons();

    // Set the dialog's layout and size.
    setLayout(layout);
    setFixedHeight(sizeHint().height());

    // Remove the help button in the top right corner of the dialog and the
    // default close button.
    setWindowFlags(windowFlags() &
                   (~Qt::WindowContextHelpButtonHint &
                    ~Qt::WindowCloseButtonHint));
}


//------------------------------------------------------------------------------
// InitializeButtons - Initialize the buttons that will appear on the dialog.
//------------------------------------------------------------------------------
void Dialog::InitializeButtons(void)
{
    QPushButton* acceptButton;
    QPushButton* rejectButton;

    switch ( type )
    {
        case DEAL:
            // Allocate space for the new button.
            acceptButton = new QPushButton();

            // Set the properties of the button.
            acceptButton->setText("Deal");
            acceptButton->setDefault(true);
            connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

            // Add the button to the layout and button vector.
            layout->addWidget(acceptButton);
            buttons.push_back(acceptButton);
            break;

        case EXCHANGE:
            break;

        case DECLARE:
            break;

        case PASS:
            break;

        case GOOD:
            break;

        case NOTGOOD:
            break;

        case OK:
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// SetDialogTitle - Sets the dialog's title.
//------------------------------------------------------------------------------
void Dialog::SetDialogTitle(void)
{
    char* msg;

    switch ( type )
    {
        case DEAL:
            msg = "Deal the cards to the players.";
            message = new QTextEdit(msg);
            break;

        case EXCHANGE:
            break;

        case DECLARE:
            break;

        case PASS:
            break;

        case GOOD:
            break;

        case NOTGOOD:
            break;

        case OK:
            break;

        default:
            break;
    }

    // Set the message to read only and add it to the layout.
    message->setReadOnly(true);
    layout->addWidget(message);
}


//------------------------------------------------------------------------------
// SetInitialMessage - Sets the dialog's initial message.
//------------------------------------------------------------------------------
void Dialog::SetInitialMessage(void)
{
    switch ( type )
    {
        case DEAL:
            setWindowTitle("Deal Phase");
            break;

        case EXCHANGE:
            break;

        case DECLARE:
            break;

        case PASS:
            break;

        case GOOD:
            break;

        case NOTGOOD:
            break;

        case OK:
            break;

        default:
            break;
    }
}
