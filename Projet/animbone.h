/**
  AnimBone :
  Data structure containing the translations, rotations and scales applied on a bone
*/

#ifndef ANIMBONE_H
#define ANIMBONE_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "bone.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class AnimBone
{
public:
    AnimBone();
    AnimBone(string);
    string getId();
    vector<aiVectorKey> getPositions();
    void addPosition(aiVectorKey position);
    int getNbPositions();
    vector<aiVectorKey> getScales();
    void addScale(aiVectorKey scale);
    int getNbScales();
    vector<aiQuatKey> getRotations();
    void addRotation(aiQuatKey rotation);
    int getNbRotations();
private:
    string id;
    vector<aiVectorKey> positions;
    vector<aiVectorKey> scales;
    vector<aiQuatKey> rotations;
    size_t nbPositions = 0;
    size_t nbScales = 0;
    size_t nbRotations = 0;
};

#endif // ANIMBONE_H
