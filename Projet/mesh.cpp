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

vector<QVector3D> Mesh::getVertices() {
    return this->vertices;
}

vector<int> Mesh::getIndices() {
    return this->indices;
}

vector<QVector3D> Mesh::getNormales() {
    return this->normales;
}

void Mesh::setVertices(vector<QVector3D> vertices) {
    this->vertices = vertices;
}

void Mesh::addVertex(QVector3D vertex) {
    this->vertices.push_back(vertex);
}

void Mesh::addIndex(int index) {
    this->indices.push_back(index);
}

void Mesh::addNormal(QVector3D normal) {
    this->normales.push_back(normal);
}
