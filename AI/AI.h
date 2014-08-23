//------------------------------------------------------------------------------
// Filename: AI.h
// Description: Header file for AI.
//------------------------------------------------------------------------------

#ifndef AI_H
#define AI_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QObject>


//------------------------------------------------------------------------------
// Class: AI
//------------------------------------------------------------------------------
class AI : public QObject
{
    Q_OBJECT
public:
    AI(void);
    AI(AI&);
    ~AI(void);

    void Initialize(void);

public slots:
    void SelectCardsToDiscard(void);
    void DeclarePoint(void);
    void DeclareSequence(void);
    void DeclareSet(void);
};

#endif // AI_H
