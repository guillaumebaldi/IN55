#ifndef MESH_H
#define MESH_H

#include <QVector3D>

#include <vector>
#include <iostream>
using namespace std;

class Mesh
{
public:
    Mesh();
    vector<QVector3D> getVertices();
    vector<int> getIndices();
    vector<QVector3D> getNormales();
    void addVertex(QVector3D vertex);
    void addIndex(int index);
    void addNormal(QVector3D normal);
private:
    vector<QVector3D> vertices;
    vector<int> indices;
    vector<QVector3D> normales;
};

#endif // MESH_H
