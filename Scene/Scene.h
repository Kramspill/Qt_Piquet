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
#include <QTableWidget>
#include <QHeaderView>


//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "State/GlobalStateInfo.h"
#include "UIArea.h"
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
    Scene(QRectF rect);
    Scene(Scene&);
    ~Scene(void);

    void              Initialize(void);

    QPointF           GetCenterPos(void);

    void              SetTitle(const QString& newTitle);
    void              SetText(const QString& newText);

    int               GetWidth(void);
    int               GetHeight(void);
    QRectF*           GetTrickArea(void);

    void              UpdateLog(const QString& newMessage);

protected:
    void              mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void              mouseDoubleClickEvent(QGraphicsSceneMouseEvent*mouseEvent);

private:
    void              ConnectSignals(void);
    bool              IsInsideTrickArea(QPointF p);

public slots:
    void              CreateDialog(Dialog::DialogType dialogType);
    void              SetUI(State phase);
    void              SetCardsMoveable(bool moveable);
    void              SetValidSelection(bool valid);
    void              UpdateScores(int p1Score, int p2Score);

signals:
    void              BeginDeal(void);
    void              BeginExchange(void);
    void              Declare(void);
    void              Skip(void);
    void              TrickPlayed(void);


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
    QTableWidgetItem* player2Score;
    UIArea*           area;
    Dialog*           dialog;
    QRectF*           playerTrickArea;
    int               xPos;
    int               yPos;
    int               width;
    int               height;
    bool              cardsMoveable;
};

#endif // SCENE_H
