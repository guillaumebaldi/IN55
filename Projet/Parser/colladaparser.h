#ifndef COLLADAPARSER_H
#define COLLADAPARSER_H

#include <QMessageBox>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model.h"
#include "bone.h"
#include "mesh.h"

#include <iostream>
#include <vector>
using namespace std;

class ColladaParser
{
public:
    ColladaParser();
    Model loadColladaFile(string& file);
    void parseBones(const aiScene* scene, aiNode *node, vector<Bone>& bones);
    void parseMeshes(aiMesh* mesh);
private:
    vector<Mesh> meshes;
};

#endif // COLLADAPARSER_H
