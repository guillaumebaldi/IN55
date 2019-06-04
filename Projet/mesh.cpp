#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices){
    this->vertices = vertices;
    this->indices = indices;    

}

vector<Vertex> Mesh::getVertices() {
    return this->vertices;
}

vector<unsigned int> Mesh::getIndices() {
    return this->indices;
}

void Mesh::setVertices(vector<Vertex> vertices) {
    this->vertices = vertices;
}

void Mesh::addVertex(Vertex vertex) {
    this->vertices.push_back(vertex);
}

void Mesh::addIndex(unsigned int index) {
    this->indices.push_back(index);
}
