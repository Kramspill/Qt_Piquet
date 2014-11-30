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
Card::Card(const QString& svgFileName, Suit theSuit, Rank theRank) :
    QGraphicsSvgItem(svgFileName),
    frontImage(svgFileName),
    backImage(":/Cards/Back/Resources/Back/Red_Back.svg"),
    facedown(false),
    suit(theSuit),
    rank(theRank)
{
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
// GetSuit - Accessor for Card's suit member variable.
//------------------------------------------------------------------------------
Card::Suit Card::GetSuit(void)
{
    return suit;
}


//------------------------------------------------------------------------------
// GetRank - Accessor for Card's rank member variable.
//------------------------------------------------------------------------------
Card::Rank Card::GetRank(void)
{
    return rank;
}


//------------------------------------------------------------------------------
// GetValue - Accessor for Card's value member variable.
//------------------------------------------------------------------------------
int Card::GetValue(void)
{
    return value;
}


//------------------------------------------------------------------------------
// GetPosition - Mutator for Card's position member variable.
//------------------------------------------------------------------------------
QPointF Card::GetPosition(void)
{
    return position;
}


//------------------------------------------------------------------------------
// UpdateSelection - Update the position of the card based on it's selection
//                   status.
//------------------------------------------------------------------------------
void Card::UpdateSelection(void)
{
    if ( this->isSelected() )
    {
        position.setY(position.y() - 30);
    }
    else
    {
        position.setY(position.y() + 30);
    }

    UpdateAnimation(false);
}


//------------------------------------------------------------------------------
// SetPosition - Mutator for Card's position member variable.
//------------------------------------------------------------------------------
void Card::SetPosition(QPointF newPosition, int zPosition)
{
    if ( zPosition != -1 )
        this->setZValue(zPosition);

    position = newPosition;
}


//------------------------------------------------------------------------------
// UpdatePosition - Update the position of this Card's transitionAnimation.
//------------------------------------------------------------------------------
void Card::UpdateAnimation(bool noAnimation)
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
// mouseReleaseEvent - Handle mouse release events.
//------------------------------------------------------------------------------
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    UpdateAnimation(false);
}


//------------------------------------------------------------------------------
// Initialize - Initialize the states and transitions of a Card.
//------------------------------------------------------------------------------
void Card::Initialize(void)
{
    // Set the Point value of the card.
    SetValue();

    // Initialize the renderer and start the card facing down.
    renderer = new QSvgRenderer(backImage);
    this->setSharedRenderer(renderer);
    facedown = true;

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
    InPlayerTrickState*    inPlayerTrickState    = new InPlayerTrickState();
    InCpuTrickState*       inCpuTrickState       = new InCpuTrickState();
    InPreviousTricksState* inPreviousTricksState = new InPreviousTricksState();

    // Add the states to the state machine.
    stateMachine->addState(inDeckState);
    stateMachine->addState(inTalonState);
    stateMachine->addState(inPlayerHandState);
    stateMachine->addState(inCpuHandState);
    stateMachine->addState(inPlayerDiscardsState);
    stateMachine->addState(inCpuDiscardsState);
    stateMachine->addState(inPlayerTrickState);
    stateMachine->addState(inCpuTrickState);
    stateMachine->addState(inPreviousTricksState);

    // Set the initial state.
    stateMachine->setInitialState(inDeckState);

    // Setup the transitions from the InDeck state.
    inDeckState->addTransition(this, SIGNAL(InPlayerHand()), inPlayerHandState);
    inDeckState->addTransition(this, SIGNAL(InCpuHand()),    inCpuHandState);
    inDeckState->addTransition(this, SIGNAL(InTalon()),      inTalonState);

    // Setup the transitions from the InTalon state.
    inTalonState->addTransition(this, SIGNAL(InPlayerHand()),
                                inPlayerHandState);
    inTalonState->addTransition(this, SIGNAL(InCpuHand()), inCpuHandState);
    //inTalonState->addTransition(this, SIGNAL(InDeck()),    inDeckState);


    // Setup the transitions from the InPlayerHand state.
    inPlayerHandState->addTransition(this, SIGNAL(InPlayerDiscards()),
                                     inPlayerDiscardsState);
    inPlayerHandState->addTransition(this, SIGNAL(InPlayerTrick()),
                                     inPlayerTrickState);

    // Setup the transitions from the InCpuHand state.
    inCpuHandState->addTransition(this, SIGNAL(InCpuDiscards()),
                                  inCpuDiscardsState);
    inCpuHandState->addTransition(this, SIGNAL(InCpuTrick()),
                                  inCpuTrickState);
/*
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

    // Link the card to the signals from CardStates.
    connect(inPlayerHandState,  SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inPlayerHandState,  SIGNAL(exited()),  this, SLOT(FlipCard()));
    connect(inPlayerTrickState, SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inPlayerTrickState, SIGNAL(exited()),  this, SLOT(FlipCard()));
    connect(inCpuTrickState,    SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inCpuTrickState,    SIGNAL(exited()),  this, SLOT(FlipCard()));

    connect(inCpuHandState, SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inCpuHandState, SIGNAL(exited()), this, SLOT(FlipCard()));

    // Run the state machine.
    stateMachine->start();
}


//------------------------------------------------------------------------------
// SetValue - Set the point value of this card.
//------------------------------------------------------------------------------
void Card::SetValue(void)
{
    switch ( rank )
    {
        case SEVEN:
        case EIGHT:
        case NINE:
        case TEN:
            value = rank;
            break;

        case JACK:
        case QUEEN:
        case KING:
            value = 10;
            break;

        case ACE:
            value = 11;
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// FlipCard - Flip this card.
//------------------------------------------------------------------------------
void Card::FlipCard(void)
{
    if ( facedown )
        renderer->load(frontImage);
    else
        renderer->load(backImage);

    // Reset the renderer to update the change and update the facedown status.
    this->setSharedRenderer(renderer);
    facedown = !facedown;
}
