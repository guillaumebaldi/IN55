#include "animationmanager.h"

AnimationManager::AnimationManager(Scene* scene)
{
    this->scene = scene;
    this->m = scene->getModel();
}

/*
 * Handles the Idle animation
 */
void AnimationManager::playIdle() {
    scene->animate(getTransformations(1, m.getAnimations()[0]));
}

/*
 * Handles the Hello animation
 */
void AnimationManager::playHello(double t) {
    scene->animate(getTransformations(t, m.getAnimations()[1]));
}

/*
 * Handles the Walk animation
 */
void AnimationManager::playWalk(double t) {
    scene->animate(getTransformations(t, m.getAnimations()[2]));
}

/*
 * Handles the Run animation
 */
void AnimationManager::playRun(double t) {
    scene->animate(getTransformations(t, m.getAnimations()[3]));
}

/*
 * Handles the Jump animation
 */
void AnimationManager::playJump(double t) {
    scene->animate(getTransformations(t, m.getAnimations()[4]));
}


/*
 * Returns the transformations to apply at a given time on each bone
 */
vector<QMatrix4x4> AnimationManager::getTransformations(double t, Animation anim){
    vector<QMatrix4x4> transformations;

    double time = t * anim.getDuration();

    //Parent of first bone
    QMatrix4x4 parent = m.getBone(anim.getAnimBones()[0].getId()).getParent();
    calcTransformations(time, anim, anim.getAnimBones()[0], transformations, parent);

    return transformations;
}

/*
 * Recursive function to have the transformations applied on each bone at a given tile
 */
void AnimationManager::calcTransformations(double t, Animation anim, AnimBone bone, vector<QMatrix4x4> &transformations, QMatrix4x4 parent){
    Bone b = m.getBone(bone.getId());
    QMatrix4x4 boneTransform;

    //Translation, rotation and scaling
    QMatrix4x4 posMatrix = calcInterpolatedPosition(t, bone);
    QMatrix4x4 rotMatrix = calcInterpolatedRotation(t, bone);
    QMatrix4x4 scaMatrix = calcInterpolatedScale(t, bone);

    //Multiplication of each transformation
    boneTransform = posMatrix * rotMatrix * scaMatrix;

    //Application of transformation with parent on the bone
    QMatrix4x4 transformation = parent * boneTransform;
    transformations.push_back(m.getTransform().inverted() * transformation * b.getOffset());

    //Recursivity on all children of the bone
    for(unsigned int i = 0; i < b.getChildren().size(); i++) {
        AnimBone a = anim.getAnimBones()[b.getChildren()[i].getNumber()];
        calcTransformations(t, anim, a, transformations, transformation);
    }
}

/*
 * Interpolation of translation
 */
QMatrix4x4 AnimationManager::calcInterpolatedPosition(double t, AnimBone bone){
    QMatrix4x4 identity;
    identity.setToIdentity();

    //If only 1 translation in animation
    if (bone.getNbPositions() == 1) {
        return QMatrix4x4(1,0,0, bone.getPositions()[0].mValue.x,
                          0,1,0, bone.getPositions()[0].mValue.y,
                          0,0,1, bone.getPositions()[0].mValue.z,
                          0,0,0,1);
    }
    if (bone.getNbPositions() == 0) {
        return identity;
    }

    //Previous id
    int id = 0;
    for (int i = 0 ; i < bone.getNbPositions() - 1 ; ++i) {
        if (t < bone.getPositions()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    //Next id
    int nextId = id +1;
    if(nextId >= bone.getNbPositions() ){
        return identity;
    }

    //Time between next id and previous id translation
    float diff = bone.getPositions()[nextId].mTime - bone.getPositions()[id].mTime;
    float f = (t - bone.getPositions()[id].mTime) / diff;

    //Computes interpolated translation
    aiVector3D startPos = bone.getPositions()[id].mValue;
    aiVector3D endPos = bone.getPositions()[nextId].mValue;
    aiVector3D diffPos = endPos - startPos;
    aiVector3D inter = startPos + f * diffPos;

    QMatrix4x4 transformation;
    transformation.translate(inter.x, inter.y, inter.z);
    return transformation;
}

/*
 * Interpolation of rotation
 */
QMatrix4x4 AnimationManager::calcInterpolatedRotation(double t, AnimBone bone){
    QMatrix4x4 identity;
    aiMatrix3x3 rotationMatrix;
    identity.setToIdentity();

    //If only 1 rotation in animation
    if (bone.getNbRotations() == 1) {
        rotationMatrix = bone.getRotations()[0].mValue.GetMatrix();
        return QMatrix4x4(rotationMatrix.a1, rotationMatrix.a2, rotationMatrix.a3, 0,
                rotationMatrix.b1, rotationMatrix.b2, rotationMatrix.b3, 0,
                rotationMatrix.c1, rotationMatrix.c2, rotationMatrix.c3, 0,
                0,0,0,1) ;
    }

    if (bone.getNbRotations() == 0) {
        return identity;
    }

    //Previous id
    int id = 0;
    for (int i = 0 ; i < bone.getNbRotations() - 1 ; ++i) {
        if (t < bone.getRotations()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    //Next id
    int nextId = id +1;
    if(nextId >= bone.getNbRotations() ){
        return identity;
    }

    //Time between next id and previous id rotation
    float diff = bone.getRotations()[nextId].mTime - bone.getRotations()[id].mTime;
    float f = (t - bone.getRotations()[id].mTime) / diff;

    //Computes interpolated rotation
    aiQuaternion startRot = bone.getRotations()[id].mValue;
    aiQuaternion endRot = bone.getRotations()[nextId].mValue;
    aiQuaternion inter;
    aiQuaternion::Interpolate(inter, startRot, endRot, f);
    inter.Normalize();

    QQuaternion quat = QQuaternion(inter.w, inter.x, inter.y, inter.z);
    QMatrix4x4 rotation;
    rotation.rotate(quat);
    return rotation;
}

/*
 * Interpolation of scalin
 */
QMatrix4x4 AnimationManager::calcInterpolatedScale(double t, AnimBone bone){
    QMatrix4x4 identity;
    identity.setToIdentity();

    //if only 1 scaling in animation
    if (bone.getNbScales() == 1) {
        return QMatrix4x4(bone.getScales()[0].mValue.x,0,0,0,
                0,bone.getScales()[0].mValue.y,0,0,
                0,0,bone.getScales()[0].mValue.z,0,
                0,0,0,1);
    }
    if (bone.getNbScales() == 0) {
        return identity;
    }

    //Previous id
    int id = 0;
    for (int i = 0 ; i < bone.getNbScales() - 1 ; ++i) {
        if (t < bone.getScales()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    //Next id
    int nextId = id + 1;
    if(nextId >= bone.getNbScales() ){
        return identity;
    }

    //Time between next id and previous id scaling
    float diff = bone.getScales()[nextId].mTime - bone.getScales()[id].mTime;
    float f = (t - bone.getScales()[id].mTime) / diff;

    //Computes interpolated scaling
    aiVector3D startSca = bone.getScales()[id].mValue;
    aiVector3D endSca = bone.getScales()[nextId].mValue;
    aiVector3D diffSca = endSca - startSca;
    aiVector3D inter = startSca + f * diffSca;

    QMatrix4x4 scale;
    scale.scale(inter.x, inter.y, inter.z);
    return scale;
}
