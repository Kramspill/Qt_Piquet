#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "Cards/Card.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int x, int y, int width, int height);

    void addItem(Card* card);

signals:

public slots:

};

#endif // SCENE_H
