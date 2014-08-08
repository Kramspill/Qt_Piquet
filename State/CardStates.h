#ifndef CARDSTATES_H
#define CARDSTATES_H

#include <QState>

class InDeckState : public QState
{
public:
    InDeckState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InPlayerHandState : public QState
{
public:
    InPlayerHandState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InCpuHandState : public QState
{
public:
    InCpuHandState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InTalonState : public QState
{
public:
    InTalonState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InPlayerDiscardsState : public QState
{
public:
    InPlayerDiscardsState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InCpuDiscardsState : public QState
{
public:
    InCpuDiscardsState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InCurrentTrickState : public QState
{
public:
    InCurrentTrickState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

class InPreviousTricksState : public QState
{
public:
    InPreviousTricksState(QState* parent = 0) :
        QState(parent)
    {
    }

protected:
    void onEntry(QEvent*) {}
};

#endif // CARDSTATES_H
