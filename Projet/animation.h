/**
  Animation :
  Data structure containing the bones used during the process of an animation
*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector3D>
#include <QMatrix4x4>
#include "bone.h"
#include "animbone.h"

#include <vector>

class Animation
{
public:
    Animation();
    Animation(string);
    string getId();
    vector<AnimBone> getAnimBones();
    void addAnimBone(AnimBone a);
    void setDuration(double d);
    double getDuration();
private:
    string id;
    vector<AnimBone> animBones;
    double duration;
    size_t nbAnimBones = 0;
};

#endif // ANIMATION_H
