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

    for(unsigned int i = 1; i < scene->mNumMeshes; i++) {
        parseMeshes(scene->mMeshes[i], scene);
    }
    QMatrix4x4 mat(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    Model m(mat);
    m.setBones(this->bones);
    m.setMeshes(this->meshes);

    string s = "resources\\human2_idle.dae";
    parseAnimations(s);
    s = "resources\\human2_hello.dae";
    parseAnimations(s);
    s = "resources\\human2_walk.dae";
    parseAnimations(s);
    s = "resources\\human2_run.dae";
    parseAnimations(s);
    s = "resources\\human2_jump.dae";
    parseAnimations(s);

    m.setAnimations(this->animations);

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

void ColladaParser::parseMeshes(aiMesh* mesh, const aiScene* scene) {
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
        /*for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D &vertex = mesh->mVertices[i];
            QVector3D veci(-vertex.x, vertex.y, vertex.z);
            this->vertices.push_back(veci);
            m.addVertex(veci);

            aiVector3D &normal = mesh->mNormals[i];
            QVector3D normi(-normal.x, normal.y, normal.z);
            this->normales.push_back(normi);
            m.addNormal(normi);
        }*/
    }
    if(mesh->mNumFaces > 0) {
        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace *face = &mesh->mFaces[i];

            for(unsigned int j = 0; j < face->mNumIndices; j++) {
                this->indices.push_back(face->mIndices[j]);

                m.addIndex(face->mIndices[j]);
            }
        }
        /*for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace *face = &mesh->mFaces[i];

            for(unsigned int j = 0; j < face->mNumIndices; j++) {
                this->indices.push_back(this->vertices.size()/2 + face->mIndices[j]);

                m.addIndex(this->vertices.size()/2 + face->mIndices[j]);
            }
        }*/
    }
    if(mesh->HasBones()) {
        for(unsigned int i = 0; i < mesh->mNumBones; i++) {
            aiBone *bone = mesh->mBones[i];
            const aiNode *p = getNode(scene, mesh->mBones[i]->mName);
            Bone b;
            b.setNumber(this->bones.size());
            b.setId(bone->mName.C_Str());
            b.setParent(p->mParent->mName.C_Str());
            /*if(!b.getParent().compare("Armature")) {
                b.setParent(b.getId());
            }*/
            b.setTransform(QMatrix4x4(bone->mOffsetMatrix[0]));
            for(unsigned int j = 0; j < bone->mNumWeights; j++) {
                b.addVertex(bone->mWeights[j].mVertexId);
                b.addWeight(bone->mWeights[j].mWeight);
            }
            this->bones.push_back(b);
            /*if(b.getId().back() == 'L') {
                this->bones.push_back(b);
                Bone invB;
                invB.setNumber(this->bones.size());
                string n = bone->mName.C_Str();
                if(b.getParent().back() == 'L') {
                    invB.setParent(b.getParent().substr(0, b.getParent().size()-1) + "R");
                }
                else {
                    invB.setParent(b.getParent());
                }
                invB.setId(n.substr(0, n.size()-1) + "R");
                invB.setTransform(QMatrix4x4(bone->mOffsetMatrix[0]));
                for(unsigned int j = 0; j < bone->mNumWeights; j++) {
                    invB.addVertex(bone->mWeights[j].mVertexId + this->vertices.size()/2);
                    invB.addWeight(bone->mWeights[j].mWeight);
                }
                this->bones.push_back(invB);
            }
            else {
                for(unsigned int j = 0; j < bone->mNumWeights; j++) {
                    b.addVertex(bone->mWeights[j].mVertexId + this->vertices.size()/2);
                    b.addWeight(bone->mWeights[j].mWeight);
                }
                this->bones.push_back(b);
            }*/
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
            string n = nodeAnim->mNodeName.C_Str();
            if(n.compare("Armature_JambeIK_L") &&
                    n.compare("Armature_JambeIK_R") &&
                    n.compare("Armature_PoleTarget_L") &&
                    n.compare("Armature_PoleTarget_R")) {
                AnimBone animBone(n);
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
        }
        a.setTimes(times);
        this->animations.push_back(a);
    }
}

const aiNode *getNode(const aiScene *scene, aiString name) {
    if (name == scene->mRootNode->mName)
        return &(*scene->mRootNode);
    else
        return getChildNode(name, scene->mRootNode);
}

const aiNode *getChildNode(aiString name, const aiNode *node) {
    if (name == node->mName)
        return node;
    else {
        const aiNode *nd = NULL;
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            nd = getChildNode(name, node->mChildren[i]);
            if (nd != NULL) return nd;
        }
        return NULL;
    }
}


