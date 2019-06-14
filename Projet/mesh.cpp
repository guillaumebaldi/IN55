#include "mesh.h"

Mesh::Mesh()
{

}

/*
 * Returns vertices
 */
vector<QVector3D> Mesh::getVertices() {
    return this->vertices;
}

/*
 * Returns indices
 */
vector<int> Mesh::getIndices() {
    return this->indices;
}

/*
 * Returns normales
 */
vector<QVector3D> Mesh::getNormales() {
    return this->normales;
}

/*
 * Adds vertex
 */
void Mesh::addVertex(QVector3D vertex) {
    this->vertices.push_back(vertex);
}

/*
 * Adds index
 */
void Mesh::addIndex(int index) {
    this->indices.push_back(index);
}

/*
 * Adds normal
 */
void Mesh::addNormal(QVector3D normal) {
    this->normales.push_back(normal);
}
