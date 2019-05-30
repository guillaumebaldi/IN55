#include "animation.h"

Animation::Animation()
{

}

Animation::Animation(string id)
{
    this->id = id;
}

string Animation::getId() {
    return this->id;
}

void Animation::setId(string id) {
    this->id = id;
}

void Animation::setAnimBones(vector<AnimBone> animBones) {
    this->animBones = animBones;
    this->nbAnimBones = animBones.size();
}

vector<AnimBone> Animation::getAnimBones() {
    return this->animBones;
}

void Animation::addAnimBone(AnimBone a) {
    this->animBones.push_back(a);
    this->nbAnimBones++;
}

void Animation::setTimes(vector<double> times) {
    this->times = times;
    this->nbTimes = times.size();
}

vector<double> Animation::getTimes() {
    return this->times;
}
