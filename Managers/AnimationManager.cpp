#include "AnimationManager.h"

// Destructor.
AnimationManager::~AnimationManager(void)
{
}

// Get the AnimationManager singleton.
AnimationManager& AnimationManager::GetSingleton(void)
{
    static AnimationManager singleton;
    return singleton;
}

// Add an animation to the list of animations held by AnimationManager.
void AnimationManager::AddAnimation(QAbstractAnimation* animation)
{
    QObject::connect(animation, SIGNAL(destroyed(QAbstractAnimation*)),
                     this, SLOT(RemoveAnimation(QAbstractAnimation*)));

    animations.append(animation);
}

// Remove all animations for the animation list.
void AnimationManager::RemoveAllAnimations(void)
{
    animations.clear();
}

// Remove an animation from the animation list.
void AnimationManager::RemoveAnimation(QAbstractAnimation* animation)
{
    QObject::disconnect(animation, SIGNAL(destroyed(QAbstractAnimation*)),
                        this, SLOT(RemoveAnimation(QAbstractAnimation*)));

    animations.removeAll(animation);
}
