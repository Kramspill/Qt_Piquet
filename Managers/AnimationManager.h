#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QAbstractAnimation>

class AnimationManager : public QObject
{
    Q_OBJECT
public:
    ~AnimationManager(void);

    static AnimationManager& GetSingleton(void);

    void AddAnimation(QAbstractAnimation* animation);
    void RemoveAllAnimations(void);

private:
    AnimationManager(void);
    AnimationManager(AnimationManager&);
    void operator=(AnimationManager&);

public slots:
    void RemoveAnimation(QAbstractAnimation* animation);

private:
    QList<QAbstractAnimation*> animations;
};

#endif // ANIMATIONMANAGER_H
