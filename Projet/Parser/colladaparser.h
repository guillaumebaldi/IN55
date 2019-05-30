#ifndef COLLADAPARSER_H
#define COLLADAPARSER_H

#include <QMessageBox>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QMatrix4x4>
#include <QQuaternion>

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
    void parseBones(const aiScene* scene, aiNode *node, vector<Bone>& bones);
    void parseMeshes(aiMesh* mesh);
    void parseAnimations(string& file);
private:
    vector<QVector3D> vertices;
    vector<QVector3D> normales;
    vector<int> indices;
    vector<Mesh> meshes;
    vector<Animation> animations;
};

#endif // COLLADAPARSER_H
