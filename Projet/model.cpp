#include "model.h"

Model::Model() {

}

/*
 * Returns transform of model
 */
QMatrix4x4 Model::getTransform() {
    return this->transform;
}

/*
 * Sets transform of model
 */
void Model::setTransform(QMatrix4x4 m) {
    this->transform = m;
}

/*
 * Sets bones
 */
void Model::setBones(vector<Bone> bones) {
    this->bones = bones;
    this->nbBones = bones.size();
}

/*
 * Returns bones
 */
vector<Bone> Model::getBones() {
    return this->bones;
}

/*
 * Returns a bone with its id
 */
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

/*
 * Returns a bone with its number
 */
Bone Model::getBoneByNumber(int number) {
    Bone b;
    for(Bone bone : bones) {
        if(bone.getNumber() == number) {
            b = bone;
        }
    }
    return b;
}

/*
 * Sets mesh
 */
void Model::setMeshes(vector<Mesh> meshes) {
    this->meshes = meshes;
    this->nbMeshes = meshes.size();
}

/*
 * Returns mesh
 */
vector<Mesh> Model::getMeshes() {
    return this->meshes;
}

/*
 * Sets animations
 */
void Model::setAnimations(vector<Animation> animations) {
    this->animations = animations;
    this->nbAnimations = animations.size();
}

/*
 * Returns animations
 */
vector<Animation> Model::getAnimations() {
    return this->animations;
}

/*
 * Returns indices of bones on which a vertex acts
 */
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
}

/*
 * Returns weights of bones on which a vertex acts
 */
QVector4D Model::getWeightsBone(int vertex, QVector4D indices) {
    QVector4D weights = QVector4D(getBoneByNumber(indices.x()).getWeight(vertex),
                                  getBoneByNumber(indices.y()).getWeight(vertex),
                                  getBoneByNumber(indices.z()).getWeight(vertex),
                                  getBoneByNumber(indices.w()).getWeight(vertex));
    return weights;
}
