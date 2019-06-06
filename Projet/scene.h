#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

#include <vector>

#include "model.h"

#include <iostream>
using namespace std;

struct VertexData {
    QVector3D position;
    QVector3D color;
    QVector3D normal;
    QVector2D uv;
};

class Scene : protected QOpenGLFunctions
{
public:
    Scene();
    Scene(Model);
    virtual ~Scene();

    void drawScene(QOpenGLShaderProgram *program, QMatrix4x4 projection, QQuaternion rotation);
    Model getModel();

    void animate(vector<QVector3D> positions, vector<QVector3D> scales, vector<QQuaternion> rotations);
private:
    void initScene();
    void buildVertices();
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer indexBoneBuf;
    QOpenGLBuffer weightsBuf;

    QMatrix4x4 *finalTransformations;

    Model model;

    VertexData* vertices;
    GLushort* indices;
    QVector4D* boneIndices;
    QVector4D* weights;

    size_t nbVertices = 0;
    size_t nbIndices = 0;
};

#endif // SCENE_H
