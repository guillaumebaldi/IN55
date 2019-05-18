#include "mesh.h"

Mesh::Mesh()
{

}

string Mesh::getId() {
    return this->id;
}

void Mesh::setId(string id) {
    this->id = id;
}

vector<float> Mesh::getVertices() {
    return this->vertices;
}

void Mesh::setVertices(vector<float> vertices) {
    this->vertices = vertices;
}
