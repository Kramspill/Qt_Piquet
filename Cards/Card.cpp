//------------------------------------------------------------------------------
// Filename: Card.cpp
// Description: Represents a playing card that is used in this game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Card.h"


//------------------------------------------------------------------------------
// Default Constructor
//------------------------------------------------------------------------------
Card::Card(void)
{
}


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Card::Card(const QString& svgFileName, Suit theSuit, Value theValue) :
    QGraphicsSvgItem(svgFileName),
    backImage(new QGraphicsSvgItem(":/Cards/Back/Resources/Back/Red_Back.svg")),
    suit(theSuit),
    value(theValue)
{
    // This'll probably be removed and get explicitely called.
    Initialize();
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
Card::Card(Card&) :
    QGraphicsSvgItem()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Card::~Card(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the states and transitions of a Card.
//------------------------------------------------------------------------------
void Card::Initialize(void)
{
    // Initialize the transition animation associated with a Card
    // moving from one place to another.
    transitionAnimation = new QPropertyAnimation(this, "pos");

    // Setup the internal state machine of the Card.
    stateMachine        = new QStateMachine();

    // Initialize the various states that a Card can be in.
    InDeckState*           inDeckState           = new InDeckState();
    InTalonState*          inTalonState          = new InTalonState();
    InPlayerHandState*     inPlayerHandState     = new InPlayerHandState();
    InCpuHandState*        inCpuHandState        = new InCpuHandState();
    InPlayerDiscardsState* inPlayerDiscardsState = new InPlayerDiscardsState();
    InCpuDiscardsState*    inCpuDiscardsState    = new InCpuDiscardsState();
    InCurrentTrickState*   inCurrentTrickState   = new InCurrentTrickState();
    InPreviousTricksState* inPreviousTricksState = new InPreviousTricksState();

    // Add the states to the state machine.
    stateMachine->addState(inDeckState);
    stateMachine->addState(inTalonState);
    stateMachine->addState(inPlayerHandState);
    stateMachine->addState(inCpuHandState);
    stateMachine->addState(inPlayerDiscardsState);
    stateMachine->addState(inCpuDiscardsState);
    stateMachine->addState(inCurrentTrickState);
    stateMachine->addState(inPreviousTricksState);

    // Set the initial state.
    stateMachine->setInitialState(inDeckState);

    // Connect the signals to the slot function calls for automatic
    // animation updates.
    connect(this, SIGNAL(CardMoved(bool)), this, SLOT(UpdatePosition(bool)));

    // Setup the transitions from the InDeck state.
    inDeckState->addTransition(this, SIGNAL(InPlayerHand()), inPlayerHandState);
    inDeckState->addTransition(this, SIGNAL(InCpuHand()),    inCpuHandState);
    inDeckState->addTransition(this, SIGNAL(InTalon()),      inTalonState);

    /*
    // Setup the transitions from the InPlayerHand state.
    inPlayerHandState->addTransition(SomeObject, SIGNAL(inPlayerDiscards()),
                                     inPlayerDiscardsState);
    inPlayerHandState->addTransition(SomeObject, SIGNAL(inCurrentTrick()),
                                     inCurrentTrickState);

    // Setup the transitions from the InCpuHand state.
    inCpuHandState->addTransition(SomeObject, SIGNAL(inCpuDiscards()),
                                  inPlayerCpuState);
    inCpuHandState->addTransition(SomeObject, SIGNAL(inCurrentTrick()),
                                  inCurrentTrickState);

    // Setup the transitions from the InTalon state.
    inTalonState->addTransition(SomeObject, SIGNAL(inPlayerHand()),
                                inPlayerHandState);
    inTalonState->addTransition(SomeObject, SIGNAL(inCpuHand()),
                                inCpuHandState);
    inTalonState->addTransition(SomeObject, SIGNAL(inDeck()),
                                inDeckState);

    // Setup the transitions from the InPlayerDiscards state.
    inPlayerDiscardsState->addTransition(SomeObject, SIGNAL(inDeck()),
                                         inDeckState);

    // Setup the transitions from the InCpuDiscards state.
    inCpuDiscardsState->addTransition(SomeObject, SIGNAL(inDeck()),
                                      inDeckState);

    // Setup the transitions from the InCurrentTrick state.
    inCurrentTrickState->addTransition(SomeObject, SIGNAL(inPreviousTricks()),
                                       inPreviousTricksState);

    // Setup the transitions from the InPreviousTricks state.
    inPreviousTricksState->addTransition(SomeObject, SIGNAL(inDeck()),
                                         inDeckState);
    */
}


//------------------------------------------------------------------------------
// GetSuit - Accessor for Card's suit member variable.
//------------------------------------------------------------------------------
Card::Suit Card::GetSuit(void)
{
    return suit;
}


//------------------------------------------------------------------------------
// GetValue - Accessor for Card's value member variable.
//------------------------------------------------------------------------------
Card::Value Card::GetValue(void)
{
    return value;
}


//------------------------------------------------------------------------------
// SetPosition - Mutator for Card's position member variable.
//------------------------------------------------------------------------------
void Card::SetPosition(QPointF newPosition)
{
    position = newPosition;
}


//------------------------------------------------------------------------------
// UpdatePosition - Update the position of this Card's transitionAnimation.
//------------------------------------------------------------------------------
void Card::UpdatePosition(bool noAnimation)
{
    if ( noAnimation )
    {
        transitionAnimation->setDuration(0);
    }
    else
    {
        transitionAnimation->setDuration(100);
    }

    transitionAnimation->setEndValue(position);
    transitionAnimation->start();
}


//------------------------------------------------------------------------------
// GetBackImage - Accessor for Card's backImage member variable.
//------------------------------------------------------------------------------
QGraphicsSvgItem* Card::GetBackImage(void)
{
    return backImage;
}
