//------------------------------------------------------------------------------
// Filename: CardLayout.h
// Description: Header file for CardLayout.
//------------------------------------------------------------------------------

#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QLayout>


//------------------------------------------------------------------------------
// Class: CardLayout
//------------------------------------------------------------------------------
class CardLayout : public QLayout
{
public:
    CardLayout(QWidget* parent);
    CardLayout(CardLayout&);
    ~CardLayout(void);

    void                      Destroy(void);

    void                      addItem(QLayoutItem* item);
    void                      setGeometry(const QRect& rect);
    QSize                     sizeHint(void) const;
    QLayoutItem*              itemAt(int index) const;
    QLayoutItem*              takeAt(int index);

private:
    QList<QLayoutItem*> items;
};

#endif // CARDLAYOUT_H
