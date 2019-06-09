#include "colladaparser.h"


ColladaParser::ColladaParser() {

}

Model ColladaParser::loadColladaFile(string& file) {
    Assimp::Importer importer;
    scene = importer.ReadFile(file,
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

    parseMeshes(scene->mMeshes[1]);

    aiMatrix4x4 transform = scene->mRootNode->mTransformation;
    QMatrix4x4 mat(transform.a1, transform.a2, transform.a3, transform.a4,
                   transform.b1, transform.b2, transform.b3, transform.b4,
                   transform.c1, transform.c2, transform.c3, transform.c4,
                   transform.d1, transform.d2, transform.d3, transform.d4);
    m.setTransform(mat);

    for(int i = 0; i < bones.size(); i++) {
        for(int j = i; j < bones.size(); j++) {
            if(bones[j].getParent() == bones[i].getTransform()) {
                bones[i].addChild(bones[j]);
            }
        }
    }

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

void ColladaParser::parseMeshes(aiMesh* mesh) {
    Mesh m;
    if(mesh->mNumVertices > 0) {
        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D &vertex = mesh->mVertices[i];
            QVector3D vec(vertex.x, vertex.y, vertex.z);
            m.addVertex(vec);

            aiVector3D &normal = mesh->mNormals[i];
            QVector3D norm(normal.x, normal.y, normal.z);
            m.addNormal(norm);
        }
    }
    if(mesh->mNumFaces > 0) {
        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace *face = &mesh->mFaces[i];

            for(unsigned int j = 0; j < face->mNumIndices; j++) {
                m.addIndex(face->mIndices[j]);
            }
        }
    }
    if(mesh->HasBones()) {
        for(unsigned int i = 0; i < mesh->mNumBones; i++) {
            aiBone *bone = mesh->mBones[i];
            const aiNode *p = getNode(scene, mesh->mBones[i]->mName);
            Bone b;
            b.setNumber(this->bones.size());
            b.setId(bone->mName.C_Str());
            aiMatrix4x4 parent = p->mParent->mTransformation;
            string n = p->mParent->mName.C_Str();
            if(!n.compare("Armature")) {
                parent = scene->mRootNode->mTransformation;
            }
            b.setParent(QMatrix4x4(parent.a1, parent.a2, parent.a3, parent.a4,
                                   parent.b1, parent.b2, parent.b3, parent.b4,
                                   parent.c1, parent.c2, parent.c3, parent.c4,
                                   parent.d1, parent.d2, parent.d3, parent.d4));
            aiMatrix4x4 t = p->mTransformation;
            b.setTransform(QMatrix4x4(t.a1, t.a2, t.a3, t.a4,
                                      t.b1, t.b2, t.b3, t.b4,
                                      t.c1, t.c2, t.c3, t.c4,
                                      t.d1, t.d2, t.d3, t.d4));
            aiMatrix4x4 offset = bone->mOffsetMatrix;
            b.setOffset(QMatrix4x4(offset.a1, offset.a2, offset.a3, offset.a4,
                                   offset.b1, offset.b2, offset.b3, offset.b4,
                                   offset.c1, offset.c2, offset.c3, offset.c4,
                                   offset.d1, offset.d2, offset.d3, offset.d4));
            for(unsigned int j = 0; j < bone->mNumWeights; j++) {
                b.addVertex(bone->mWeights[j].mVertexId);
                b.addWeight(bone->mWeights[j].mWeight);
            }
            this->bones.push_back(b);
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
    if(!scene->HasAnimations()) {
        QMessageBox::warning(0, "test", "Pas d'animations");
        exit(-1);
    }

    for(unsigned int i = 0; i < scene->mNumAnimations; i++) {
        string nTemp = file.substr(file.find("_")+1);
        string name(nTemp.begin(), std::find(nTemp.begin(), nTemp.end(), '.'));
        Animation a(name);
        const aiAnimation *anim = scene->mAnimations[i];
        a.setDuration(anim->mDuration);
        for(unsigned int b = 0; b < this->bones.size(); b++) {
            const aiNodeAnim * nodeAnim = anim->mChannels[b];
            string n = nodeAnim->mNodeName.C_Str();
            if(n.compare("Armature_JambeIK_L") &&
                    n.compare("Armature_JambeIK_R") &&
                    n.compare("Armature_PoleTarget_L") &&
                    n.compare("Armature_PoleTarget_R")) {
                AnimBone animBone(n);
                for(unsigned int nPos = 0; nPos < nodeAnim->mNumPositionKeys; nPos++) {
                    animBone.addPosition(nodeAnim->mPositionKeys[nPos]);
                }
                for(unsigned int nSca = 0; nSca < nodeAnim->mNumScalingKeys; nSca++) {
                    animBone.addScale(nodeAnim->mScalingKeys[nSca]);
                }
                for(unsigned int nRot = 0; nRot < nodeAnim->mNumRotationKeys; nRot++) {
                    animBone.addRotation(nodeAnim->mRotationKeys[nRot]);
                }
                a.addAnimBone(animBone);
            }
        }
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
