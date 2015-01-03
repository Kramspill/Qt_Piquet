//------------------------------------------------------------------------------
// Filename: UIArea.cpp
// Description: Represents the user interface area.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "UIArea.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
UIArea::UIArea(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("background: transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setEnabled(false);
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
UIArea::UIArea(UIArea&)
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
UIArea::~UIArea(void)
{
}


//------------------------------------------------------------------------------
// paintEvent - Called when this item needs repainting.
//------------------------------------------------------------------------------
void UIArea::paintEvent(QPaintEvent* event)
{
    QRect rect(this->rect());

    QPainter painter(this);
    QPen     pen(Qt::gray);
    pen.setWidth(5);

    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(20, 20, 20, 250)));

    painter.drawRoundedRect(rect, 10, 10);
}
