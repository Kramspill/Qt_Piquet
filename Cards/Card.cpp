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
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void Card::Destroy(void)
{
    delete renderer;                renderer              = 0;
    delete transitionAnimation;     transitionAnimation   = 0;
    delete inDeckState;             inDeckState           = 0;
    delete inTalonState;            inTalonState          = 0;
    delete inPlayerHandState;       inPlayerHandState     = 0;
    delete inCpuHandState;          inCpuHandState        = 0;
    delete inPlayerDiscardsState;   inPlayerDiscardsState = 0;
    delete inCpuDiscardsState;      inCpuDiscardsState    = 0;
    delete inPlayerTrickState;      inPlayerTrickState    = 0;
    delete inCpuTrickState;         inCpuTrickState       = 0;
    delete inPreviousTricksState;   inPreviousTricksState = 0;
    delete stateMachine;            stateMachine          = 0;
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
// SetSuit - Set the cards suit member.
//------------------------------------------------------------------------------
void Card::SetSuit(Card::Suit newSuit)
{
    suit = newSuit;
}


//------------------------------------------------------------------------------
// SetRank - Set the cards rank member.
//------------------------------------------------------------------------------
void Card::SetRank(Card::Rank newRank)
{
    rank = newRank;
}


//------------------------------------------------------------------------------
// UpdateSelection - Update the position of the card based on it's selection
//                   status.
//------------------------------------------------------------------------------
void Card::UpdateSelection(void)
{
    if ( this->isSelected() )
    {
        origPosition = position;
        position.setY(position.y() - 30);
    }
    else
    {
        position.setY(origPosition.y());
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

    position     = newPosition;
    origPosition = position;
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
// mousePressEvent - Handle mouse press events.
//------------------------------------------------------------------------------
void Card::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if ( isEnabled() && (flags() & QGraphicsItem::ItemIsSelectable))
    {
        setSelected(!isSelected());
        UpdateSelection();
    }
}


//------------------------------------------------------------------------------
// mouseReleaseEvent - Handle mouse release events.
//------------------------------------------------------------------------------
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if ( this->flags() & QGraphicsItem::ItemIsMovable )
    {
        UpdateAnimation(false);
        QGraphicsItem::mouseReleaseEvent(event);
    }
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
    inDeckState           = new InDeckState();
    inTalonState          = new InTalonState();
    inPlayerHandState     = new InPlayerHandState();
    inCpuHandState        = new InCpuHandState();
    inPlayerDiscardsState = new InPlayerDiscardsState();
    inCpuDiscardsState    = new InCpuDiscardsState();
    inPlayerTrickState    = new InPlayerTrickState();
    inCpuTrickState       = new InCpuTrickState();
    inPreviousTricksState = new InPreviousTricksState();

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
    inTalonState->addTransition(this, SIGNAL(InDeck()),    inDeckState);


    // Setup the transitions from the InPlayerHand state.
    inPlayerHandState->addTransition(this, SIGNAL(InPlayerDiscards()),
                                     inPlayerDiscardsState);
    inPlayerHandState->addTransition(this, SIGNAL(InPlayerTrick()),
                                     inPlayerTrickState);
    inPlayerHandState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InCpuHand state.
    inCpuHandState->addTransition(this, SIGNAL(InCpuDiscards()),
                                  inCpuDiscardsState);
    inCpuHandState->addTransition(this, SIGNAL(InCpuTrick()),
                                  inCpuTrickState);
    inCpuHandState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InPlayerDiscards state.
    inPlayerDiscardsState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InCpuDiscards state.
    inCpuDiscardsState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InPlayerTrick state.
    inPlayerTrickState->addTransition(this, SIGNAL(InPlayerHand()),
                                       inPlayerHandState);
    inPlayerTrickState->addTransition(this, SIGNAL(InPreviousTricks()),
                                      inPreviousTricksState);
    inPlayerTrickState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InCpuTrick state.
    inCpuTrickState->addTransition(this, SIGNAL(InCpuHand()),
                                   inCpuHandState);
    inCpuTrickState->addTransition(this, SIGNAL(InPreviousTricks()),
                                   inPreviousTricksState);
    inCpuTrickState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Setup the transitions from the InPreviousTricks state.
    inPreviousTricksState->addTransition(this, SIGNAL(InDeck()), inDeckState);

    // Link the card to the signals from CardStates.
    connect(inPlayerHandState,     SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inPlayerHandState,     SIGNAL(exited()),  this, SLOT(FlipCard()));
    connect(inPlayerTrickState,    SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inPlayerTrickState,    SIGNAL(exited()),  this, SLOT(FlipCard()));
    connect(inCpuTrickState,       SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inCpuTrickState,       SIGNAL(exited()),  this, SLOT(FlipCard()));
    connect(inPreviousTricksState, SIGNAL(entered()), this, SLOT(Display()));
    connect(inPreviousTricksState, SIGNAL(exited()),  this, SLOT(Display()));
    connect(inPlayerDiscardsState, SIGNAL(entered()), this, SLOT(FlipCard()));
    connect(inPlayerDiscardsState, SIGNAL(exited()),  this, SLOT(FlipCard()));

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


//------------------------------------------------------------------------------
// FlipCard - Flip the card and resize for display purposes.
//------------------------------------------------------------------------------
void Card::Display(void)
{
    // Flip the card.
    FlipCard();

    // If the card is now facedown, it is leaving a display cardArray so we
    // correct the resize, else we apply a resize.
    if ( facedown )
        this->setScale(0.5);
    else
        this->setScale(0.35);
}
