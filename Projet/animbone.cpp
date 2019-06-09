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

void AnimBone::setPositions(vector<aiVectorKey> positions) {
    this->positions = positions;
}

vector<aiVectorKey> AnimBone::getPositions() {
    return this->positions;
}

aiVectorKey AnimBone::getPosition(float id) {
    return this->positions[id];
}

int AnimBone::getIdPosition(float t) {
    for(unsigned int i = 0; i < nbPositions - 1; i++) {
        if(t < (float)this->positions[i+1].mTime) {
            return i;
        }
    }
}

void AnimBone::addPosition(aiVectorKey position) {
    this->positions.push_back(position);
    this->nbPositions++;
}

int AnimBone::getNbPositions() {
    return this->nbPositions;
}

void AnimBone::setScales(vector<aiVectorKey> scales) {
    this->scales = scales;
}

vector<aiVectorKey> AnimBone::getScales() {
    return this->scales;
}

aiVectorKey AnimBone::getScale(float id) {
    return this->scales[id];
}

int AnimBone::getIdScale(float t) {
    for(unsigned int i = 0; i < nbScales - 1; i++) {
        if(t < (float)this->scales[i+1].mTime) {
            return i;
        }
    }
}

void AnimBone::addScale(aiVectorKey scale) {
    this->scales.push_back(scale);
    this->nbScales++;
}

int AnimBone::getNbScales() {
    return this->nbScales;
}

void AnimBone::setRotations(vector<aiQuatKey> rotations) {
    this->rotations = rotations;
}

vector<aiQuatKey> AnimBone::getRotations() {
    return this->rotations;
}

aiQuatKey AnimBone::getRotation(float id) {
    return this->rotations[id];
}

int AnimBone::getIdRotation(float t) {
    for(unsigned int i = 0; i < nbRotations - 1; i++) {
        if(t < (float)this->rotations[i+1].mTime) {
            return i;
        }
    }
}

void AnimBone::addRotation(aiQuatKey rotation) {
    this->rotations.push_back(rotation);
    this->nbRotations++;
}

int AnimBone::getNbRotations() {
    return this->nbRotations;
}
