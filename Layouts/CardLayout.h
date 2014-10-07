//------------------------------------------------------------------------------
// Filename: CardLayout.h
// Description: Header file for CardLayout.
//------------------------------------------------------------------------------

#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsLayout>


//------------------------------------------------------------------------------
// Class: CardLayout
//------------------------------------------------------------------------------
class CardLayout : public QGraphicsLayout
{
public:
    CardLayout(QGraphicsLayoutItem* parent = 0);
    CardLayout(CardLayout&);
    ~CardLayout(void);

    void                        AddItem(QGraphicsLayoutItem* layoutItem);
    int                         GetItemIndex(QGraphicsLayoutItem* item);

    void                        setGeometry(const QRect& rect);
    QSizeF                      sizeHint(Qt::SizeHint which,
                                         const QSizeF& constraint = QSizeF()
                                         ) const;
    int                         count(void) const;
    QGraphicsLayoutItem*        itemAt(int index) const;
    void                        removeAt(int index);

private:
    QList<QGraphicsLayoutItem*> items;
};

#endif // CARDLAYOUT_H
