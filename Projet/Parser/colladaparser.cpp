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

    for(unsigned int i = 1; i < scene->mNumMeshes; i++) {
        parseMeshes(scene->mMeshes[i], scene);
    }
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

    vector<QMatrix4x4> transformations = getTransformations(1, m.getAnimations()[0]);
    /*for(int i = 0; i < m.getBones().size(); i++){
        std::cout << transformations[i].data()[0] << " "<< transformations[i].data()[1] << " "<< transformations[i].data()[2] << " "<< transformations[i].data()[3] << " "<< transformations[i].data()[4] << " "<< transformations[i].data()[5] << " "<< transformations[i].data()[6] << " "<< transformations[i].data()[7] << " "<< transformations[i].data()[8] << " "<< transformations[i].data()[9] << " "<< transformations[i].data()[10] << " "<< transformations[i].data()[11] << " "<< transformations[i].data()[12] << " "<< transformations[i].data()[13] << " "<< transformations[i].data()[14] << " "<< transformations[i].data()[15] << "\n";
    }*/
    this->idleTrans = transformations;

    vector<QMatrix4x4> trans2 = getTransformations(0.8, m.getAnimations()[2]);
    this->walkTrans = trans2;

    return m;
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
        vector<double> times;
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
                    if(std::find(times.begin(), times.end(), nodeAnim->mPositionKeys[nPos].mTime) != times.end()) {
                    }
                    else {
                        times.push_back(nodeAnim->mPositionKeys[nPos].mTime);
                    }
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
        a.setTimes(times);
        this->animations.push_back(a);
    }
}


/*vector<QMatrix4x4> ColladaParser::getTransformations(double t, Animation anim, const aiScene *scene) {
    vector<QMatrix4x4> transformations;

    double time = t * anim.getDuration();

    vector<AnimBone> bones = anim.getAnimBones();
    for(unsigned int i = 0; i < bones.size(); i++) {
        calculateTransformations(time, anim.getAnimBones()[i], transformations);
    }

    return transformations;
}

void ColladaParser::calculateTransformations(double t, AnimBone bone, vector<QMatrix4x4> &transformations) {
    aiMatrix4x4 nodeMatrix = m.getBone(bone.getId()).getTransform();

    QMatrix4x4 nodeTransform;

    for(unsigned int i = 0; i < bone.getPositions().size(); i++) {
        QMatrix4x4 transMatrix = CalcInterpolatedPosition(t, bone);
        QMatrix4x4 scaleMatrix = CalcInterpolatedScale(t, bone);
        QMatrix4x4 rotationMatrix = CalcInterpolatedRotation(t, bone);

        nodeTransform = transMatrix * rotationMatrix * scaleMatrix;
        aiMatrix4x4 parent = m.getBone(bone.getId()).getTransform();
        QMatrix4x4 parentTransform = QMatrix4x4(parent.a1, parent.a2, parent.a3, parent.a4,
                                                parent.b1, parent.b2, parent.b3, parent.b4,
                                                parent.c1, parent.c2, parent.c3, parent.c4,
                                                parent.d1, parent.d2, parent.d3, parent.d4);
        //std::cout << nodeTransform.data()[0] << " "<< nodeTransform.data()[1] << " "<< nodeTransform.data()[2] << " "<< nodeTransform.data()[3] << " "<< nodeTransform.data()[4] << " "<< nodeTransform.data()[5] << " "<< nodeTransform.data()[6] << " "<< nodeTransform.data()[7] << " "<< nodeTransform.data()[8] << " "<< nodeTransform.data()[9] << " "<< nodeTransform.data()[10] << " "<< nodeTransform.data()[11] << " "<< nodeTransform.data()[12] << " "<< nodeTransform.data()[13] << " "<< nodeTransform.data()[14] << " "<< nodeTransform.data()[15] << "\n";

        QMatrix4x4 transfo = parentTransform * nodeTransform;
        QMatrix4x4 boneTransform = QMatrix4x4(nodeMatrix.a1, nodeMatrix.a2, nodeMatrix.a3, nodeMatrix.a4,
                                              nodeMatrix.b1, nodeMatrix.b2, nodeMatrix.b3, nodeMatrix.b4,
                                              nodeMatrix.c1, nodeMatrix.c2, nodeMatrix.c3, nodeMatrix.c4,
                                              nodeMatrix.d1, nodeMatrix.d2, nodeMatrix.d3, nodeMatrix.d4);
        transformations.push_back(m.getTransform().inverted() * transfo * boneTransform);
    }
}*/


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

/*QMatrix4x4 ColladaParser::CalcInterpolatedPosition(float t, AnimBone bone) {
    if (bone.getNbPositions() == 1) {
        return QMatrix4x4(1, 0, 0, bone.getPosition(0).mValue.x,
                          0, 1, 0, bone.getPosition(0).mValue.y,
                          0, 0, 1, bone.getPosition(0).mValue.z,
                          0, 0, 0, 1);
    }

    unsigned int id = bone.getIdPosition(t);
    unsigned int nextId = id + 1;
    float diff = bone.getPosition(nextId).mTime - bone.getPosition(id).mTime;
    float inter = (t - (float)bone.getPosition(id).mTime) / diff;

    aiVector3D beginPos = bone.getPosition(id).mValue;
    aiVector3D endPos = bone.getPosition(nextId).mValue;
    aiVector3D pos = (1 - inter) * beginPos + inter * endPos;

    QMatrix4x4 translation;
    translation.translate(pos.x, pos.y, pos.z);
    return translation;
}

QMatrix4x4 ColladaParser::CalcInterpolatedScale(float t, AnimBone bone) {
    if (bone.getNbScales() == 1) {
        return QMatrix4x4(bone.getScale(0).mValue.x, 0, 0, 0,
                          0, bone.getScale(0).mValue.y, 0, 0,
                          0, 0, bone.getScale(0).mValue.z, 0,
                          0, 0, 0, 1);
    }

    unsigned int id = bone.getIdScale(t);
    unsigned int nextId = id + 1;
    float diff = bone.getScale(nextId).mTime - bone.getScale(id).mTime;
    float inter = (t - (float)bone.getScale(id).mTime) / diff;

    aiVector3D beginScale = bone.getScale(id).mValue;
    aiVector3D endScale = bone.getScale(nextId).mValue;
    aiVector3D sca = (1 - inter) * beginScale + inter * endScale;

    QMatrix4x4 scale;
    scale.scale(sca.x, sca.y, sca.z);
    return scale;
}

QMatrix4x4 ColladaParser::CalcInterpolatedRotation(float t, AnimBone bone) {
    if (bone.getNbRotations() == 1) {
        aiMatrix3x3 rota = bone.getRotation(0).mValue.GetMatrix();
        return QMatrix4x4(rota.a1, rota.a2, rota.a3, 0,
                          rota.b1, rota.b2, rota.b3, 0,
                          rota.c1, rota.c2, rota.c3, 0,
                          0, 0, 0, 1);
    }


    unsigned int id = bone.getIdRotation(t);
    unsigned int nextId = id + 1;
    float diff = bone.getRotation(nextId).mTime - bone.getRotation(id).mTime;
    float inter = (t - (float)bone.getRotation(id).mTime) / diff;

    aiQuaternion beginRotation = bone.getRotation(id).mValue;
    aiQuaternion endRotation = bone.getRotation(nextId).mValue;
    aiQuaternion rot;
    aiQuaternion::Interpolate(rot, beginRotation, endRotation, inter);
    rot.Normalize();

    QQuaternion r = QQuaternion(rot.w, rot.x, rot.y, rot.z);
    QMatrix4x4 rotation;
    rotation.rotate(r);
    return rotation;
}*/


vector<QMatrix4x4> ColladaParser::getTransformations(double t, Animation anim){
    vector<QMatrix4x4> transformationList;

    double time = t * anim.getDuration();

    QMatrix4x4 parent = m.getBone(anim.getAnimBones()[0].getId()).getParent();
    calcTransformations(time, anim, anim.getAnimBones()[0], transformationList, parent);

    return transformationList;
}

void ColladaParser::calcTransformations(double t, Animation anim, AnimBone bone, vector<QMatrix4x4> &transformationList, QMatrix4x4 parent){
    Bone b = m.getBone(bone.getId());
    QMatrix4x4 boneTransform;

    for(unsigned int i = 0; i < 1; i++) {
        QMatrix4x4 posMatrix = calcInterpolatedPosition(t, bone);
        QMatrix4x4 rotMatrix = calcInterpolatedRotation(t, bone);
        QMatrix4x4 scaMatrix = calcInterpolatedScale(t, bone);

        boneTransform = posMatrix * rotMatrix * scaMatrix;
    }
    QMatrix4x4 transformation = parent * boneTransform;
    transformationList.push_back(m.getTransform().inverted() * transformation * b.getOffset());
    for(unsigned int i = 0; i < b.getChildren().size(); i++) {
        AnimBone a = anim.getAnimBones()[b.getChildren()[i].getNumber()];
        calcTransformations(t, anim, a, transformationList, transformation);
    }
}

QMatrix4x4 ColladaParser::calcInterpolatedPosition(double t, AnimBone bone){
    QMatrix4x4 identity;
    identity.setToIdentity();

    if (bone.getNbPositions() == 1) {
        return QMatrix4x4(1,0,0, bone.getPositions()[0].mValue.x,
                          0,1,0, bone.getPositions()[0].mValue.y,
                          0,0,1, bone.getPositions()[0].mValue.z,
                          0,0,0,1);
    }
    if (bone.getNbPositions() == 0) {
        return identity;
    }

    int id = 0;
    for (int i = 0 ; i < bone.getNbPositions() - 1 ; ++i) {
        if (t < bone.getPositions()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    int nextId = id +1;
    if(nextId >= bone.getNbPositions() ){
        return identity;
    }

    float diff = bone.getPositions()[nextId].mTime - bone.getPositions()[id].mTime;
    float f = (t - bone.getPositions()[id].mTime) / diff;

    aiVector3D startPos = bone.getPositions()[id].mValue;
    aiVector3D endPos = bone.getPositions()[nextId].mValue;
    aiVector3D diffPos = endPos - startPos;
    aiVector3D inter = startPos + f * diffPos;

    QMatrix4x4 transformation;
    transformation.translate(inter.x, inter.y, inter.z);
    return transformation;
}

QMatrix4x4 ColladaParser::calcInterpolatedRotation(double t, AnimBone bone){
    QMatrix4x4 identity;
    aiMatrix3x3 rotationMatrix;
    identity.setToIdentity();

    if (bone.getNbRotations() == 1) {
        rotationMatrix = bone.getRotations()[0].mValue.GetMatrix();
        return QMatrix4x4(rotationMatrix.a1, rotationMatrix.a2, rotationMatrix.a3, 0,
                rotationMatrix.b1, rotationMatrix.b2, rotationMatrix.b3, 0,
                rotationMatrix.c1, rotationMatrix.c2, rotationMatrix.c3, 0,
                0,0,0,1) ;
    }

    if (bone.getNbRotations() == 0) {
        return identity;
    }

    int id = 0;
    for (int i = 0 ; i < bone.getNbRotations() - 1 ; ++i) {
        if (t < bone.getRotations()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    int nextId = id +1;
    if(nextId >= bone.getNbRotations() ){
        return identity;
    }

    float diff = bone.getRotations()[nextId].mTime - bone.getRotations()[id].mTime;
    float f = (t - bone.getRotations()[id].mTime) / diff;

    aiQuaternion startRot = bone.getRotations()[id].mValue;
    aiQuaternion endRot = bone.getRotations()[nextId].mValue;
    aiQuaternion inter;
    aiQuaternion::Interpolate(inter, startRot, endRot, f);
    inter.Normalize();

    QQuaternion quat = QQuaternion(inter.w, inter.x, inter.y, inter.z);
    QMatrix4x4 rotation;
    rotation.rotate(quat);
    return rotation;
}

QMatrix4x4 ColladaParser::calcInterpolatedScale(double t, AnimBone bone){
    QMatrix4x4 identity;
    identity.setToIdentity();

    if (bone.getNbScales() == 1) {
        return QMatrix4x4(bone.getScales()[0].mValue.x,0,0,0,
                0,bone.getScales()[0].mValue.y,0,0,
                0,0,bone.getScales()[0].mValue.z,0,
                0,0,0,1);
    }
    if (bone.getNbScales() == 0) {
        return identity;
    }

    int id = 0;
    for (int i = 0 ; i < bone.getNbScales() - 1 ; ++i) {
        if (t < bone.getScales()[i + 1].mTime) {
            id = i;
            break;
        }
    }

    int nextId = id + 1;
    if(nextId >= bone.getNbScales() ){
        return identity;
    }

    float diff = bone.getScales()[nextId].mTime - bone.getScales()[id].mTime;
    float f = (t - bone.getScales()[id].mTime) / diff;

    aiVector3D startSca = bone.getScales()[id].mValue;
    aiVector3D endSca = bone.getScales()[nextId].mValue;
    aiVector3D diffSca = endSca - startSca;
    aiVector3D inter = startSca + f * diffSca;

    QMatrix4x4 scale;
    scale.scale(inter.x, inter.y, inter.z);
    return scale;
}

