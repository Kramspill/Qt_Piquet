//------------------------------------------------------------------------------
// Filename: Player.h
// Description: Header file for Player.
//------------------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>
#include <QEventLoop>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/CardArray.h"
#include "Scene/Scene.h"
#include "State/GlobalStateInfo.h"


//------------------------------------------------------------------------------
// Class: Player
//------------------------------------------------------------------------------
class Player : public QObject
{
    Q_OBJECT
public:
    Player(void);
    Player(Player&);
    ~Player(void);

    virtual void Initialize(PlayerNum num);

    virtual void SelectElder(void);
    virtual void ExecuteDeal(void);
    virtual void ExecuteExchange(void);
    virtual void AnnounceDeclaration(State phase);
    virtual void Respond(State phase);
    virtual void PlayTrick(void);
    virtual void CarteBlanche(void);

protected:
    virtual void ExecuteCarteBlanche(void);

private:
    void         ConnectSignals(void);

public slots:
    void         CarteBlancheYes(void);
    void         CarteBlancheNo(void);

private slots:
    void         SkipRequested(void);

signals:
    void         BeginElderSelect(void);

    void         BeginDeal(void);
    void         DealComplete(void);

    void         BeginExchange(void);
    void         ExchangeComplete(void);

    void         Declare(void);
    void         Skip(void);

    void         Blanche(void);
    void         ScoreCarteBlanche(void);

    void         PrepForTrick(void);
    void         TrickPlayed(void);

    void         SetCardsMoveable(bool);
    void         SetCardsSelectable(bool, PlayerNum);
    void         DeselectCards(void);
    void         RequestCardTransfer(CardArray::Type,
                                     CardArray::Type,
                                     int);
    void         SetUI(State);

protected:
    PlayerNum    playerNumber;
};

#endif // PLAYER_H
