//------------------------------------------------------------------------------
// Filename: UIArea.h
// Description: Header file for UIArea.
//------------------------------------------------------------------------------

#ifndef UIAREA_H
#define UIAREA_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPainter>


//------------------------------------------------------------------------------
// Class: UIArea
//------------------------------------------------------------------------------
class UIArea : public QWidget
{
    Q_OBJECT
public:
    UIArea(QWidget *parent = 0);
    UIArea(UIArea&);
    ~UIArea(void);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // UIAREA_H
