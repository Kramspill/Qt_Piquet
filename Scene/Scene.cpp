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
Scene::Scene(void) :
    QGraphicsScene(),
    dialog(0)
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
    // Allocate memory for member variables.
    container      = new QGraphicsWidget();
    mainLayout     = new QGraphicsGridLayout();
    playerCardArea = new QGraphicsGridLayout();
    cpuCardArea    = new QGraphicsGridLayout();
    talonArea      = new QGraphicsGridLayout();
    playingArea    = new QGraphicsGridLayout();
    inputDialog    = new InputDialog();
    scoreDialog    = new ScoreDialog();

    // Position the layouts within the mainLayout.
    PositionLayouts();

    // Set the containing widget's layout and add the container to the scene.
    container->setLayout(mainLayout);
    this->addItem(container);

    // Activate the main layout.
    mainLayout->activate();

    // Connect signals.
    ConnectSignals();
}


//------------------------------------------------------------------------------
// AddLayout - Add a layout to one of the scene's top layer layouts.
//------------------------------------------------------------------------------
void Scene::AddLayout(Scene::Layout layout, CardLayout* cardLayout,
                      int row, int column)
{
    QGraphicsGridLayout* l = GetLayout(layout);

    l->addItem(cardLayout, row, column, Qt::AlignVCenter);

    // Re-activate the main layout.
    mainLayout->activate();
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

        // Call the parent class' mousePressEvent if the item isn't a Card.
        if ( !itemIsACard )
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
// PositionLayouts - Set the positions of the layouts contained by mainLayout.
//------------------------------------------------------------------------------
void Scene::PositionLayouts(void)
{
    // Add the layouts within mainLayout.
    mainLayout->addItem(playerCardArea, 4, 2, 1, 5, Qt::AlignVCenter);
    mainLayout->addItem(cpuCardArea,    0, 2, 1, 5, Qt::AlignVCenter);
    mainLayout->addItem(talonArea,      1, 0, 3, 1, Qt::AlignVCenter);
    mainLayout->addItem(playingArea,    1, 1, 3, 7, Qt::AlignVCenter);
    mainLayout->addItem(inputDialog,    4, 8, 1, 2, Qt::AlignVCenter);
    mainLayout->addItem(scoreDialog,    1, 8, 3, 2, Qt::AlignVCenter);
}


//------------------------------------------------------------------------------
// ConnectSignals - Connect the signals to/from this class.
//------------------------------------------------------------------------------
void Scene::ConnectSignals(void)
{
    QObject::connect(inputDialog, SIGNAL(ExecuteDeal()),
                     this,        SIGNAL(ExecuteDeal()));
    QObject::connect(inputDialog, SIGNAL(ExecutePlayerDiscard()),
                     this,        SIGNAL(ExecutePlayerDiscard()));
}


//------------------------------------------------------------------------------
// GetLayout - Return a desired layout from this class.
//------------------------------------------------------------------------------
QGraphicsGridLayout* Scene::GetLayout(Scene::Layout layout)
{
    QGraphicsGridLayout* l;

    switch ( layout )
    {
        case MAIN:
            l = mainLayout;
            break;

        case PLAYER:
            l = playerCardArea;
            break;

        case CPU:
            l = cpuCardArea;
            break;

        case TALON:
            l = talonArea;
            break;

        case PLAYING:
            l = playingArea;
            break;

        default:
            break;
    }

    return l;
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
