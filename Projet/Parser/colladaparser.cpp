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

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        parseMeshes(scene->mMeshes[i]);
    }

    Model m(QMatrix4x4(scene->mRootNode->FindNode("Model")->mTransformation[0]));
    vector<Bone> bones;
    parseBones(scene, scene->mRootNode->FindNode("Armature"), bones);
    m.setBones(bones);
    m.setMeshes(this->meshes);
    /*std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getVertices().size() << " " << m.getMeshes()[0].getVertices()[0].x() << "/" << m.getMeshes()[0].getVertices()[0].y()<< "/" << m.getMeshes()[0].getVertices()[0].z() << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getVertices().size() << " " << m.getMeshes()[1].getVertices()[1].x() << "/" << m.getMeshes()[1].getVertices()[0].y()<< "/" << m.getMeshes()[1].getVertices()[0].z() << "\n";
    std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getNormales().size() << " " << m.getMeshes()[0].getNormales()[0].x() << "/" << m.getMeshes()[0].getNormales()[0].y()<< "/" << m.getMeshes()[0].getNormales()[0].z() << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getNormales().size() << " " << m.getMeshes()[1].getNormales()[0].x() << "/" << m.getMeshes()[1].getNormales()[0].y()<< "/" << m.getMeshes()[1].getNormales()[0].z() << "\n";
    std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getIndices().size() << " " << m.getMeshes()[0].getIndices()[0] << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getIndices().size() << " " << m.getMeshes()[1].getIndices()[0] << "\n";*/
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
        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D &vertex = mesh->mVertices[i];
            QVector3D vec(vertex.x, vertex.y, vertex.z);
            this->vertices.push_back(vec);
            m.addVertex(vec);

            aiVector3D &normal = mesh->mNormals[i];
            QVector3D norm(normal.x, normal.y, normal.z);
            this->normales.push_back(norm);
            m.addNormal(norm);
        }
    }
    if(mesh->mNumFaces > 0) {
        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace *face = &mesh->mFaces[i];

            for(unsigned int j = 0; j < face->mNumIndices; j++) {
                this->indices.push_back(face->mIndices[j]);

                m.addIndex(face->mIndices[j]);
            }
        }
    }
    this->meshes.push_back(m);
}


