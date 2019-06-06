#include "animationmanager.h"

AnimationManager::AnimationManager(Scene* scene)
{
    this->scene = scene;
}

void AnimationManager::playIdle() {
    Animation a = scene->getModel().getAnimation("idle");
    vector<QVector3D> positions;
    vector<QVector3D> scales;
    vector<QQuaternion> rotations;

    for(unsigned int i = 0; i < a.getAnimBones().size(); i++) {
        AnimBone anim(a.getAnimBones()[i]);
        Bone b(scene->getModel().getBone(anim.getId()));
        if(b.getId().compare("")) {
            vector<QVector3D> positionsT(anim.getPositions());
            positions.insert(std::end(positions), std::begin(positionsT), std::end(positionsT));

            vector<QVector3D> scalesT(anim.getScales());
            scales.insert(std::end(scales), std::begin(scalesT), std::end(scalesT));

            vector<QQuaternion> rotationsT(anim.getRotations());
            rotations.insert(std::end(rotations), std::begin(rotationsT), std::end(rotationsT));
        }
    }

    scene->animate(positions, scales, rotations);
}

void AnimationManager::playHello() {

}

void AnimationManager::playWalk() {

}

void AnimationManager::playRun() {

}

void AnimationManager::playJump() {

}
