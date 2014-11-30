//------------------------------------------------------------------------------
// Filename: Scene.h
// Description: Header file for Scene.
//------------------------------------------------------------------------------

#ifndef SCENE_H
#define SCENE_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QRect>
#include <QLabel>
#include <QTextEdit>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Cards/Card.h"
#include "Cards/CardArray.h"
#include "Dialog.h"


//------------------------------------------------------------------------------
// Class: Scene
//------------------------------------------------------------------------------
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum PhaseType
    {
        DEAL,
        EXCHANGE,
        POINT,
        SEQUENCE,
        SET,
        TRICK
    };

public:
    Scene(int x, int y, int width, int height);
    Scene(Scene&);
    ~Scene(void);

    void         Initialize(void);

    QPointF      GetCenterPos(void);

    void         SetTitle(const QString& newTitle);
    void         SetText(const QString& newText);

protected:
    void         mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void         mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void         mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void         mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

private:
    void         ConnectSignals(void);
    bool         IsInsideTrickArea(QPointF p);

public slots:
    void         CreateDialog(Dialog::DialogType dialogType);
    void         SetUI(PhaseType phase);
    void         SetCardsMoveable(bool moveable);

signals:
    void         RequestACardTransfer(CardArray::CardArrayType,
                                      CardArray::CardArrayType,
                                      Card*);
    void         SignalCardSelectionsChanged(Card*);
    void         ExecuteDeal(void);
    void         ExecuteExchange(void);
    void         DeclarePoint(void);
    void         DeclareSequence(void);
    void         DeclareSet(void);
    void         SkipDeclaration(void); //TODO
    void         SkipPoint(void);
    void         SkipSequence(void);
    void         SkipSet(void);

private:
    QPushButton* primaryAction;
    QPushButton* secondaryAction;
    QLabel*      title;
    QLabel*      text;
    QTextEdit*   log;
    Dialog*      dialog;
    QRect*       playerTrickArea;
    int          xPos;
    int          yPos;
    int          width;
    int          height;
    bool         cardsMoveable;
};

#endif // SCENE_H
