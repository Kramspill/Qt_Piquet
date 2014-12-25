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
Scene::Scene(int x, int y, int width, int height) :
    QGraphicsScene(x, y, width, height),
    dialog(0),
    xPos(x),
    yPos(y),
    width(width),
    height(height),
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

    // Add items to the scene.
    addWidget(primaryAction);
    addWidget(secondaryAction);
    addWidget(title);
    addWidget(text);
    addWidget(log);

    QPointF p = GetCenterPos();
    int x = (int)p.x();
    int y = (int)p.y();

    // Position the items in the scene.
    primaryAction->move(x+280, y+270);
    secondaryAction->move(x+170, y+270);
    title->move(x+220, y+200);
    text->move(x+180, y+230);
    log->move(x+130, y);

    // Set up the player trick area.
    playerTrickArea = new QRect(x-200, y-80, 170, 160);

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
            if ( card && cardsMoveable )
            {
                if ( IsInsideTrickArea(mouseEvent->scenePos()) )
                {
                    card->setFlag(QGraphicsItem::ItemIsSelectable, true);
                    card->setSelected(true);
                    emit TrickPlayed();
                }
                else
                {
                    card->UpdateAnimation(false);
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
    switch ( phase )
    {
        case DEAL:
            title->setText("Deal Phase");
            text->setText("Click 'Deal' to have\nthe dealer deal the cards.");

            primaryAction->setText("Deal");
            secondaryAction->setVisible(false);

            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::connect(primaryAction, SIGNAL(clicked()),
                             this,          SIGNAL(BeginDeal()));
            break;

        case EXCHANGE:
            title->setText("Exchange Phase");
            text->setText("Select cards from your hand\nto exchange with from the Talon.");

            primaryAction->setText("Exchange");
            primaryAction->setEnabled(false);
            secondaryAction->setVisible(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(BeginDeal()));
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
            break;

        case SET:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Set declaration.");

            primaryAction->setEnabled(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            break;

        case RESPOND:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Point declaration.");

            primaryAction->setEnabled(false);

            primaryAction->setText("Good");
            secondaryAction->setText("Not Good");
            secondaryAction->setVisible(true);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            break;

        case TRICK:
            title->setText("Trick Phase");
            text->setText("Drag a card to the playing field.");

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(Declare()));
            QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(Skip()));

            primaryAction->setVisible(false);
            secondaryAction->setVisible(false);
            break;
    };
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
    if ( valid )
        primaryAction->setEnabled(true);
    else
        primaryAction->setEnabled(false);
}
