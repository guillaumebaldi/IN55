#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "model.h"
#include "bone.h"
#include "animation.h"
#include "animbone.h"
#include "mesh.h"
#include "scene.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
    void setIdle(vector<QMatrix4x4> t);
    vector<QMatrix4x4> getIdle();
    void setWalk(vector<QMatrix4x4> t);
    vector<QMatrix4x4> getWalk();
private:
    Scene *scene;
    vector<QMatrix4x4> idleTransformations;
    vector<QMatrix4x4> walkTransformations;
};

#endif // ANIMATIONMANAGER_H
