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

vector<AnimBone> Animation::getAnimBones() {
    return this->animBones;
}

void Animation::addAnimBone(AnimBone a) {
    this->animBones.push_back(a);
    this->nbAnimBones++;
}

void Animation::setDuration(double d) {
    this->duration = d;
}

double Animation::getDuration() {
    return this->duration;
}
