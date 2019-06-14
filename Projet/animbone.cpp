#include "animbone.h"

AnimBone::AnimBone()
{

}

AnimBone::AnimBone(string id)
{
    this->id = id;
}

/*
 * Returns id of animbone
 */
string AnimBone::getId() {
    return this->id;
}

/*
 * Returns translations
 */
vector<aiVectorKey> AnimBone::getPositions() {
    return this->positions;
}

/*
 * Adds translation
 */
void AnimBone::addPosition(aiVectorKey position) {
    this->positions.push_back(position);
    this->nbPositions++;
}

/*
 * Returns number of translations
 */
int AnimBone::getNbPositions() {
    return this->nbPositions;
}

/*
 * Returns scales
 */
vector<aiVectorKey> AnimBone::getScales() {
    return this->scales;
}

/*
 * Adds scale
 */
void AnimBone::addScale(aiVectorKey scale) {
    this->scales.push_back(scale);
    this->nbScales++;
}

/*
 * Returns number of scales
 */
int AnimBone::getNbScales() {
    return this->nbScales;
}

/*
 * Returns rotations
 */
vector<aiQuatKey> AnimBone::getRotations() {
    return this->rotations;
}

/*
 * Adds rotation
 */
void AnimBone::addRotation(aiQuatKey rotation) {
    this->rotations.push_back(rotation);
    this->nbRotations++;
}

/*
 * Returns number of rotations
 */
int AnimBone::getNbRotations() {
    return this->nbRotations;
}
