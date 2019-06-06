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

Bone Model::getBone(string id) {
    Bone b;
    for(Bone bone : bones) {
        if(!(bone.getId()).compare(id)) {
            b = bone;
        }
    }
    if(!id.compare("")) {
        b = getBone(id);
    }
    return b;
}

Bone Model::getBoneByNumber(int number) {
    Bone b;
    for(Bone bone : bones) {
        if(bone.getNumber() == number) {
            b = bone;
        }
    }
    return b;
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

Animation Model::getAnimation(string id) {
    Animation a;
    for(Animation anim : animations) {
        if(!(anim.getId()).compare(id)) {
            a = anim;
        }
    }
    return a;
}

QVector4D Model::getIndicesBone(int vertex) {
    QVector4D indices = QVector4D(-1.0, -1.0, -1.0, -1.0);

    int a = 0;
    for(unsigned int i = 0; i < getBones().size(); i++) {
        vector<int> vertices = getBones()[i].getVertices();
        if(std::find(vertices.begin(), vertices.end(), vertex) != vertices.end()) {
            if(a == 0) {
                indices.setX(getBones()[i].getNumber());
            }
            else if(a == 1) {
                indices.setY(getBones()[i].getNumber());
            }
            else if(a == 2) {
                indices.setZ(getBones()[i].getNumber());
            }
            else if(a == 3) {
                indices.setW(getBones()[i].getNumber());
            }
            a++;
        }
    }
    return indices;
    /*vector<int> indices;
    for(unsigned int i = 0; i < getBones().size(); i++) {
        vector<int> vertices = getBones()[i].getVertices();
        if(std::find(vertices.begin(), vertices.end(), vertex) != vertices.end()) {
            indices.push_back(getBones()[i].getNumber());
        }
    }
    size_t size = indices.size();
    for(unsigned int i = size; i < 5; i++) {
        indices.push_back(-1);
    }
    return indices;*/
}

QVector4D Model::getWeightsBone(int vertex, QVector4D indices) {
    QVector4D weights = QVector4D(getBoneByNumber(indices.x()).getWeight(vertex),
                                  getBoneByNumber(indices.y()).getWeight(vertex),
                                  getBoneByNumber(indices.z()).getWeight(vertex),
                                  getBoneByNumber(indices.w()).getWeight(vertex));
    return weights;
    /*vector<float> weights;
    for(unsigned int i = 0; i < indices.size(); i++) {
        weights.push_back(getBoneByNumber(indices[i]).getWeight(vertex));
    }
    return weights;*/
}
