//------------------------------------------------------------------------------
// Filename: CardManager.h
// Description: Header file for CardManager.
//------------------------------------------------------------------------------

#ifndef CARDMANAGER_H
#define CARDMANAGER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>
#include <QTimer>
#include <QEventLoop>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"
#include "Scene/Scene.h"
#include "ScoreManager.h"
#include "Cards/CardArray.h"
#include "Cards/Card.h"


//------------------------------------------------------------------------------
// Class: CardManager
//------------------------------------------------------------------------------
class CardManager : public QObject
{
    Q_OBJECT
public:
    CardManager(void);
    CardManager(CardManager&);
    ~CardManager(void);

    void               Initialize(Scene* scene);

    void               TransferCards(CardArray* src,
                                     CardArray* dest,
                                     int        numCards);

    CardArray*         GetCardArray(CardArray::Type type);
    std::vector<Card*> GetSelection(PlayerNum player);

private:
    void               InitializeCards(void);
    void               AddCardsToScene(Scene* scene);
    void               ShuffleDeck(void);

    void               DealOutCards(CardArray* src,
                                    CardArray* dest,
                                    int        numCards);
    void               TransferSelectedCards(CardArray* src,
                                             CardArray* dest);

public slots:
    void               SetCardsMoveable(bool setMoveable);
    void               SetCardsSelectable(bool setSelectable,
                                          PlayerNum player);

    void               DeselectCards(void);
    void               ValidateSelection(void);
    void               PrepForTrick(void);

signals:
    void               ValidSelection(bool);
    void               InformCardsMoveable(bool);

private:
    CardArray*         deck;
    CardArray*         talon;
    CardArray*         playerHand;
    CardArray*         cpuHand;
    CardArray*         playerDiscards;
    CardArray*         cpuDiscards;
    CardArray*         previousTricks;
    CardArray*         playerTrick;
    CardArray*         cpuTrick;
    QTimer*            transitionTimer;
};

#endif // CARDMANAGER_H
