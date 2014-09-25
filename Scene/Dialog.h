//------------------------------------------------------------------------------
// Filename: Dialog.h
// Description: Header file for Dialog.
//------------------------------------------------------------------------------

#ifndef DIALOG_H
#define DIALOG_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QDialog>


//------------------------------------------------------------------------------
// Class: Dialog
//------------------------------------------------------------------------------
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);

signals:

public slots:

};

#endif // DIALOG_H