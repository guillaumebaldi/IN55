#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>
using namespace std;

class Mesh
{
public:
    Mesh();
    string getId();
    void setId(string id);
    vector<float> getVertices();
    void setVertices(vector<float> vertices);
private:
    string id;
    vector<float> vertices;
};

#endif // MESH_H
