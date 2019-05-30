#include "animbone.h"

AnimBone::AnimBone()
{

}

AnimBone::AnimBone(string id)
{
    this->id = id;
}

string AnimBone::getId() {
    return this->id;
}

void AnimBone::setPositions(vector<QVector3D> positions) {
    this->positions = positions;
    this->nbPositions = positions.size();
}

vector<QVector3D> AnimBone::getPositions() {
    return this->positions;
}

void AnimBone::setScales(vector<QVector3D> scales) {
    this->scales = scales;
    this->nbScales = scales.size();
}

vector<QVector3D> AnimBone::getScales() {
    return this->scales;
}

void AnimBone::setRotations(vector<QQuaternion> rotations) {
    this->rotations = rotations;
    this->nbRotations = rotations.size();
}

vector<QQuaternion> AnimBone::getRotations() {
    return this->rotations;
}
