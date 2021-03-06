//------------------------------------------------------------------------------
// Filename: CardStates.h
// Description: Collection of state classes that a Card can take.
//------------------------------------------------------------------------------

#ifndef CARDSTATES_H
#define CARDSTATES_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QState>


//------------------------------------------------------------------------------
// Class: InDeckState
//------------------------------------------------------------------------------
class InDeckState : public QState
{
public:
    InDeckState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InPlayerHandState
//------------------------------------------------------------------------------
class InPlayerHandState : public QState
{
public:
    InPlayerHandState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InCpuHandState
//------------------------------------------------------------------------------
class InCpuHandState : public QState
{
public:
    InCpuHandState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InTalonState
//------------------------------------------------------------------------------
class InTalonState : public QState
{
public:
    InTalonState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InPlayerDiscardsState
//------------------------------------------------------------------------------
class InPlayerDiscardsState : public QState
{
public:
    InPlayerDiscardsState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InCpuDiscardsState
//------------------------------------------------------------------------------
class InCpuDiscardsState : public QState
{
public:
    InCpuDiscardsState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InPlayerTrickState
//------------------------------------------------------------------------------
class InPlayerTrickState : public QState
{
public:
    InPlayerTrickState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InCpuTrickState
//------------------------------------------------------------------------------
class InCpuTrickState : public QState
{
public:
    InCpuTrickState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};


//------------------------------------------------------------------------------
// Class: InPreviousTricksState
//------------------------------------------------------------------------------
class InPreviousTricksState : public QState
{
public:
    InPreviousTricksState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
    void onExit(QEvent*)  {}
};

#endif // CARDSTATES_H
