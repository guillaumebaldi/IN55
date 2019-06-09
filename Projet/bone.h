#ifndef BONE_H
#define BONE_H

#include <QVector3D>
#include <QMatrix4x4>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
using namespace std;
#include <algorithm>

class Bone
{
public:
    Bone();
    Bone(string, QMatrix4x4);
    Bone(QMatrix4x4);
    QMatrix4x4 getTransform();
    void setTransform(QMatrix4x4 m);
    QMatrix4x4 getOffset();
    void setOffset(QMatrix4x4 m);
    string getId();
    void setId(string id);
    QMatrix4x4 getParent();
    void setParent(QMatrix4x4 parent);
    int getNumber();
    void setNumber(int number);
    vector<int> getVertices();
    void addVertex(int v);
    vector<float> getWeights();
    float getWeight(int vertex);
    void addWeight(float w);
    vector<Bone> getChildren();
    void addChild(Bone b);
private:
    int number;
    string id;
    QMatrix4x4 parent;
    QMatrix4x4 transform;
    QMatrix4x4 offset;
    vector<int> vertices;
    vector<float> weights;
    vector<Bone> children;
};

#endif // BONE_H
