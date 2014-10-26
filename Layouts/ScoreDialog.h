//------------------------------------------------------------------------------
// Filename: ScoreDialog.h
// Description: Header file for ScoreDialog.
//------------------------------------------------------------------------------

#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

//------------------------------------------------------------------------------
// Qt Header Files
//------------------------------------------------------------------------------
#include <QGraphicsGridLayout>


//------------------------------------------------------------------------------
// Class: ScoreDialog
//------------------------------------------------------------------------------
class ScoreDialog : public QObject, public QGraphicsGridLayout
{
    Q_OBJECT
public:
    ScoreDialog(QGraphicsGridLayout* parent = 0);
    ScoreDialog(ScoreDialog&);
    ~ScoreDialog(void);

};

#endif // SCOREDIALOG_H
