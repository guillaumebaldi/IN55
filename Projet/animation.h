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
    void setId(string id);
    void setAnimBones(vector<AnimBone> animBones);
    vector<AnimBone> getAnimBones();
    void addAnimBone(AnimBone a);
    void setTimes(vector<double> times);
    vector<double> getTimes();
    void setDuration(double d);
    double getDuration();
private:
    string id;
    vector<AnimBone> animBones;
    vector<double> times;
    double duration;
    size_t nbAnimBones = 0;
    size_t nbTimes = 0;
};

#endif // ANIMATION_H
