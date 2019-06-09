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

QMatrix4x4 Bone::getTransform() {
    return this->transform;
}

void Bone::setTransform(QMatrix4x4 m) {
    this->transform = m;
}

QMatrix4x4 Bone::getOffset() {
    return this->offset;
}

void Bone::setOffset(QMatrix4x4 m) {
    this->offset = m;
}

string Bone::getId() {
    return this->id;
}

void Bone::setId(string id) {
    this->id = id;
}

QMatrix4x4 Bone::getParent() {
    return this->parent;
}

void Bone::setParent(QMatrix4x4 parent) {
    this->parent = parent;
}

int Bone::getNumber() {
    return this->number;
}

void Bone::setNumber(int number) {
    this->number = number;
}

vector<int> Bone::getVertices() {
    return this->vertices;
}

void Bone::addVertex(int v) {
    this->vertices.push_back(v);
}

vector<float> Bone::getWeights() {
    return this->weights;
}

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

void Bone::addWeight(float w) {
    this->weights.push_back(w);
}

vector<Bone> Bone::getChildren() {
    return this->children;
}

void Bone::addChild(Bone b) {
    this->children.push_back(b);
}
