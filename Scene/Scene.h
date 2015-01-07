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
#include <QPushButton>
#include <QRect>
#include <QLabel>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QMenu>
#include <QMenuBar>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"
#include "UIArea.h"
#include "Cards/Card.h"
#include "Cards/CardArray.h"


//------------------------------------------------------------------------------
// Class: Scene
//------------------------------------------------------------------------------
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QRectF rect);
    Scene(Scene&);
    ~Scene(void);

    void              Initialize(void);
    void              Destroy(void);
    void              ResetTable(void);

    QPointF           GetCenterPos(void);

    void              SetTitle(const QString& newTitle);
    void              SetText(const QString& newText);

    void              PostScore(int partie);
    void              ClearLog(void);

    int               GetWidth(void);
    int               GetHeight(void);
    QRectF*           GetTrickArea(void);

protected:
    void              mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseDoubleClickEvent(QGraphicsSceneMouseEvent*mouseEvent);

private:
    bool              IsInsideTrickArea(QPointF p);

public slots:
    void              UpdateLog(const QString& newMessage);
    void              SetUI(State phase);
    void              SetCardsMoveable(bool moveable);
    void              SetValidSelection(bool valid);
    void              UpdateScores(int p1Score, int p2Score);

signals:
    void              BeginElderSelect(void);
    void              BeginDeal(void);
    void              BeginExchange(void);
    void              Declare(void);
    void              Skip(void);
    void              Yes(void);
    void              No(void);
    void              TrickPlayed(void);
    void              Continue(void);
    void              NewGame(void);

    void              RequestACardTransfer(CardArray::Type,
                                           CardArray::Type,
                                           Card*);
    void              SignalCardSelectionsChanged(Card*);
    void              ValidateSelection();

private:
    QPushButton*      primaryAction;
    QPushButton*      secondaryAction;
    QLabel*           title;
    QLabel*           text;
    QTextEdit*        log;
    QTableWidget*     table;
    QTableWidgetItem* player1Score;
    QTableWidgetItem* tableScores[2][6];
    QTableWidgetItem* player2Score;
    UIArea*           area;
    QMenuBar*         menuBar;
    QRectF*           playerTrickArea;
    int               xPos;
    int               yPos;
    int               width;
    int               height;
    bool              cardsMoveable;
};

#endif // SCENE_H
