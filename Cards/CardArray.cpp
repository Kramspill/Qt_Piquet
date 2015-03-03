//------------------------------------------------------------------------------
// Filename: CardArray.cpp
// Description: Represents an array of cards (stored as a vector).
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "CardArray.h"


//------------------------------------------------------------------------------
// Default Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(void)
{
}


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(CardArray::Type arrayType, int x, int y) :
    cards(0),
    type(arrayType),
    initialCardPosition(QPointF(x, y)),
    nextCardPosition(QPointF(x, y))
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardArray::CardArray(CardArray&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardArray::~CardArray(void)
{
}


//------------------------------------------------------------------------------
// Destroy - Free up the memory associated with an object of this type.
//------------------------------------------------------------------------------
void CardArray::Destroy(void)
{
    Card* card;

    while ( cards.size() > 0 )
    {
        card = cards.back();

        // Remove the card.
        cards.pop_back();

        // Free the memory.
        card->Destroy();
        delete card;
    }

    card = 0;
}


//------------------------------------------------------------------------------
// AddCard - Add a card to the CardArray.
//------------------------------------------------------------------------------
void CardArray::AddCard(Card* newCard, bool initialCardCreation, bool doNothing)
{
    // Add the new card to the array.
    cards.push_back(newCard);

    if ( type == CPUHAND || type == PLAYERHAND )
        Sort();

    // Update the position and state of the cards.
    if ( !doNothing )
        UpdateCardPositions(newCard, initialCardCreation);
}


//------------------------------------------------------------------------------
// RemoveCard - Remove a given card from this array. Doesn't free the memory
//              associated with the card.
//------------------------------------------------------------------------------
void CardArray::RemoveCard(Card* aCard, bool doNothing)
{
    std::vector<Card*>::iterator iterator;

    // Locate the card and remove it.
    iterator = std::find(cards.begin(), cards.end(), aCard);
    cards.erase(iterator);

    if ( !doNothing )
        UpdateCardPositions();
}


//------------------------------------------------------------------------------
// RemoveTopCard - Remove the last card from this array. Doesn't free the memory
//                 associated with the card but instead returns a pointer to the
//                 removed Card.
//------------------------------------------------------------------------------
Card* CardArray::RemoveTopCard(void)
{
    Card* removedCard = 0;

    // Make sure there are cards in the array
    // and a card exists at the given index.
    if ( cards.size() > 0 )
    {
        removedCard = cards.back();

        // Remove the card.
        cards.pop_back();

        // Clean up the card array and update the next card position.
        UpdateCardPositions();
    }

    return removedCard;
}


//------------------------------------------------------------------------------
// GetCard - Return a card from this CardArray at the given index.
//------------------------------------------------------------------------------
Card* CardArray::GetCard(int index)
{
    return cards[index];
}


//------------------------------------------------------------------------------
// Shuffle - Randomize this CardArray.
//------------------------------------------------------------------------------
void CardArray::Shuffle(void)
{
    // Shuffle the cards.
    std::srand(std::time(0));
    std::random_shuffle(cards.begin(), cards.end());

    ResetZPositions();
}


//------------------------------------------------------------------------------
// Sort - Sort this CardArray.
//------------------------------------------------------------------------------
void CardArray::Sort(void)
{
    std::sort(cards.begin(), cards.end(), CardSort);
    ResetZPositions();
}


//------------------------------------------------------------------------------
// Stagger - Visually stagger the cards in this CardArray.
//------------------------------------------------------------------------------
void CardArray::Stagger(CardArray::StaggerType staggerType)
{
    QPointF newPosition;
    Card*   card;
    int     arraySize = GetSize();

    switch ( staggerType )
    {
        case NOSTAGGER:
            newPosition = QPointF(nextCardPosition.x(),
                                  nextCardPosition.y() + (GetSize() + 1));

            for ( int index = 0; index < arraySize; index++ )
            {
                card = GetCard(index);

                card->SetPosition(newPosition);
                UpdateCardState(card, true);
            }
            break;

        case DECKSTAGGER:
            for ( int index = 0; index < arraySize; index++ )
            {
                card = GetCard(index);

                newPosition = card->GetPosition();
                newPosition.setY(newPosition.y() - index);

                card->SetPosition(newPosition);
                UpdateCardState(card, true);
            }
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// GetSize - Return the size of the cards vector.
//------------------------------------------------------------------------------
int CardArray::GetSize(void)
{
    return cards.size();
}


//------------------------------------------------------------------------------
// GetType - Accessor for CardArray's Type member variable.
//------------------------------------------------------------------------------
CardArray::Type CardArray::GetType(void)
{
    return type;
}


//------------------------------------------------------------------------------
// UpdateCardPositions - Update the positions of the cards in the array.
//------------------------------------------------------------------------------
void CardArray::UpdateCardPositions(Card* addedCard, bool noAnimation)
{
    bool newCardAdded = false;

    // If a new card has been added, set it's position and state.
    if ( addedCard )
    {
        addedCard->SetPosition(nextCardPosition, GetSize());
        UpdateCardState(addedCard, noAnimation);
        newCardAdded = true;
    }

    // Clean up the positions of the cards and update the next card's position.
    CleanUpCardPositions(newCardAdded);
}


//------------------------------------------------------------------------------
// CleanUpCardPositions - Clean up the positions of the cards and update the
//                        next card's position.
//------------------------------------------------------------------------------
void CardArray::CleanUpCardPositions(bool newCardAdded)
{
    Card*   card;
    QPointF shiftedPosition;
    int     arraySize = GetSize();

    switch ( type )
    {
        case DECK:
        case TALON:
            if ( newCardAdded )
            {
                nextCardPosition = QPointF(nextCardPosition.x(),
                                           nextCardPosition.y() - 1);
            }
            else
            {
                nextCardPosition = QPointF(nextCardPosition.x(),
                                           nextCardPosition.y() + 1);
            }
            break;

        case CPUDISCARDS:
        case PLAYERDISCARDS:
        case PREVIOUSTRICKS:
            if ( arraySize > 0 )
            {
                // Loop through the array of cards and shift them.
                for ( int index = 0; index < arraySize; index++ )
                {
                    card = GetCard(index);

                    // Get the original position of the card and shift it.
                    shiftedPosition.setX(card->GetPosition().x());
                    shiftedPosition.setY(card->GetPosition().y());

                    // Set the new position of the card.
                    card->SetPosition(shiftedPosition, index + 1);

                    // Update the card's animation.
                    card->UpdateAnimation(false);
                }

                // Update the position of the next card.
                if ( type == PLAYERDISCARDS || type == CPUDISCARDS )
                    nextCardPosition = QPointF(shiftedPosition.x(),
                                               shiftedPosition.y()+40);
                else
                    nextCardPosition = QPointF(shiftedPosition.x(),
                                               shiftedPosition.y()+27);
            }
            else
            {
                nextCardPosition = initialCardPosition;
            }
            break;

        case PLAYERHAND:
            if ( arraySize > 0 )
            {
                // Loop through the array of cards and shift them.
                for ( int index = 0; index < arraySize; index++ )
                {
                    card = GetCard(index);

                    // Get the original position of the card and shift it.
                    shiftedPosition.setX(initialCardPosition.x() -
                                         (18*arraySize) + (index*40));
                    shiftedPosition.setY(card->GetPosition().y());

                    // Set the new position of the card.
                    card->SetPosition(shiftedPosition, index + 1);

                    // Update the card's animation.
                    card->UpdateAnimation(false);
                }

                // Update the position of the next card.
                nextCardPosition = QPointF(shiftedPosition.x() + 40,
                                           shiftedPosition.y());
            }
            else
            {
                nextCardPosition = initialCardPosition;
            }
            break;

        case CPUHAND:
            if ( arraySize > 0 )
            {
                // Loop through the array of cards and shift them.
                for ( int index = 0; index < arraySize; index++ )
                {
                    card = GetCard(index);

                    // Get the original position of the card and shift it.
                    shiftedPosition.setX(initialCardPosition.x() +
                                         (18*arraySize) - (index*40));
                    shiftedPosition.setY(card->GetPosition().y());

                    // Set the new position of the card.
                    card->SetPosition(shiftedPosition, arraySize - index);

                    // Update the card's animation.
                    card->UpdateAnimation(false);
                }

                // Update the position of the next card.
                nextCardPosition = QPointF(shiftedPosition.x() - 40,
                                           shiftedPosition.y());
            }
            else
            {
                nextCardPosition = initialCardPosition;
            }
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// UpdateCardState - Update the state and animation of a card.
//------------------------------------------------------------------------------
void CardArray::UpdateCardState(Card* card, bool noAnimation)
{
    // Update the card's animation regardless of where the card is going.
    card->UpdateAnimation(noAnimation);

    // Emit a signal to tell the card to change states.
    switch ( type )
    {
        case DECK:
            emit card->InDeck();
            break;

        case TALON:
            emit card->InTalon();
            break;

        case PLAYERHAND:
            emit card->InPlayerHand();
            break;

        case CPUHAND:
            emit card->InCpuHand();
            break;

        case PLAYERDISCARDS:
            emit card->InPlayerDiscards();
            break;

        case CPUDISCARDS:
            emit card->InCpuDiscards();
            break;

        case PLAYERTRICK:
            emit card->InPlayerTrick();
            break;

        case CPUTRICK:
            emit card->InCpuTrick();
            break;

        case PREVIOUSTRICKS:
            emit card->InPreviousTricks();
            break;

        default:
            break;
    }
}


//------------------------------------------------------------------------------
// ResetZPositions - Reset the zPositions in this array.
//------------------------------------------------------------------------------
void CardArray::ResetZPositions(void)
{
    Card* card;
    int   arraySize = GetSize();

    for ( int index = 0; index < arraySize; index++ )
    {
        card = GetCard(index);
        card->SetPosition(card->GetPosition(), index + 1);
    }
}


//------------------------------------------------------------------------------
// CardSort - Used to sort cards.
//------------------------------------------------------------------------------
bool CardSort(Card* i, Card* j)
{
    bool result = false;

    if ( i->GetSuit() < j->GetSuit() )
    {
        result = true;
    }
    else if ( i->GetSuit() == j->GetSuit() )
    {
        if ( i->GetRank() < j->GetRank() )
            result = true;
    }

    return result;
}
