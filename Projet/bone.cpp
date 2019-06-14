#include "bone.h"

Bone::Bone()
{

}

Bone::Bone(QMatrix4x4 transform)
{
    this->transform = transform;
}

Bone::Bone(string id, QMatrix4x4 transform)
{
    this->id = id;
    this->transform = transform;
}

/*
 * Returns transform of bone
 */
QMatrix4x4 Bone::getTransform() {
    return this->transform;
}

/*
 * Sets transform of bone
 */
void Bone::setTransform(QMatrix4x4 m) {
    this->transform = m;
}

/*
 * Returns offset of bone
 */
QMatrix4x4 Bone::getOffset() {
    return this->offset;
}

/*
 * Sets offset of bone
 */
void Bone::setOffset(QMatrix4x4 m) {
    this->offset = m;
}

/*
 * Returns id of bone
 */
string Bone::getId() {
    return this->id;
}

/*
 * Sets id of bone
 */
void Bone::setId(string id) {
    this->id = id;
}

/*
 * Returns parent of bone
 */
QMatrix4x4 Bone::getParent() {
    return this->parent;
}

/*
 * Sets parent of bone
 */
void Bone::setParent(QMatrix4x4 parent) {
    this->parent = parent;
}

/*
 * Returns number of the bone
 */
int Bone::getNumber() {
    return this->number;
}

/*
 * Sets number of the bone
 */
void Bone::setNumber(int number) {
    this->number = number;
}

/*
 * Returns vertices of bone
 */
vector<int> Bone::getVertices() {
    return this->vertices;
}

/*
 * Adds vertex
 */
void Bone::addVertex(int v) {
    this->vertices.push_back(v);
}

/*
 * Returns weights of bone
 */
vector<float> Bone::getWeights() {
    return this->weights;
}

/*
 * Returns weight of vertex of bone
 */
float Bone::getWeight(int vertex) {
    float w = 0;
    ptrdiff_t pos = distance(vertices.begin(), find(vertices.begin(), vertices.end(), vertex));
    if(pos >= vertices.size()) {
        w = -1;
    }
    else {
        w = this->getWeights()[pos];
    }
    return w;
}

/*
 * Adds weight
 */
void Bone::addWeight(float w) {
    this->weights.push_back(w);
}

/*
 * Returns children of bone
 */
vector<Bone> Bone::getChildren() {
    return this->children;
}

/*
 * Adds child to the bone
 */
void Bone::addChild(Bone b) {
    this->children.push_back(b);
}
