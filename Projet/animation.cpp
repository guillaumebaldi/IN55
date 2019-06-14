#include "animation.h"

Animation::Animation()
{
}

Animation::Animation(string id)
{
    this->id = id;
}

/*
 * Returns id of the animation
 */
string Animation::getId() {
    return this->id;
}

/*
 * Returns the bones used in an animation
 */
vector<AnimBone> Animation::getAnimBones() {
    return this->animBones;
}

/*
 * Adds a bone
 */
void Animation::addAnimBone(AnimBone a) {
    this->animBones.push_back(a);
    this->nbAnimBones++;
}

/*
 * Sets the duration of animation
 */
void Animation::setDuration(double d) {
    this->duration = d;
}

/*
 * Returns the duration of animation
 */
double Animation::getDuration() {
    return this->duration;
}
