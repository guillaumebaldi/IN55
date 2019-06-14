/**
  AnimationManager :
  Handles the process of an animation
*/

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
    void playHello(double t);
    void playWalk(double t);
    void playRun(double t);
    void playJump(double t);
    vector<QMatrix4x4> getTransformations(double t, Animation anim);
private:
    void calcTransformations(double t, Animation anim, AnimBone bone, vector<QMatrix4x4> &transformations, QMatrix4x4 parent);
    QMatrix4x4 calcInterpolatedPosition(double t, AnimBone bone);
    QMatrix4x4 calcInterpolatedRotation(double t, AnimBone bone);
    QMatrix4x4 calcInterpolatedScale(double t, AnimBone bone);

    Scene *scene;
    Model m;
};

#endif // ANIMATIONMANAGER_H
