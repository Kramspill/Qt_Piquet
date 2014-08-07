#include "Scene.h"

Scene::Scene(int x, int y, int width, int height) :
    QGraphicsScene(x, y, width, height)
{
}

void Scene::addItem(Card* card)
{
    QGraphicsScene::addItem(card);
}
