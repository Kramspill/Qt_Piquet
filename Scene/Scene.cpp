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

    // Position the items in the scene.
    primaryAction->move(2180, 800);
    secondaryAction->move(2120, 800);
    title->move(2150, 700);
    text->move(2120, 750);
    log->move(2050, 500);

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
// mouseReleaseEvent - Override of QGraphicsScene::mousePressEvent to allow
//                     multiple item selection without needing the Ctrl key.
//------------------------------------------------------------------------------
void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Get the item located at this mousePressEvent.
    QGraphicsItem* itemUnderMouse =
            itemAt(mouseEvent->scenePos(), QTransform());

    // Toggle the item's selection if possible.
    if ( itemUnderMouse && itemUnderMouse->isEnabled() &&
            (itemUnderMouse->flags() & QGraphicsItem::ItemIsSelectable) )
    {
        itemUnderMouse->setSelected(!itemUnderMouse->isSelected());

        // Inform the card it has been selected and add the card to the
        // selection array.
        emit SignalCardSelectionsChanged((Card*)itemUnderMouse);
    }
    else if ( itemUnderMouse )
    {
        Card* itemIsACard = qgraphicsitem_cast<Card*>(itemUnderMouse);

        // Call the parent class' mousePressEvent if the item isn't a Card
        // or we have set the cards to be moveable.
        if ( !itemIsACard || cardsMoveable )
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
        }
    }
}


//------------------------------------------------------------------------------
// mouseReleaseEvent - Override of QGraphicsScene::mouseDoubleClickEvent to do
//                     nothing.
//------------------------------------------------------------------------------
void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{
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
// CreateDialog - Create and display a dialog to allow user interaction.
//------------------------------------------------------------------------------
void Scene::CreateDialog(Dialog::DialogType dialogType)
{
    dialog = new Dialog();
    dialog->Initialize(dialogType);

    int result = dialog->exec();

    if ( result == 1 )
    {
        emit ExecuteDeal();
        //emit DialogAccepted(dialogType);
    }
}


//------------------------------------------------------------------------------
// SetUI - Setup the ui buttons and labels for the current phase.
//------------------------------------------------------------------------------
void Scene::SetUI(Scene::PhaseType phase)
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
                             this,          SIGNAL(ExecuteDeal()));
            break;

        case EXCHANGE:
            title->setText("Exchange Phase");
            text->setText("Select cards from your hand\nto exchange with from the Talon.");

            primaryAction->setText("Exchange");
            secondaryAction->setVisible(false);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(ExecuteDeal()));
            QObject::connect(   primaryAction, SIGNAL(clicked()),
                                this,          SIGNAL(ExecuteExchange()));
            break;

        case POINT:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Point declaration.");

            primaryAction->setText("Declare");
            secondaryAction->setText("Skip");
            secondaryAction->setVisible(true);

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(ExecuteExchange()));
            QObject::connect(   primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclarePoint()));

            QObject::connect(   secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipPoint()));
            break;

        case SEQUENCE:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Sequence declaration.");

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclarePoint()));
            QObject::connect(   primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclareSequence()));

            QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipPoint()));
            QObject::connect(   secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipSequence()));
            break;

        case SET:
            title->setText("Declaration Phase");
            text->setText("Select cards of the same\nsuit for Set declaration.");

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclareSequence()));
            QObject::connect(   primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclareSet()));

            QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipSequence()));
            QObject::connect(   secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipSet()));
            break;

        case TRICK:
            title->setText("Trick Phase");
            text->setText("Select cards of the same\nsuit for Set declaration.");

            primaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            secondaryAction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            text->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            QObject::disconnect(primaryAction,   SIGNAL(clicked()),
                                this,            SIGNAL(DeclareSet()));
            QObject::disconnect(secondaryAction, SIGNAL(clicked()),
                                this,            SIGNAL(SkipSet()));
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
