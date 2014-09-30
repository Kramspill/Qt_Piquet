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
#include <QPushButton>


//------------------------------------------------------------------------------
// Class: Dialog
//------------------------------------------------------------------------------
class Dialog : public QDialog
{
    Q_OBJECT
public:
    enum DialogType
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

    void                      Initialize(DialogType dialogType);

private:
    void                      InitializeButtons(void);
    void                      SetDialogTitle(void);
    void                      SetInitialMessage(void);

signals:
    void                      ExecuteDeal(void);

private:
    DialogType                type;
    QGridLayout*              layout;
    QTextEdit*                message;
    std::vector<QPushButton*> buttons;
};

#endif // DIALOG_H
