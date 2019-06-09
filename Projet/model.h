#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QMatrix4x4>
#include "bone.h"
#include "mesh.h"
#include "animation.h"
#include <algorithm>
#include <vector>
using namespace std;

class Model
{
public:
    Model();
    Model(QMatrix4x4);
    Model(QMatrix4x4, vector<Bone>);
    Model(QMatrix4x4, vector<Bone>, vector<Mesh>);
    Model(QMatrix4x4, vector<Bone>, vector<Mesh>, vector<Animation>);
    QMatrix4x4 getTransform();
    void setTransform(QMatrix4x4 m);
    void setBones(vector<Bone> bones);
    vector<Bone> getBones();
    Bone getBone(string id);
    Bone getBoneByNumber(int number);
    void setMeshes(vector<Mesh> meshes);
    vector<Mesh> getMeshes();
    void setAnimations(vector<Animation> animations);
    vector<Animation> getAnimations();
    QVector4D getIndicesBone(int vertex);
    QVector4D getWeightsBone(int vertex, QVector4D indices);
private:
    QMatrix4x4 transform;
    vector<Bone> bones;
    vector<Mesh> meshes;
    vector <Animation> animations;
    size_t nbBones = 0;
    size_t nbMeshes = 0;
    size_t nbAnimations = 0;
};

#endif // MODEL_H
