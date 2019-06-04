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
    QMatrix4x4 mat(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    Model m(mat);
    vector<Bone> bones;
    parseBones(scene, scene->mRootNode->FindNode("Armature"), bones);
    m.setBones(bones);
    m.setMeshes(this->meshes);

    string s = "resources\\human_walk.dae";
    parseAnimations(s);
    s = "resources\\human_run.dae";
    parseAnimations(s);
    s = "resources\\human_jump.dae";
    parseAnimations(s);
    s = "resources\\human_hello.dae";
    parseAnimations(s);
    s = "resources\\human_idle.dae";
    parseAnimations(s);

    m.setAnimations(this->animations);
    /*std::cout << m.getAnimations()[0].getId() << " ";
    std::cout << m.getAnimations()[1].getId() << " ";
    std::cout << m.getAnimations()[2].getId() << " ";
    std::cout << m.getAnimations()[3].getId() << " ";
    std::cout << m.getAnimations()[4].getId() << " ";*/
    /*std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getVertices().size() << " " << m.getMeshes()[0].getVertices()[0].x() << "/" << m.getMeshes()[0].getVertices()[0].y()<< "/" << m.getMeshes()[0].getVertices()[0].z() << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getVertices().size() << " " << m.getMeshes()[1].getVertices()[1].x() << "/" << m.getMeshes()[1].getVertices()[0].y()<< "/" << m.getMeshes()[1].getVertices()[0].z() << "\n";
    std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getNormales().size() << " " << m.getMeshes()[0].getNormales()[0].x() << "/" << m.getMeshes()[0].getNormales()[0].y()<< "/" << m.getMeshes()[0].getNormales()[0].z() << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getNormales().size() << " " << m.getMeshes()[1].getNormales()[0].x() << "/" << m.getMeshes()[1].getNormales()[0].y()<< "/" << m.getMeshes()[1].getNormales()[0].z() << "\n";
    std::cout << m.getMeshes()[0].getId() << " " << m.getMeshes()[0].getIndices().size() << " " << m.getMeshes()[0].getIndices()[0] << "\n";
    std::cout << m.getMeshes()[1].getId() << " " << m.getMeshes()[1].getIndices().size() << " " << m.getMeshes()[1].getIndices()[0] << "\n";*/
    /*std::cout << scene->mAnimations[0]->mChannels[0]->mPositionKeys[0].mValue.x << " " << scene->mAnimations[0]->mChannels[0]->mPositionKeys[0].mValue.y << " " << scene->mAnimations[0]->mChannels[0]->mPositionKeys[0].mValue.z << "\n";
    std::cout << scene->mAnimations[0]->mChannels[0]->mRotationKeys[0].mValue.w << " " << scene->mAnimations[0]->mChannels[0]->mRotationKeys[0].mValue.x << " " << scene->mAnimations[0]->mChannels[0]->mRotationKeys[0].mValue.y<< "\n";
    std::cout << scene->mAnimations[0]->mChannels[0]->mScalingKeys[0].mValue.x << " " << scene->mAnimations[0]->mChannels[0]->mScalingKeys[0].mValue.y << " " << scene->mAnimations[0]->mChannels[0]->mScalingKeys[0].mValue.z << "\n";*/
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
    //m.setId(mesh->mName.C_Str());
    if(mesh->mNumVertices > 0) {
        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D &vertex = mesh->mVertices[i];
            Vertex vert;
            vert.position.setX(vertex.x);
            vert.position.setX(vertex.y);
            vert.position.setX(vertex.z);
            this->vertices.push_back(vert.position);


            aiVector3D &normal = mesh->mNormals[i];
            vert.normal.setX(normal.x);
            vert.normal.setX(normal.y);
            vert.normal.setX(normal.z);
            this->normales.push_back(vert.normal);
            m.addVertex(vert);
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

void ColladaParser::parseAnimations(string &file) {
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

    for(unsigned int i = 0; i < scene->mNumAnimations; i++) {
        string nTemp = file.substr(file.find("_")+1);
        string name(nTemp.begin(), std::find(nTemp.begin(), nTemp.end(), '.'));
        Animation a(name);
        const aiAnimation *anim = scene->mAnimations[i];
        vector<double> times;
        for(unsigned int b = 0; b < anim->mNumChannels; b++) {
            const aiNodeAnim * nodeAnim = anim->mChannels[b];
            AnimBone animBone(nodeAnim->mNodeName.C_Str());
            vector<QVector3D> pos;
            vector<QVector3D> scal;
            vector<QQuaternion> rot;
            for(unsigned int nPos = 0; nPos < nodeAnim->mNumPositionKeys; nPos++) {
                if(std::find(times.begin(), times.end(), nodeAnim->mPositionKeys[nPos].mTime) != times.end()) {
                }
                else {
                    times.push_back(nodeAnim->mPositionKeys[nPos].mTime);
                }
                aiVector3D &p = nodeAnim->mPositionKeys[nPos].mValue;
                QVector3D vec(p.x, p.y, p.z);
                pos.push_back(vec);
            }
            for(unsigned int nSca = 0; nSca < nodeAnim->mNumScalingKeys; nSca++) {
                aiVector3D &s = nodeAnim->mScalingKeys[nSca].mValue;
                QVector3D vec(s.x, s.y, s.z);
                scal.push_back(vec);
            }
            for(unsigned int nRot = 0; nRot < nodeAnim->mNumRotationKeys; nRot++) {
                aiQuaternion &r = nodeAnim->mRotationKeys[nRot].mValue;
                QQuaternion quat(r.w, r.x, r.y, r.z);
                rot.push_back(quat);
            }
            animBone.setPositions(pos);
            animBone.setScales(scal);
            animBone.setRotations(rot);
            a.addAnimBone(animBone);
        }
        a.setTimes(times);
        this->animations.push_back(a);
    }
}


