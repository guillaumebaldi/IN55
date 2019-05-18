#include "model.h"

Model::Model() {

}

Model::Model(QMatrix4x4 transform)
{
    this->transform = transform;
}

Model::Model(QMatrix4x4 transform , vector<Bone> bones) {
    this->transform = transform;
    this->bones = bones;
    this->nbBones = bones.size();
}

Model::Model(QMatrix4x4 transform , vector<Bone> bones, vector<Mesh> meshes) {
    this->transform = transform;
    this->bones = bones;
    this->nbBones = bones.size();
    this->meshes = meshes;
    this->nbMeshes = meshes.size();
}

QMatrix4x4 Model::getTransform() {
    return this->transform;
}

void Model::setTransform(QMatrix4x4 m) {
    this->transform = m;
}

void Model::setBones(vector<Bone> bones) {
    this->bones = bones;
}

vector<Bone> Model::getBones() {
    return this->bones;
}

void Model::addBone(Bone b) {
    this->bones.push_back(b);
    this->nbBones++;
}

void Model::setMeshes(vector<Mesh> meshes) {
    this->meshes = meshes;
}

vector<Mesh> Model::getMeshes() {
    return this->meshes;
}

void Model::addMesh(Mesh m) {
    this->meshes.push_back(m);
    this->nbMeshes++;
}
