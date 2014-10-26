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
    height(height)
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
// ConnectSignals - Connect various signals to/from this class.
//------------------------------------------------------------------------------
void Scene::ConnectSignals(void)
{
    QObject::connect(dialog, SIGNAL(ExecuteDeal()),
                     this,   SIGNAL(ExecuteDeal()));
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
