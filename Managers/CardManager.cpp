//------------------------------------------------------------------------------
// Filename: CardManager.cpp
// Description: Manager for the cards used in this game.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "CardManager.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CardManager::CardManager(void)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
CardManager::CardManager(CardManager&) :
    QObject()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
CardManager::~CardManager(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the Cards and CardArrays held by this manager.
//------------------------------------------------------------------------------
void CardManager::Initialize(Scene* scene)
{
    // Allocate memory for member variables.
    deck           = new CardLayout(CardLayout::DECK);
    talon          = new CardLayout(CardLayout::TALON);
    playerHand     = new CardLayout(CardLayout::PLAYERHAND);
    cpuHand        = new CardLayout(CardLayout::CPUHAND);
    playerDiscards = new CardLayout(CardLayout::PLAYERDISCARDS);
    cpuDiscards    = new CardLayout(CardLayout::CPUDISCARDS);
    previousTricks = new CardLayout(CardLayout::PREVIOUSTRICKS);
    playerTrick    = new CardLayout(CardLayout::PLAYERTRICK);
    cpuTrick       = new CardLayout(CardLayout::CPUTRICK);

    // Add the card layouts to the appropriate area within the scene.
    AddLayoutsToScene(scene);

    // Initialize the timer to allow animation to finish before informing of
    // state changes.
    transitionTimer = new QTimer();
    transitionTimer->setSingleShot(true);

    // Initialize the member that keeps track of the number of cards transferred
    // from the most recent card transaction.
    numOfCardsTransferred = 0;

    // Connect signals to/from this class.
    ConnectSignals();

    // Initialize all the cards used in the game and add them to the deck.
    InitializeCards();

    // Shuffle the deck.
    ShuffleDeck();
}


//------------------------------------------------------------------------------
// TransferCards - Transfer cards between one CardArray and another.
//------------------------------------------------------------------------------
void CardManager::TransferCards(CardLayout* source, CardLayout* destination,
                                int numberOfCards)
{
    for (int index = 0; index < numberOfCards; index++)
    {
        // Remove the card from the source array, and add it to the destination.
        Card* card = source->RemoveCard();
        destination->AddCard(card);
    }

    // Update the number of cards transferred.
    numOfCardsTransferred = numberOfCards;

    // Delay the signal of transfer completion for animation purposes.
    transitionTimer->start(100);
}


//------------------------------------------------------------------------------
// TransferSelectedCards - Transfer a cardArray's selected cards to another
//                         CardArray.
//------------------------------------------------------------------------------
void CardManager::TransferSelectedCards(CardLayout* source,
                                        CardLayout* destination)
{
    int numberOfCards = 3;//source->GetSelectedCardsSize();

    if ( numberOfCards > 0 )
    {
        for (int index = 0; index < numberOfCards; index++)
        {
            // Remove the card from the source array, and add it to the
            // destination.
            //Card* card = source->RemoveSelectedCard();
            //destination->AddCard(card);
        }

        // Update the number of cards transferred.
        numOfCardsTransferred = numberOfCards;

        // Delay the signal of transfer completion for animation purposes.
        transitionTimer->start(100);
    }
}


//------------------------------------------------------------------------------
// GetDesiredCardLayout - Return the CardArray associated with a given type.
//------------------------------------------------------------------------------
CardLayout* CardManager::GetDesiredCardLayout(CardLayout::Type type)
{
    CardLayout* returnedArray = 0;

    switch ( type )
    {
        case CardLayout::DECK:
            returnedArray = deck;
            break;

        case CardLayout::TALON:
            returnedArray = talon;
            break;

        case CardLayout::PLAYERHAND:
            returnedArray = playerHand;
            break;

        case CardLayout::CPUHAND:
            returnedArray = cpuHand;
            break;

        case CardLayout::PLAYERDISCARDS:
            returnedArray = playerDiscards;
            break;

        case CardLayout::CPUDISCARDS:
            returnedArray = cpuDiscards;
            break;

        case CardLayout::PREVIOUSTRICKS:
            returnedArray = previousTricks;
            break;

        default:
            break;
    }

    return returnedArray;
}


//------------------------------------------------------------------------------
// GetSelectionScore - Get the score of the user's current selection.
//------------------------------------------------------------------------------
/*ScoreManager::PhaseScore CardManager::GetSelectionScore(
                                                CardLayout::SelectionType phase)
{
    return playerHand->GetSelectionScore(phase);
}*/


//------------------------------------------------------------------------------
// AddLayoutsToScene - Add the card layouts to the scene.
//------------------------------------------------------------------------------
void CardManager::AddLayoutsToScene(Scene* scene)
{
    scene->AddLayout(Scene::PLAYING, deck,           2, 4);
    scene->AddLayout(Scene::TALON,   talon,          1, 0);
    scene->AddLayout(Scene::PLAYER,  playerHand,     0, 0);
    scene->AddLayout(Scene::CPU,     cpuHand,        0, 0);
    scene->AddLayout(Scene::PLAYING, playerDiscards, 2, 6);
    scene->AddLayout(Scene::PLAYING, cpuDiscards,    0, 6);
    scene->AddLayout(Scene::PLAYING, previousTricks, 1, 0);
    scene->AddLayout(Scene::PLAYING, playerTrick,    2, 3);
    scene->AddLayout(Scene::PLAYING, cpuTrick,       0, 3);
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the various signals to/from this class.
//------------------------------------------------------------------------------
void CardManager::ConnectSignals(void)
{
    connect(transitionTimer, SIGNAL(timeout()), this,
            SLOT(SignalTransferComplete()));

    /*connect(playerHand, SIGNAL(SignalValidSelection()), this,
            SIGNAL(SignalValidSelection()));*/
}


//------------------------------------------------------------------------------
// InitializeCards - Create all the cards and add them to the deck.
//------------------------------------------------------------------------------
void CardManager::InitializeCards(void)
{
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/7C.svg",
                           Card::CLUBS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/8C.svg",
                           Card::CLUBS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/9C.svg",
                           Card::CLUBS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/10C.svg",
                           Card::CLUBS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/JC.svg",
                           Card::CLUBS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/QC.svg",
                           Card::CLUBS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/KC.svg",
                           Card::CLUBS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Clubs/Resources/Clubs/AC.svg",
                           Card::CLUBS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/7D.svg",
                           Card::DIAMONDS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/8D.svg",
                           Card::DIAMONDS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/9D.svg",
                           Card::DIAMONDS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/10D.svg",
                           Card::DIAMONDS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/JD.svg",
                           Card::DIAMONDS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/QD.svg",
                           Card::DIAMONDS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/KD.svg",
                           Card::DIAMONDS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Diamonds/Resources/Diamonds/AD.svg",
                           Card::DIAMONDS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/7H.svg",
                           Card::HEARTS, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/8H.svg",
                           Card::HEARTS, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/9H.svg",
                           Card::HEARTS, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/10H.svg",
                           Card::HEARTS, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/JH.svg",
                           Card::HEARTS, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/QH.svg",
                           Card::HEARTS, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/KH.svg",
                           Card::HEARTS, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Hearts/Resources/Hearts/AH.svg",
                           Card::HEARTS, Card::ACE), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/7S.svg",
                           Card::SPADES, Card::SEVEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/8S.svg",
                           Card::SPADES, Card::EIGHT), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/9S.svg",
                           Card::SPADES, Card::NINE), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/10S.svg",
                           Card::SPADES, Card::TEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/JS.svg",
                           Card::SPADES, Card::JACK), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/QS.svg",
                           Card::SPADES, Card::QUEEN), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/KS.svg",
                           Card::SPADES, Card::KING), true);
    deck->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                           Card::SPADES, Card::ACE), true);

    // TEST //
    /*talon->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                            Card::SPADES, Card::ACE), true);
    playerHand->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                                 Card::SPADES, Card::ACE), true);
    cpuHand->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                              Card::SPADES, Card::ACE), true);
    playerDiscards->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                                     Card::SPADES, Card::ACE), true);
    cpuDiscards->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                                  Card::SPADES, Card::ACE), true);
    previousTricks->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                                     Card::SPADES, Card::ACE), true);
    playerTrick->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                                  Card::SPADES, Card::ACE), true);
    cpuTrick->AddCard(new Card(":/Cards/Spades/Resources/Spades/AS.svg",
                               Card::SPADES, Card::ACE), true);*/
    //////////
}


//------------------------------------------------------------------------------
// ShuffleDeck - Shuffle the deck.
//------------------------------------------------------------------------------
void CardManager::ShuffleDeck(void)
{
    // Line up the cards in the deck before shuffling.
    //deck->Stagger(CardLayout::NOSTAGGER);
    deck->Shuffle();

    // Re-stagger the deck.
    //deck->Stagger(CardLayout::DECKSTAGGER);
}


//------------------------------------------------------------------------------
// SetCardsSelectable - Enable/Disable a CardArray's cards to be selected.
//------------------------------------------------------------------------------
void CardManager::SetCardsSelectable(bool setSelectable, int limit,
                                     CardLayout::Type type)
{
    Card*       card;
    CardLayout* cardArray = GetDesiredCardLayout(type);

    // Set the limit of how many cards can be selected at once.
    //cardArray->SetSelectionLimit(limit);

    // Loop through the array setting the ItemIsSelectable property.
    for ( int index = 0; index < cardArray->count(); index++ )
    {
        card = cardArray->itemAt(index);

        if ( setSelectable )
            card->setFlag(QGraphicsItem::ItemIsSelectable, true);
        else
            card->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}


//------------------------------------------------------------------------------
// CardSelectionsChanged - Inform the card and CardArray that it's selection has
//                         changed.
//------------------------------------------------------------------------------
void CardManager::CardSelectionsChanged(Card* card,
                                        CardLayout::Type type)
{
    CardLayout* cardArray = GetDesiredCardLayout(type);

    // Update the card selections array in the CardArray.
    /*if ( cardArray->UpdateCardSelections(card) )
    {
        // Update the position of the card based on if it's selected or not.
        card->UpdateSelection();
    }*/
}


//------------------------------------------------------------------------------
// CallCheckSelection - Check the selection in the CardArray is correct for
//                      the phase the game is in.
//------------------------------------------------------------------------------
/*bool CardManager::CheckSelection(CardLayout::SelectionType phase,
                                 CardLayout::Type type)
{
    CardLayout* cardArray = GetDesiredCardLayout(type);

    return cardArray->CheckSelection(phase);
}*/


//------------------------------------------------------------------------------
// SignalTransferComplete - Inform the gameManager that a card transfer has
//                          finished.
//------------------------------------------------------------------------------
void CardManager::SignalTransferComplete(void)
{
    emit TransferComplete(numOfCardsTransferred);
}
