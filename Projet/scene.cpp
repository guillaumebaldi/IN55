#include "scene.h"

Scene::Scene(Model model)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();

    this->model = model;
    buildVertices();

    initScene();
}

Scene::~Scene() {
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Scene::initScene() {
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, nbIndices * sizeof(GLushort));

    this->finalTransformations = (QMatrix4x4*)malloc(sizeof(QMatrix4x4) * model.getBones().size());
    for(unsigned int i = 0; i < model.getBones().size(); i++) {
        finalTransformations[i] = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                                             0.0, 1.0, 0.0, 0.0,
                                             0.0, 0.0, 1.0, 0.0,
                                             0.0, 0.0, 0.0, 1.0);
    }
}

void Scene::animate(vector<QMatrix4x4> transformations) {
    for(unsigned int i = 0; i < model.getBones().size(); i++) {
        this->finalTransformations[i] = transformations[i];
    }
}

void Scene::drawScene(QOpenGLShaderProgram *program, QMatrix4x4 projection, QQuaternion rotation) {
    arrayBuf.bind();

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int uvLocation = program->attributeLocation("uv");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int idBonesLocation = program->attributeLocation("idBones");
    program->enableAttributeArray(idBonesLocation);
    program->setAttributeBuffer(idBonesLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    offset += sizeof(QVector4D);

    int weightLocation = program->attributeLocation("weight");
    program->enableAttributeArray(weightLocation);
    program->setAttributeBuffer(weightLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    arrayBuf.release();

    program->setUniformValueArray("transform", this->finalTransformations, 19);

    indexBuf.bind();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);
    program->setUniformValue("mvp", projection * matrix);
    glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_SHORT, 0);

    indexBuf.release();
}

void Scene::buildVertices() {
    vector<int> indMeshes;
    vector<QVector3D> verticesMeshes;
    vector<QVector3D> normalesMeshes;

    for(unsigned int i = 0; i < this->model.getMeshes().size(); i++) {
        this->nbIndices += this->model.getMeshes()[i].getIndices().size();
        vector<int> indMesh(model.getMeshes()[i].getIndices());
        indMeshes.insert(std::end(indMeshes),
                   std::begin(indMesh),
                   std::end(indMesh));

        this->nbVertices += this->model.getMeshes()[i].getVertices().size();
        vector<QVector3D> verticesMesh(model.getMeshes()[i].getVertices());
        verticesMeshes.insert(std::end(verticesMeshes),
                              std::begin(verticesMesh),
                              std::end(verticesMesh));

        vector<QVector3D> normalesMesh(model.getMeshes()[i].getNormales());
        normalesMeshes.insert(std::end(normalesMeshes),
                              std::begin(normalesMesh),
                              std::end(normalesMesh));

    }
    this->indices = (GLushort*)malloc(sizeof(GLushort) * nbIndices);
    for(unsigned int i = 0; i < this->nbIndices; i++) {
        indices[i] = indMeshes[i];
    }

    this->vertices = (VertexData*)malloc(sizeof(VertexData) * nbVertices);
    for(unsigned int i = 0; i < this->nbVertices; i++) {
        this->vertices[i].position = verticesMeshes[i];
        this->vertices[i].normal = normalesMeshes[i];
        this->vertices[i].color = QVector3D(1.0f, 1.0f, 1.0f);
        this->vertices[i].uv = QVector2D(0.0f, 0.0f);
        this->vertices[i].boneIndices = model.getIndicesBone(i);
        this->vertices[i].weights = model.getWeightsBone(i, this->vertices[i].boneIndices);
    }
}

Model Scene::getModel() {
    return this->model;
}
