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


vector<aiVectorKey> AnimBone::getPositions() {
    return this->positions;
}

void AnimBone::addPosition(aiVectorKey position) {
    this->positions.push_back(position);
    this->nbPositions++;
}

int AnimBone::getNbPositions() {
    return this->nbPositions;
}


vector<aiVectorKey> AnimBone::getScales() {
    return this->scales;
}

void AnimBone::addScale(aiVectorKey scale) {
    this->scales.push_back(scale);
    this->nbScales++;
}

int AnimBone::getNbScales() {
    return this->nbScales;
}


vector<aiQuatKey> AnimBone::getRotations() {
    return this->rotations;
}

void AnimBone::addRotation(aiQuatKey rotation) {
    this->rotations.push_back(rotation);
    this->nbRotations++;
}

int AnimBone::getNbRotations() {
    return this->nbRotations;
}
