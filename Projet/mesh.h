#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector2D>




#include <vector>
#include <iostream>

using namespace std;

struct Vertex
{
    // Position
    QVector3D position;
    // Normal
   QVector3D normal;
    // TexCoords
   QVector2D uv;
};

class Mesh
{
public:
    Mesh();
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
    vector<Vertex> getVertices();
    vector<unsigned int> getIndices();
    void setVertices(vector<Vertex> vertices);
    void addVertex(Vertex vertex);
    void addIndex(unsigned int index);
private:    
    vector<Vertex> vertices;
    vector<unsigned int> indices;
};

#endif // MESH_H
