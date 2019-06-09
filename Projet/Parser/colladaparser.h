#ifndef COLLADAPARSER_H
#define COLLADAPARSER_H

#include <QMessageBox>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector>

#include "model.h"
#include "bone.h"
#include "mesh.h"
#include "animbone.h"
#include "animation.h"

#include <iostream>
#include <vector>
using namespace std;
#include <algorithm>

class ColladaParser
{
public:
    ColladaParser();
    Model loadColladaFile(string& file);
    void parseMeshes(aiMesh* mesh, const aiScene* scene);
    void parseAnimations(string& file);

    vector<QMatrix4x4> getTransformations(double t, Animation anim);
    /*vector<QMatrix4x4> getTransformations(double t, Animation anim, const aiScene *scene);
    void calculateTransformations(double t, AnimBone bone, vector<QMatrix4x4> &transformations);*/
    vector<QMatrix4x4> idleTrans;
    vector<QMatrix4x4> walkTrans;
private:
    vector<QVector3D> vertices;
    vector<QVector3D> normales;
    vector<int> indices;
    vector<Mesh> meshes;
    vector<Animation> animations;
    vector<Bone> bones;
    Model m;
    const aiScene* scene;

    void calcTransformations(double t, Animation anim, AnimBone bone, vector<QMatrix4x4> &transformationList, QMatrix4x4 parent);
    QMatrix4x4 calcInterpolatedPosition(double t, AnimBone bone);
    QMatrix4x4 calcInterpolatedRotation(double t, AnimBone bone);
    QMatrix4x4 calcInterpolatedScale(double t, AnimBone bone);
};

const aiNode *getNode(const aiScene *scene, aiString name);
const aiNode *getChildNode(aiString name, const aiNode *node);

#endif // COLLADAPARSER_H
