#include "Card.h"

// Default Constructor.
Card::Card(void)
{
}

// Constructor.
Card::Card(const QString& svgFileName, Suit theSuit, Value theValue) :
    QGraphicsSvgItem(svgFileName),
    backImage(new QGraphicsSvgItem(":/Cards/Back/Resources/Back/Red_Back.svg")),
    suit(theSuit),
    value(theValue)
{
    // This'll probably be removed and get explicitely called.
    Initialize();
}

// Copy Constructor.
Card::Card(Card&) : QGraphicsSvgItem()
{
}

// Destructor.
Card::~Card(void)
{
}

void Card::Initialize(void)
{
    // Initialize the transition animation associated with a Card
    // moving from one place to another.
    transitionAnimation = new QPropertyAnimation(this, "pos");

    // Setup the internal state machine of the Card.
    stateMachine = new QStateMachine();

    // Initialize the various states that a Card can be in.
    InDeckState*           inDeckState           = new InDeckState(stateMachine);
    InPlayerHandState*     inPlayerHandState     = new InPlayerHandState(stateMachine);
    InCpuHandState*        inCpuHandState        = new InCpuHandState(stateMachine);
    InTalonState*          inTalonState          = new InTalonState(stateMachine);
    InPlayerDiscardsState* inPlayerDiscardsState = new InPlayerDiscardsState(stateMachine);
    InCpuDiscardsState*    inCpuDiscardsState    = new InCpuDiscardsState(stateMachine);
    InCurrentTrickState*   inCurrentTrickState   = new InCurrentTrickState(stateMachine);
    InPreviousTricksState* inPreviousTricksState = new InPreviousTricksState(stateMachine);

    // Connect the signals to the slot function calls for automatic animation updates.
    connect(this, SIGNAL(CardMoved()), this, SLOT(UpdateAnimation()));

    // Setup the transitions from the InDeck state.
    inDeckState->addTransition(this, SIGNAL(InPlayerHand()), inPlayerHandState);
    inDeckState->addTransition(this, SIGNAL(InCpuHand()),    inCpuHandState);
    inDeckState->addTransition(this, SIGNAL(InTalon()),      inTalonState);

    /*
    // Setup the transitions from the InPlayerHand state.
    inPlayerHandState->addTransition(SomeObject, SIGNAL(inPlayerDiscards()), inPlayerDiscardsState);
    inPlayerHandState->addTransition(SomeObject, SIGNAL(inCurrentTrick()), inCurrentTrickState);

    // Setup the transitions from the InCpuHand state.
    inCpuHandState->addTransition(SomeObject, SIGNAL(inCpuDiscards()), inPlayerCpuState);
    inCpuHandState->addTransition(SomeObject, SIGNAL(inCurrentTrick()), inCurrentTrickState);

    // Setup the transitions from the InTalon state.
    inTalonState->addTransition(SomeObject, SIGNAL(inPlayerHand()), inPlayerHandState);
    inTalonState->addTransition(SomeObject, SIGNAL(inCpuHand()), inCpuHandState);
    inTalonState->addTransition(SomeObject, SIGNAL(inDeck()), inDeckState);

    // Setup the transitions from the InPlayerDiscards state.
    inPlayerDiscardsState->addTransition(SomeObject, SIGNAL(inDeck()), inDeckState);

    // Setup the transitions from the InCpuDiscards state.
    inCpuDiscardsState->addTransition(SomeObject, SIGNAL(inDeck()), inDeckState);

    // Setup the transitions from the InCurrentTrick state.
    inCurrentTrickState->addTransition(SomeObject, SIGNAL(inPreviousTricks()), inPreviousTricksState);

    // Setup the transitions from the InPreviousTricks state.
    inPreviousTricksState->addTransition(SomeObject, SIGNAL(inDeck()), inDeckState);
    */
}

// Accessor for Card's suit member.
Card::Suit Card::GetSuit(void)
{
    return suit;
}

// Accessor for Card's value member.
Card::Value Card::GetValue(void)
{
    return value;
}

void Card::SetPosition(QPointF newPosition)
{
    position = newPosition;
}

void Card::UpdateAnimation(void)
{
    transitionAnimation->setDuration(100);
    transitionAnimation->setEndValue(position);
    transitionAnimation->start();
}

// Accessor for Card's backImage member.
QGraphicsSvgItem* Card::GetBackImage(void)
{
    return backImage;
}
