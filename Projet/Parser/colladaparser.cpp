#include "colladaparser.h"

ColladaParser::ColladaParser() {

}

Model ColladaParser::loadColladaFile(string& file) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file,
          aiProcess_CalcTangentSpace       |
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          aiProcess_SortByPType);

    if(!scene) {
        QMessageBox::warning(0, "Fichier .dae manquant", "Le fichier .dae n'a pas pu être ouvert, vérifiez qu'il existe bien.");
        exit(-1);
    }
    if(!scene->HasMeshes()) {
        QMessageBox::warning(0, "test", "Pas de meshes");
        exit(-1);
    }

    for(int i = 0; i < scene->mNumMeshes; i++) {
        parseMeshes(scene->mMeshes[i]);
    }

    Model m(QMatrix4x4(scene->mRootNode->FindNode("Model")->mTransformation[0]));
    vector<Bone> bones;
    parseBones(scene, scene->mRootNode->FindNode("Armature"), bones);
    m.setBones(bones);
    m.setMeshes(this->meshes);
    return m;
}

void ColladaParser::parseBones(const aiScene* scene, aiNode *node, vector<Bone>& bones) {
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        Bone newBone;
        newBone.setId(node->mChildren[i]->mName.C_Str());
        newBone.setTransform(QMatrix4x4(node->mChildren[i]->mTransformation[0]));
        bones.push_back(newBone);
        parseBones(scene, node->mChildren[i], bones);
    }
}

void ColladaParser::parseMeshes(aiMesh* mesh) {
    Mesh m;
    m.setId(mesh->mName.C_Str());
    if(mesh->mNumVertices > 0) {
        for(int i = 0; i < mesh->mNumVertices; i++) {
            vector<float> vertices;
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);
            m.setVertices(vertices);
            this->meshes.push_back(m);
        }
    }
}


