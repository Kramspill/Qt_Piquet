//------------------------------------------------------------------------------
// Filename: InputDialog.h
// Description: Header file for InputDialog.
//------------------------------------------------------------------------------

#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsGridLayout>
#include <QGraphicsProxyWidget>
#include <QPushButton>


//------------------------------------------------------------------------------
// Class: InputDialog
//------------------------------------------------------------------------------
class InputDialog : public QObject, public QGraphicsGridLayout
{
    Q_OBJECT
public:
    InputDialog(QGraphicsLayoutItem *parent = 0);
    InputDialog(InputDialog&);
    ~InputDialog(void);

    void                  Initialize(void);

private:
    void                  ConnectSignals(void);

signals:
    void                  ExecuteDeal(void);
    void                  ExecutePlayerDiscard(void);

private:
    QGraphicsProxyWidget* dealButton;     // TEMP
    QGraphicsProxyWidget* exchangeButton; // TEMP
    QGraphicsProxyWidget* declareButton;  // TEMP
    QGraphicsProxyWidget* sinkButton;     // TEMP
};

#endif // INPUTDIALOG_H
