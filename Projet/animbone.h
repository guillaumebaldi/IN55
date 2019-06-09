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
    /*void setPositions(vector<QVector3D> positions);
    vector<QVector3D> getPositions();
    void setScales(vector<QVector3D> scales);
    vector<QVector3D> getScales();
    void setRotations(vector<QQuaternion> rotations);
    vector<QQuaternion> getRotations();*/
    void setPositions(vector<aiVectorKey> positions);
    vector<aiVectorKey> getPositions();
    aiVectorKey getPosition(float id);
    int getIdPosition(float t);
    void addPosition(aiVectorKey position);
    int getNbPositions();
    void setScales(vector<aiVectorKey> scales);
    vector<aiVectorKey> getScales();
    aiVectorKey getScale(float id);
    int getIdScale(float t);
    void addScale(aiVectorKey scale);
    int getNbScales();
    void setRotations(vector<aiQuatKey> rotations);
    vector<aiQuatKey> getRotations();
    aiQuatKey getRotation(float id);
    int getIdRotation(float t);
    void addRotation(aiQuatKey rotation);
    int getNbRotations();
private:
    string id;
    /*vector<QVector3D> positions;
    vector<QVector3D> scales;
    vector<QQuaternion> rotations;*/
    vector<aiVectorKey> positions;
    vector<aiVectorKey> scales;
    vector<aiQuatKey> rotations;
    size_t nbPositions = 0;
    size_t nbScales = 0;
    size_t nbRotations = 0;
};

#endif // ANIMBONE_H
