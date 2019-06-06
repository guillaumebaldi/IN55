#ifndef BONE_H
#define BONE_H

#include <QVector3D>
#include <QMatrix4x4>

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
    string getId();
    void setId(string id);
    string getParent();
    void setParent(string id);
    int getNumber();
    void setNumber(int number);
    vector<int> getVertices();
    void addVertex(int v);
    vector<float> getWeights();
    float getWeight(int vertex);
    void addWeight(float w);
private:
    int number;
    string id;
    string parent;
    QMatrix4x4 transform;
    vector<int> vertices;
    vector<float> weights;
};

#endif // BONE_H
