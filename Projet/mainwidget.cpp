#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    scene(0),
    manager(0),
    angularSpeed(0)
{
}

/*void MainWidget::load() {

    ColladaParser parser;
    string s = "resources\\human_walk.dae";
    Model m = parser.loadColladaFile(s);
    for(int i = 0; i < m.getBones().size(); i++) {
        //std::cout << m.getBones()[i].getId() << " " <<m.getBones()[i].getTransform().data()[0] << "\n";
    }
    //this->scene(m);
    //std::cout << scene->vertices[0].position.x();
}*/

MainWidget::~MainWidget()
{
    makeCurrent();
    delete scene;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

void MainWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_1:
            manager->playIdle();
            break;
        case Qt::Key_2:
            manager->playHello();
            break;
        case Qt::Key_3:
            manager->playWalk();
            break;
        case Qt::Key_4:
            manager->playRun();
            break;
        case Qt::Key_5:
            manager->playJump();
            break;
    }
}

void MainWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    ColladaParser parser;
    string s = "resources\\human2.dae";
    Model m = parser.loadColladaFile(s);
    for(int i = 0; i < m.getBones().size(); i++) {
        //std::cout << m.getBones()[i].getId() << " " <<m.getBones()[i].getTransform().data()[0] << "\n";
    }

    scene = new Scene(m);
    manager = new AnimationManager(scene);

    timer.start(12, this);
}

void MainWidget::initShaders() {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "resources\\vshader.glsl"))
        close();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "resources\\fshader.glsl"))
        close();

    if (!program.link())
        close();

    if (!program.bind())
        close();
}

void MainWidget::initTextures() {

}

void MainWidget::resizeGL(int w, int h) {
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    projection.setToIdentity();

    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->drawScene(&program, projection, rotation);
}
