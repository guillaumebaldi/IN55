#ifndef ANIMBONE_H
#define ANIMBONE_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "bone.h"

#include <vector>

class AnimBone
{
public:
    AnimBone();
    AnimBone(string);
    string getId();
    void setPositions(vector<QVector3D> positions);
    vector<QVector3D> getPositions();
    void setScales(vector<QVector3D> scales);
    vector<QVector3D> getScales();
    void setRotations(vector<QQuaternion> rotations);
    vector<QQuaternion> getRotations();
private:
    string id;
    vector<QVector3D> positions;
    vector<QVector3D> scales;
    vector<QQuaternion> rotations;
    size_t nbPositions = 0;
    size_t nbScales = 0;
    size_t nbRotations = 0;
};

#endif // ANIMBONE_H
