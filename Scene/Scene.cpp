//------------------------------------------------------------------------------
// Filename: Scene.cpp
// Description: Represents the game scene.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// My Header Files
//------------------------------------------------------------------------------
#include "Scene.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Scene::Scene(QRectF rect) :
    QGraphicsScene(rect),
    dialog(0),
    xPos(rect.x()),
    yPos(rect.y()),
    width(rect.width()),
    height(rect.height()),
    cardsMoveable(false)
{
}


//------------------------------------------------------------------------------
// Copy Constructor
//------------------------------------------------------------------------------
Scene::Scene(Scene&) :
    QGraphicsScene()
{
}


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
Scene::~Scene(void)
{
}


//------------------------------------------------------------------------------
// Initialize - Initialize the scene by connecting the appropriate signals.
//------------------------------------------------------------------------------
void Scene::Initialize(void)
{
    // Allocate space for member variables.
    primaryAction   = new QPushButton();
    secondaryAction = new QPushButton();
    title           = new QLabel();
    text            = new QLabel();
    log             = new QTextEdit();
    table           = new QTableWidget();
    player1Score    = new QTableWidgetItem("0");
    player2Score    = new QTableWidgetItem("0");
    area            = new UIArea();

    // Set the size and position of the items in the scene.
    float uiLeft = width - (width / 4);
    QRect uiArea = QRect(uiLeft, 0, width - uiLeft, height);

    // User Interface
    QRect rect(uiLeft-10, 0, width-uiLeft+15, height+1);
    area->setGeometry(rect);

    // Score display.
    table->setRowCount(7);
    table->setColumnCount(2);
    table->setShowGrid(false);
    table->setHorizontalHeaderLabels(QStringList()<<"Player 1"<<"Player 2");
    table->setVerticalHeaderLabels(QStringList()<<"Partie 1"<<"Partie 2"<<
                                   "Partie 3"<<"Partie 4"<<"Partie 5"<<
                                   "Partie 6"<<"Current");
    for ( int i = 0; i < table->horizontalHeader()->count(); i++)
    {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    for (int i = 0; i < table->verticalHeader()->count(); i++)
    {
        table->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    table->setGeometry(uiArea.x(),
                       10,
                       uiArea.width()-5,
                       (uiArea.height()/3)-20);
    table->setStyleSheet("QTableView { border: 2px solid gray; border-radius: 10px;"
                         "background-color: QColor(20, 20, 20, 50); color: white; "
                         "gridline-color: white; }"
                         "QTableView::item { border-left: 1px solid gray; border-right: 1px solid gray; }"
                         "QTableView QTableCornerButton::section { background: transparent; }"
                         "QHeaderView { background: transparent; }"
                         "QHeaderView::section { background-color: QColor(20, 20, 20, 240); color: white;"
                         "padding: 2px; border: 2px solid gray; border-radius: 1px; }");
    table->setEnabled(false);

    QFont f = player1Score->font();
    f.setPointSizeF(16.0);
    player1Score->setFont(f);
    player2Score->setFont(f);
    player1Score->setTextAlignment(Qt::AlignCenter);
    player2Score->setTextAlignment(Qt::AlignCenter);
    table->setItem(6, 0, player1Score);
    table->setItem(6, 1, player2Score);


    // Action log.
    log->setGeometry(uiArea.x(),
                     uiArea.height()/3,
                     uiArea.width()-5,
                     (uiArea.height()/3)+50);
    log->setFontPointSize(16.0);
    log->setStyleSheet("QTextEdit { border: 2px solid gray; border-radius: 10px;"
                                    "background-color: QColor(20, 20, 20, 50); color: white; }");
    log->setEnabled(false);

    // Phase title.
    title->setGeometry(uiArea.x() +
                       (uiArea.width()/2 - 80),
                       ((uiArea.height()/4)*3),
                       0,
                       0);
    f = title->font();
    f.setPointSizeF(18.0);
    f.setBold(true);
    f.setUnderline(true);
    title->setFont(f);
    title->setStyleSheet("QLabel { background : transparent; color: white }");

    // Phase message.
    text->setGeometry(uiArea.x() + (uiArea.width()/2 - 120),
                      ((uiArea.height()/4)*3)+50,
                      0,
                      0);
    f = text->font();
    f.setPointSizeF(16.0);
    text->setFont(f);
    text->setStyleSheet("QLabel { background : transparent; color: white }");

    // Primary action.
    primaryAction->setGeometry(uiArea.x()+180,
                               ((uiArea.height()/4)*3)+130,
                               110,
                               45);
    f = primaryAction->font();
    f.setPointSizeF(16.0);
    primaryAction->setFont(f);
    primaryAction->setStyleSheet("QPushButton { border: 2px solid gray; border-radius: 10px;"
                                 "background-color: QColor(40, 40, 40, 100); color: white; }"
                                 "QPushButton:hover { background-color: QColor(60, 60, 60, 200); }"
                                 "QPushButton:disabled { color: gray; }");

    // Secondary action.
    secondaryAction->setGeometry(uiArea.x()+30,
                                 ((uiArea.height()/4)*3)+130,
                                 110,
                                 45);
    f = secondaryAction->font();
    f.setPointSizeF(14.0);
    secondaryAction->setFont(f);
    secondaryAction->setStyleSheet("QPushButton { border: 2px solid gray; border-radius: 10px;"
                                   "background-color: QColor(40, 40, 40, 100); color: white; }"
                                   "QPushButton:hover { background-color: QColor(60, 60, 60, 200); }"
                                   "QPushButton:disabled { color: gray; }");

    // Add the items to the scene.
    addWidget(area);
    addWidget(primaryAction);
    addWidget(secondaryAction);
    addWidget(title);
    addWidget(text);
    addWidget(log);
    addWidget(table);

    // Set up the player trick area.
    QRectF playingArea;
    playingArea.setWidth((width - uiArea.width()) * 0.83);
    playingArea.setHeight(height * 0.7);
    playingArea.setX((width - uiArea.width() - playingArea.width())+100);
    playingArea.setY(height - playingArea.height());

    playerTrickArea = new QRectF(playingArea);

    // Connect the signals.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// GetCenterPos - Get the coordinates of the center of the window.
//------------------------------------------------------------------------------
QPointF Scene::GetCenterPos(void)
{
    return QPointF(xPos + (width/2), yPos + (height/2));
}


//------------------------------------------------------------------------------
// SetTitle - Set the UI input box title.
//------------------------------------------------------------------------------
void Scene::SetTitle(const QString& newTitle)
{
    title->setText(newTitle);
}


//------------------------------------------------------------------------------
// SetText - Set the UI input box text.
//------------------------------------------------------------------------------
void Scene::SetText(const QString& newText)
{
    text->setText(newText);
}


//------------------------------------------------------------------------------
// PostScore - Post the partie score to the table.
//------------------------------------------------------------------------------
void Scene::PostScore(int partie)
{
    QTableWidgetItem* item1 = new QTableWidgetItem(player1Score->text());
    QTableWidgetItem* item2 = new QTableWidgetItem(player2Score->text());

    QFont f = item1->font();
    f.setPointSizeF(16.0);
    item1->setFont(f);
    item2->setFont(f);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);

    // Update the global state info.
    table->setItem(partie, 0, item1);
    table->setItem(partie, 1, item2);
}


//------------------------------------------------------------------------------
// GetWidth - Get the Scene width.
//------------------------------------------------------------------------------
int Scene::GetWidth(void)
{
    return width;
}


//------------------------------------------------------------------------------
// GetHeight - Get the Scene height.
//------------------------------------------------------------------------------
int Scene::GetHeight(void)
{
    return height;
}


//------------------------------------------------------------------------------
// GetTrickArea - Get the Trick area.
//------------------------------------------------------------------------------
QRectF* Scene::GetTrickArea(void)
{
    return playerTrickArea;
}


//------------------------------------------------------------------------------
// UpdateLog - Update the log field.
//------------------------------------------------------------------------------
void Scene::UpdateLog(const QString& newMessage)
{
    log->append(newMessage);
}


//------------------------------------------------------------------------------
// mousePressEvent - Override of QGraphicsScene::mousePressEvent to allow
//                   multiple item selection without needing the Ctrl key.
//------------------------------------------------------------------------------
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Get the item located at this mousePressEvent.
    QGraphicsItem* itemUnderMouse =
            itemAt(mouseEvent->scenePos(), QTransform());

    // If there is an item, then call the parent function.
    if ( itemUnderMouse )
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}


//------------------------------------------------------------------------------
// mouseMoveEvent - Override of QGraphicsScene::mouseMoveEvent.
//------------------------------------------------------------------------------
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}


//------------------------------------------------------------------------------
// mouseReleaseEvent - Override of QGraphicsScene::mouseReleaseEvent.
//------------------------------------------------------------------------------
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Get the item located at this mousePressEvent.
    QGraphicsItem* itemUnderMouse =
            itemAt(mouseEvent->scenePos(), QTransform());

    if ( itemUnderMouse )
    {
        Card* card = qgraphicsitem_cast<Card*>(itemUnderMouse);

        // Call the parent class' mousePressEvent if the item isn't a Card
        // or we have set the cards to be moveable.
        if ( !card || cardsMoveable )
        {
            if ( card && (card->flags() & QGraphicsItem::ItemIsMovable) &&
                 cardsMoveable )
            {
                if ( IsInsideTrickArea(mouseEvent->scenePos()) )
                {
                    card->setFlag(QGraphicsItem::ItemIsSelectable, true);
                    card->setSelected(true);
                    emit TrickPlayed();
                }
            }
        }
    }

    emit ValidateSelection();

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


//------------------------------------------------------------------------------
// mouseDoubleClickEvent - Override of QGraphicsScene::mouseDoubleClickEvent.
//------------------------------------------------------------------------------
void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Get the item located at this mousePressEvent.
    QGraphicsItem* itemUnderMouse =
            itemAt(mouseEvent->scenePos(), QTransform());

    // If there is an item, then call the parent function.
    if ( itemUnderMouse )
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect various signals to/from this class.
//------------------------------------------------------------------------------
void Scene::ConnectSignals(void)
{
    /*QObject::connect(dialog, SIGNAL(ExecuteDeal()),
                     this,   SIGNAL(ExecuteDeal()));*/
}


//------------------------------------------------------------------------------
// IsInsideTrickArea - Check if a card was moved inside the trick area.
//------------------------------------------------------------------------------
bool Scene::IsInsideTrickArea(QPointF p)
{
    bool result = false;

    if ( p.x() > playerTrickArea->x() &&
         p.x() < playerTrickArea->x() + playerTrickArea->width() &&
         p.y() > playerTrickArea->y() &&
         p.y() < playerTrickArea->y() + playerTrickArea->height() )
    {
        result = true;
    }

    return result;
}


//------------------------------------------------------------------------------
// CreateDialog - Create and display a dialog to allow user interaction.
//------------------------------------------------------------------------------
void Scene::CreateDialog(Dialog::DialogType dialogType)
{
    dialog = new Dialog();
    dialog->Initialize(dialogType);

    int result = dialog->exec();

    if ( result == 1 )
    {
        //emit ExecuteDeal();
        //emit DialogAccepted(dialogType);
    }
}


//------------------------------------------------------------------------------
// SetUI - Setup the ui buttons and labels for the current phase.
//------------------------------------------------------------------------------
void Scene::SetUI(State phase)
{
    QFont        title_font  = title->font();
    QFont        text_font   = text->font();
    QFont        action_font = primaryAction->font();
    QFontMetrics fmTitle(title_font);
    QFontMetrics fmText(text_font);
    QString      str;
    float        uiLeft = width - (width / 4);
    QRectF       uiArea = QRectF(uiLeft, 0, width - uiLeft, height);
    char* string = new char[40];
    int   i   = 0;

    switch ( phase )
    {
        case ELDERSELECT:
            title->setText("Elder Selection");
            text->setText("Click 'Randomize' to\nrandomly select the Elder.");

            primaryAction->setText("Randomize");
            secondaryAction->setVisible(false);

            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmText.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/2,
                                primaryAction->y());

            QObject::connect(primaryAction, SIGNAL(clicked()),
                             this,          SIGNAL(BeginElderSelect()));
            break;

        case DEAL:
            title->setText("Deal Phase");
            text->setText("Click 'Deal' to have\nthe dealer deal the cards.");

            primaryAction->setText("Deal");
            secondaryAction->setVisible(false);

            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmText.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/2,
                                primaryAction->y());

            QObject::disconnect(primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(BeginElderSelect()));
            QObject::connect(   primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(BeginDeal()));
            break;

        case EXCHANGE:
            title->setText("Exchange Phase");
            text->setText("Select cards from your hand to\nexchange with from the Talon.");

            primaryAction->setText("Exchange");
            primaryAction->setEnabled(false);
            secondaryAction->setVisible(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/2,
                                primaryAction->y());

            if ( declarationResults->carteBlancheWinner == PLAYER1 )
            {
                QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                    this,            SIGNAL(Yes()));

                QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                    this,            SIGNAL(No()));
            }
            else
            {
                QObject::disconnect(primaryAction, SIGNAL(clicked()),
                                    this,          SIGNAL(BeginDeal()));
            }
            QObject::connect(   primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(BeginExchange()));
            break;

        case POINT:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Point declaration.");

            primaryAction->setText("Declare");
            primaryAction->setEnabled(false);
            secondaryAction->setText("Skip");
            secondaryAction->setVisible(true);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+((uiArea.width()-secondaryAction->width())/4)*3,
                                secondaryAction->y());
            secondaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/4,
                                  primaryAction->y());


            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(BeginExchange()));
            QObject::connect(   primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(Declare()));

            QObject::connect(   secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(Skip()));
            break;

        case SEQUENCE:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Sequence declaration.");

            primaryAction->setEnabled(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+((uiArea.width()-secondaryAction->width())/4)*3,
                                secondaryAction->y());
            secondaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/4,
                                  primaryAction->y());
            break;

        case SET:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Set declaration.");

            primaryAction->setEnabled(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+((uiArea.width()-secondaryAction->width())/4)*3,
                                secondaryAction->y());
            secondaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/4,
                                  primaryAction->y());
            break;

        case RESPOND:
            title->setText("Declaration Phase");
            text->setText("Select cards to match or\nimprove on the declaration");

            primaryAction->setEnabled(false);

            primaryAction->setText("Not Good");
            secondaryAction->setText("Good");
            secondaryAction->setVisible(true);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+((uiArea.width()-secondaryAction->width())/4)*3,
                                secondaryAction->y());
            secondaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/4,
                                  primaryAction->y());
            break;

        case TRICK:
            title->setText("Trick Phase");
            text->setText("Drag a card to the playing field.");

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str))/2),
                       text->y());

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(Declare()));
            QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(Skip()));

            primaryAction->setVisible(false);
            secondaryAction->setVisible(false);
            break;

        case BLANCHE:
            title->setText("Carte Blanche");
            text->setText("Do you wish to\ndeclare Carte Blanche?");

            primaryAction->setText("Yes");
            primaryAction->setEnabled(true);
            secondaryAction->setText("No");
            secondaryAction->setVisible(true);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmTitle.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+((uiArea.width()-secondaryAction->width())/4)*3,
                                secondaryAction->y());
            secondaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/4,
                                  primaryAction->y());

            QObject::disconnect(primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(BeginDeal()));
            QObject::connect(   primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(Yes()));

            QObject::connect(   secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(No()));
            break;

        case SUMMARY:
            title->setText("Results");

            if ( partieResults->currentDeal == 6 )
            {
                int p1Final = 0;
                int p2Final = 0;
                for ( i = 0; i < 6; i++ )
                {
                    p1Final += partieResults->deal[0][i];
                    p2Final += partieResults->deal[1][i];
                }

                snprintf(string, 40, "PLAYER 1: %d\nPLAYER 2: %d",
                         p1Final, p2Final);
                primaryAction->setText("New Game");
            }
            else
            {
                snprintf(string, 40, "PLAYER 1: %d\nPLAYER 2: %d",
                         player1Score->text().toInt(),
                         player2Score->text().toInt());
                primaryAction->setText("Continue");
            }

            text->setText(string);

            primaryAction->setVisible(true);
            secondaryAction->setVisible(false);

            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            // Position the items.
            str = title->text();
            title->move(uiArea.x()+((uiArea.width()-fmText.width(str))/2),
                        title->y());
            str = text->text();
            text->move(uiArea.x()+((uiArea.width()-fmText.width(str)/2)/2),
                       text->y());
            primaryAction->move(uiArea.x()+(uiArea.width()-primaryAction->width())/2,
                                primaryAction->y());

            QObject::connect(primaryAction, SIGNAL(clicked()),
                             this,          SIGNAL(Continue()));
            break;
    };

    delete[] string;
}


//------------------------------------------------------------------------------
// SetCardsMoveable - Set the cards in the scene to allow movement by a user.
//------------------------------------------------------------------------------
void Scene::SetCardsMoveable(bool moveable)
{
    cardsMoveable = moveable;
}


//------------------------------------------------------------------------------
// SetCardsMoveable - Set the cards in the scene to allow movement by a user.
//------------------------------------------------------------------------------
void Scene::SetValidSelection(bool valid)
{
    if ( primaryAction->text() != "Yes")
    {
        if ( valid )
            primaryAction->setEnabled(true);
        else
            primaryAction->setEnabled(false);
    }
}


//------------------------------------------------------------------------------
// UpdateScores - Set player1Score's and player2Score's value.
//------------------------------------------------------------------------------
void Scene::UpdateScores(int p1Score, int p2Score)
{
    char* str = new char[5];

    sprintf(str,"%d",p1Score);
    player1Score->setText(str);

    sprintf(str,"%d",p2Score);
    player2Score->setText(str);

    delete[] str;
}
