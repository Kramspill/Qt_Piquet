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
#include <QTextEdit>
#include <QGridLayout>


//------------------------------------------------------------------------------
// Class: Dialog
//------------------------------------------------------------------------------
class Dialog : public QDialog
{
    Q_OBJECT
public:
    enum ButtonType
    {
        DEAL,
        EXCHANGE,
        DECLARE,
        PASS,
        GOOD,
        NOTGOOD,
        OK
    };

public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(Dialog&);
    ~Dialog(void);

    void Initialize(char* title, char* msg, int numOfBtns,
                    ButtonType* buttonTypes);

private:
    QGridLayout* layout;
    QTextEdit* message;
};

#endif // DIALOG_H
