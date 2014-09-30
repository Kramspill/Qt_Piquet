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
    QObject::connect(dialog, SIGNAL(ExecuteDeal()),
                     this,   SIGNAL(ExecuteDeal()));
}


//------------------------------------------------------------------------------
// addItem - Override of QGraphicsScene::addItem to accept a Card object.
//------------------------------------------------------------------------------
void Scene::addItem(Card* card)
{
    QGraphicsScene::addItem(card);
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
