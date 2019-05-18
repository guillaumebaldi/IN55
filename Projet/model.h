#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QMatrix4x4>
#include "bone.h"
#include "mesh.h"

#include <vector>
using namespace std;

class Model
{
public:
    Model();
    Model(QMatrix4x4);
    Model(QMatrix4x4, vector<Bone>);
    Model(QMatrix4x4, vector<Bone>, vector<Mesh>);
    QMatrix4x4 getTransform();
    void setTransform(QMatrix4x4 m);
    void setBones(vector<Bone> bones);
    vector<Bone> getBones();
    void addBone(Bone b);
    void setMeshes(vector<Mesh> meshes);
    vector<Mesh> getMeshes();
    void addMesh(Mesh m);
private:
    QMatrix4x4 transform;
    vector<Bone> bones;
    vector<Mesh> meshes;
    size_t nbBones = 0;
    size_t nbMeshes = 0;
};

#endif // MODEL_H
