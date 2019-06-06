#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "model.h"
#include "bone.h"
#include "animation.h"
#include "animbone.h"
#include "mesh.h"
#include "scene.h"

#include <QVector3D>
#include <QQuaternion>

#include <vector>
using namespace std;

class AnimationManager
{
public:
    AnimationManager();
    AnimationManager(Scene*);
    void playIdle();
    void playHello();
    void playWalk();
    void playRun();
    void playJump();
private:
    Scene *scene;
};

#endif // ANIMATIONMANAGER_H
