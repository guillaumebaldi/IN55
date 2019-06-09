#include "animationmanager.h"

AnimationManager::AnimationManager(Scene* scene)
{
    this->scene = scene;
}



/*void AnimationManager::playIdle() {
    Animation a = scene->getModel().getAnimation("idle");
    vector<QVector3D> positions;
    vector<QVector3D> scales;
    vector<QQuaternion> rotations;

    for(unsigned int i = 0; i < a.getAnimBones().size(); i++) {
        AnimBone anim(a.getAnimBones()[i]);
        Bone b(scene->getModel().getBone(anim.getId()));
        if(b.getId().compare("")) {
            /*vector<QVector3D> positionsT(anim.getPositions());
            positions.insert(std::end(positions), std::begin(positionsT), std::end(positionsT));

            vector<QVector3D> scalesT(anim.getScales());
            scales.insert(std::end(scales), std::begin(scalesT), std::end(scalesT));

            vector<QQuaternion> rotationsT(anim.getRotations());
            rotations.insert(std::end(rotations), std::begin(rotationsT), std::end(rotationsT));
        }
    }

    scene->animate(positions, scales, rotations);
}*/

void AnimationManager::playIdle() {
    Animation a = scene->getModel().getAnimation("idle");
    vector<QMatrix4x4> transformations;

    /*for(unsigned int i = 0; i < a.getAnimBones().size(); i++) {
        AnimBone bone = a.getAnimBones()[i];

        aiVector3D pos;
        CalcInterpolatedPosition(pos, 0.0416662, bone);
        //aiVector3D pos = bone.getPosition(0).mValue;
        aiMatrix4x4 matrixPos;
        aiMatrix4x4::Translation(aiVector3D(pos.x, pos.y, pos.z), matrixPos);

        aiVector3D sca;
        CalcInterpolatedScale(sca, 0.0416662, bone);
        //aiVector3D sca = bone.getScale(0).mValue;
        aiMatrix4x4 matrixSca;
        aiMatrix4x4::Scaling(aiVector3D(sca.x, sca.y, sca.z), matrixSca);

        aiQuaternion rot;
        CalcInterpolatedRotation(rot, 0.0416662, bone);
        //aiQuaternion rot = bone.getRotation(0).mValue;
        aiMatrix4x4 matrixRot = aiMatrix4x4(rot.GetMatrix());

        aiMatrix4x4 trans = matrixPos * matrixRot * matrixSca;
        trans.d4 = 1;
        //aiMatrix4x4 temp = scene->getModel().getBone(scene->getModel().getBone(bone.getId()).getParent()).getTransform() * trans;
        aiMatrix4x4 temp = scene->getModel().getBone(bone.getId()).getParent() * trans;
        temp.d4 = 1;
        aiMatrix4x4 final = scene->getModel().inverse * temp * scene->getModel().getBone(bone.getId()).getTransform();
        //final = final.Transpose();
        //trans = trans.Transpose();
        final.d4 = 1;
        /*transformations.push_back(QMatrix4x4(final.a1, final.b1, trans.c1, final.d1,
                                             final.a2, final.b2, final.c2, final.d2,
                                             final.a3, final.b3, final.c3, final.d3,
                                             final.a4, final.b4, final.c4, final.d4));
        transformations.push_back(QMatrix4x4(final[0]));
        std::cout << transformations[i].data()[0] << " "<< transformations[i].data()[1] << " "<< transformations[i].data()[2] << " "<< transformations[i].data()[3] << " "<< transformations[i].data()[4] << " "<< transformations[i].data()[5] << " "<< transformations[i].data()[6] << " "<< transformations[i].data()[7] << " "<< transformations[i].data()[8] << " "<< transformations[i].data()[9] << " "<< transformations[i].data()[10] << " "<< transformations[i].data()[11] << " "<< transformations[i].data()[12] << " "<< transformations[i].data()[13] << " "<< transformations[i].data()[14] << " "<< transformations[i].data()[15] << "\n";
        std::cout << final.a1 << " "<< final.a2 << " "<< final.a3 << " "<< final.a4 << " "<< final.b1 << " "<< final.b2 << " "<< final.b3 << " "<< final.b4 << " "<< final.c1 << " "<< final.c2 << " "<< final.c3 << " "<< final.c4 << " "<< final.d1 << " "<< final.d2 << " "<< final.d3 << " "<< final.d4 << "\n";
        //std::cout << matrixPos.a1 << " "<< matrixPos.a2 << " "<< matrixPos.a3 << " "<< matrixPos.a4 << " "<< matrixPos.b1 << " "<< matrixPos.b2 << " "<< matrixPos.b3 << " "<< matrixPos.b4 << " "<< matrixPos.c1 << " "<< matrixPos.c2 << " "<< matrixPos.c3 << " "<< matrixPos.c4 << " "<< matrixPos.d1 << " "<< matrixPos.d2 << " "<< matrixPos.d3 << " "<< matrixPos.d4 << "\n";
    }
    scene->animate(transformations);*/
}

void AnimationManager::playHello() {

}

void AnimationManager::playWalk() {

}

void AnimationManager::playRun() {

}

void AnimationManager::playJump() {

}

void AnimationManager::setIdle(vector<QMatrix4x4> t) {
    this->idleTransformations = t;
}

vector<QMatrix4x4> AnimationManager::getIdle() {
    return this->idleTransformations;
}

void AnimationManager::setWalk(vector<QMatrix4x4> t) {
    this->walkTransformations = t;
}

vector<QMatrix4x4> AnimationManager::getWalk() {
    return this->walkTransformations;
}
