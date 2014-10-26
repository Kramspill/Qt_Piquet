//------------------------------------------------------------------------------
// Filename: InputDialog.cpp
// Description: The dialog used for user interaction.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "InputDialog.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
InputDialog::InputDialog(QGraphicsLayoutItem* parent) :
    QGraphicsGridLayout(parent)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
InputDialog::InputDialog(InputDialog&) :
    QGraphicsGridLayout()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
InputDialog::~InputDialog(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the contents of this dialog.
//------------------------------------------------------------------------------
void InputDialog::Initialize(void)
{
    dealButton     = new QGraphicsProxyWidget();
    exchangeButton = new QGraphicsProxyWidget();
    declareButton  = new QGraphicsProxyWidget();
    sinkButton     = new QGraphicsProxyWidget();

    dealButton->setWidget(new QPushButton("Deal"));
    exchangeButton->setWidget(new QPushButton("Exchange"));
    declareButton->setWidget(new QPushButton("Declare"));
    sinkButton->setWidget(new QPushButton("Sink"));

    this->addItem(dealButton,     0, 0);
    this->addItem(exchangeButton, 0, 1);
    this->addItem(declareButton,  1, 0);
    this->addItem(sinkButton,     1, 1);

    ConnectSignals();
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to/from this class.
//------------------------------------------------------------------------------
void InputDialog::ConnectSignals(void)
{
    connect(dealButton,     SIGNAL(clicked()), this, SIGNAL(ExecuteDeal()));
    connect(exchangeButton, SIGNAL(clicked()), this, SIGNAL(ExecutePlayerDiscard()));
}
