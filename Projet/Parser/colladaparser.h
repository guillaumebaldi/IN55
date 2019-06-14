/**
  ColladaParser :
  Parses COLLADA files to have model, bones and animations
*/

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
    void parseMeshes(aiMesh* mesh);
    void parseAnimations(string& file);
private:
    vector<Mesh> meshes;
    vector<Animation> animations;
    vector<Bone> bones;
    Model m;
    const aiScene* scene;
};

const aiNode *getNode(const aiScene *scene, aiString name);
const aiNode *getChildNode(aiString name, const aiNode *node);

#endif // COLLADAPARSER_H
