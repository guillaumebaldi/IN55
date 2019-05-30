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

Model::Model(QMatrix4x4 transform , vector<Bone> bones, vector<Mesh> meshes, vector<Animation> animations) {
    this->transform = transform;
    this->bones = bones;
    this->nbBones = bones.size();
    this->meshes = meshes;
    this->nbMeshes = meshes.size();
    this->animations = animations;
    this->nbAnimations = animations.size();
}

QMatrix4x4 Model::getTransform() {
    return this->transform;
}

void Model::setTransform(QMatrix4x4 m) {
    this->transform = m;
}

void Model::setBones(vector<Bone> bones) {
    this->bones = bones;
    this->nbBones = bones.size();
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
    this->nbMeshes = meshes.size();
}

vector<Mesh> Model::getMeshes() {
    return this->meshes;
}

void Model::addMesh(Mesh m) {
    this->meshes.push_back(m);
    this->nbMeshes++;
}

void Model::setAnimations(vector<Animation> animations) {
    this->animations = animations;
    this->nbAnimations = animations.size();
}

vector<Animation> Model::getAnimations() {
    return this->animations;
}

void Model::addAnimation(Animation a) {
    this->animations.push_back(a);
    this->nbAnimations++;
}
