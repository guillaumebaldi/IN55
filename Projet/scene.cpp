#include "scene.h"

Scene::Scene(Model model)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();
    indexBoneBuf.create();
    weightsBuf.create();

    this->model = model;
    buildVertices();

    initScene();
}

Scene::~Scene() {
    arrayBuf.destroy();
    indexBuf.destroy();
    indexBoneBuf.destroy();
    weightsBuf.destroy();
}

void Scene::initScene() {
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, nbIndices * sizeof(GLushort));

    indexBoneBuf.bind();
    indexBoneBuf.allocate(boneIndices, nbVertices * sizeof(QVector4D));

    weightsBuf.bind();
    weightsBuf.allocate(weights, nbVertices * sizeof(QVector4D));

    //transformBuf.bind();
    this->finalTransformations = (QMatrix4x4*)malloc(sizeof(QMatrix4x4) * nbVertices);
    for(unsigned int i = 0; i < nbVertices; i++) {
        finalTransformations[i] = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                                             0.0, 1.0, 0.0, 0.0,
                                             0.0, 0.0, 1.0, 0.0,
                                             0.0, 0.0, 0.0, 1.0);
    }
    /*transformBuf.allocate(finalTransformation, nbVertices * sizeof(QMatrix4x4));
    transformBuf.release();*/
}

void Scene::animate(vector<QVector3D> positions, vector<QVector3D> scales, vector<QQuaternion> rotations) {
    /*vector<QMatrix4x4> posTransformation;
    vector<QVector3D> posVertex;
    vector<QMatrix4x4> scaleTransformation;
    vector<QVector3D> scaleVertex;
    vector<QMatrix4x4> rotationTransformaion;
    vector<QQuaternion> rotationVertex;*/

    for(unsigned int i = 0; i < positions.size(); i++) {
        QMatrix4x4 posTransformation = QMatrix4x4(1.0, 0.0, 0.0, positions[i].x(),
                                                  0.0, 1.0, 0.0, positions[i].y(),
                                                  0.0, 0.0, 1.0, positions[i].z(),
                                                  0.0, 0.0, 0.0, 1.0);
        QMatrix4x4 scaleTransformation = QMatrix4x4(scales[i].x(), 0.0, 0.0, 0.0,
                                                    0.0, scales[i].y(), 0.0, 0.0,
                                                    0.0, 0.0, scales[i].z(), 0.0,
                                                    0.0, 0.0, 0.0, 1.0);
        float x = rotations[i].x();
        float y = rotations[i].y();
        float z = rotations[i].z();
        float s = rotations[i].scalar();
        QMatrix4x4 rotationTransformation = QMatrix4x4(1-2*pow(y,2)-2*pow(z,2), 2*x*y-2*s*z, 2*x*z+2*s*y, 0.0,
                                                      2*x*y+2*s*z, 1-2*pow(x,2)-2*pow(z,2), 2*y*z-2*s*x, 0.0,
                                                      2*x*z-2*s*y, 2*y*z+2*s*x, 1-2*pow(x,2)-2*pow(y,2), 0.0,
                                                      0.0, 0.0, 0.0, 1.0);

        QMatrix4x4 temp = posTransformation * rotationTransformation * scaleTransformation;
        QMatrix4x4 temp2;
        if(i == 0) {
            temp2 = QMatrix4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1) * temp;
        }
        else {
            temp2 = model.getBone(model.getBoneByNumber(i).getParent()).getTransform() * temp;
        }
        this->finalTransformations[i] = temp2 * model.getBoneByNumber(i).getTransform();
        //this->finalTransformations[i] = posTransformation * rotationTransformation * scaleTransformation;
    }

    /*for(unsigned int i = 0; i < nbVertices; i++) {
        posVertex.push_back(QVector3D(0.0, 0.0, 0.0));
        scaleVertex.push_back(QVector3D(0.0, 0.0, 0.0));
        rotationVertex.push_back(QQuaternion(0.0, 0.0, 0.0, 0.0));
    }
    int s = 0;
    for(unsigned int i = 0; i < positions.size(); i++) {
        for(int j = s; j < s+offset[i]; j++) {
            posVertex[id[j]] += (positions[i] * weights[j]);
            scaleVertex[id[j]] += (scales[i] * weights[j]);
            rotationVertex[id[j]] += (rotations[i] * weights[j]);
        }
        s += offset[i];
    }

    for(unsigned int i = 0; i < nbVertices; i++) {
        posTransformation.push_back(QMatrix4x4(1.0, 0.0, 0.0, posVertex[i].x(),
                                 0.0, 1.0, 0.0, posVertex[i].y(),
                                 0.0, 0.0, 1.0, posVertex[i].z(),
                                 0.0, 0.0, 0.0, 1.0));
        scaleTransformation.push_back(QMatrix4x4(scaleVertex[i].x(), 0.0, 0.0, 0.0,
                                                 0.0, scaleVertex[i].y(), 0.0, 0.0,
                                                 0.0, 0.0, scaleVertex[i].z(), 0.0,
                                                 0.0, 0.0, 0.0, 1.0));
        float x = rotationVertex[i].x();
        float y = rotationVertex[i].y();
        float z = rotationVertex[i].z();
        float s = rotationVertex[i].scalar();
        rotationTransformaion.push_back(QMatrix4x4(1-2*pow(y,2)-2*pow(z,2), 2*x*y-2*s*z, 2*x*z+2*s*y, 0.0,
                                                   2*x*y+2*s*z, 1-2*pow(x,2)-2*pow(z,2), 2*y*z-2*s*x, 0.0,
                                                   2*x*z-2*s*y, 2*y*z+2*s*x, 1-2*pow(x,2)-2*pow(y,2), 0.0,
                                                   0.0, 0.0, 0.0, 1.0));

        this->finalTransformations[i] = posTransformation[i] * rotationTransformaion[i] * scaleTransformation[i];
    }*/
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

    arrayBuf.release();

    indexBoneBuf.bind();

    int idBonesLocation = program->attributeLocation("idBones");
    program->enableAttributeArray(idBonesLocation);
    program->setAttributeBuffer(idBonesLocation, GL_FLOAT, 0, 4, sizeof(QVector4D));

    indexBoneBuf.release();

    weightsBuf.bind();

    int weightLocation = program->attributeLocation("weight");
    program->enableAttributeArray(weightLocation);
    program->setAttributeBuffer(weightLocation, GL_FLOAT, 0, 4, sizeof(QVector4D));

    weightsBuf.release();

    /*indexBoneBuf.bind();

    int idBonesLocation = program->attributeLocation("idBones");
    program->enableAttributeArray(idBonesLocation);
    program->setAttributeBuffer(idBonesLocation, GL_FLOAT, 0, 5, sizeof(int));

    indexBoneBuf.release();

     weightsBuf.bind();

    int weightLocation = program->attributeLocation("weight");
    program->enableAttributeArray(weightLocation);
    program->setAttributeBuffer(weightLocation, GL_FLOAT, 0, 5, sizeof(int));

    weightsBuf.release();
    */
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
    }

    /*QVector4D *inde = (QVector4D*)malloc(sizeof(QVector4D) * nbVertices);
    QVector4D *weights = (QVector4D*)malloc(sizeof(QVector4D) * nbVertices);
    for(unsigned int i = 0; i < nbVertices; i++) {
        inde[i] = model.getIndicesBone(i);
        weights[i] = model.getWeightsBone(i, inde[i]);
    }*/

    /*vector<int> b;
    vector<float> w;
    for(unsigned int i = 0; i < nbVertices; i++) {
        vector<int> indBone(model.getIndicesBone(i));
        b.insert(std::end(b),
                 std::begin(indBone),
                 std::end(indBone));
        vector<float> weig(model.getWeightsBone(i, indBone));
        w.insert(std::end(w),
                 std::begin(weig),
                 std::end(weig));
    }*/

    this->boneIndices = (QVector4D*)malloc(sizeof(QVector4D) * nbVertices);
    this->weights = (QVector4D*)malloc(sizeof(QVector4D) * nbVertices);

    for(unsigned int i = 0; i < nbVertices; i++) {
        boneIndices[i] = model.getIndicesBone(i);
        weights[i] = model.getWeightsBone(i, boneIndices[i]);
    }

    /*for(int i = 0; i < nbVertices*5; i++) {
        this->boneIndices[i] = b[i];
        this->weights[i] = w[i];
    }*/


    /*for(unsigned int i = 0; i < nbVertices; i++) {
        vector<int> in = model.getIndicesBone(i);
        vector<float> we = model.getWeightsBone(i, in);
        copy(in.begin(), in.end(), boneIndices);
        copy(we.begin(), we.end(), weights);
    }*/
    /*for(int i = 0; i < 20; i++) {
        std::cout << boneIndices[i] << " " << weights[i] << "\n";
    }*/
}

Model Scene::getModel() {
    return this->model;
}
