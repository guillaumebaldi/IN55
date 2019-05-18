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

string Bone::getId() {
    return this->id;
}

void Bone::setId(string id) {
    this->id = id;
}
