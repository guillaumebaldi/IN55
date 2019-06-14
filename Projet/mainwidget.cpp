#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    scene(0),
    manager(0)
{
    //Label for animation speed
    label = new QLabel(this);
    label->setText("Animation speed : ");
    label->setFixedWidth(90);
    label->setFixedHeight(30);
    label->setStyleSheet("QLabel { background-color : white; color : blue; }");
    label->setFocus();

    //Textbox input for animation speed
    line = new QLineEdit(this);
    line->move(100,5);
    line->setPlaceholderText(QString::fromStdString(std::to_string(animationSpeed)));

    //Button to put camera at its initial position
    button = new QPushButton(this);
    button->move(10, 50);
    button->setFixedHeight(50);
    button->setText("Camera initial position");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(setCameraInitialPosition()));
}

MainWidget::~MainWidget()
{
    makeCurrent();
    delete scene;
    doneCurrent();
}

/*
 * Sets the camera to its initial position
 */
void MainWidget::setCameraInitialPosition() {
    camera->setInitialPosition();
}

/*
 * When we press the mouse
 */
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    camera->setMousePressPosition(QVector2D(e->localPos()));
    label->setFocus();
}

/*
 * When we release the mouse
 */
void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    camera->move(QVector2D(e->localPos()));
}

/*
 * Timer
 */
void MainWidget::timerEvent(QTimerEvent *)
{
    //Updates camera rotation
    camera->update();
    //When we launch an animation, updates the frame to have the transformations
    if(isAnimating) {
        if(animation == 2){
            manager->playHello(frame);
            frame += 0.02 * animationSpeed;
        }
        else if(animation == 3) {
            manager->playWalk(frame);
            frame += 0.02 * animationSpeed;
        }
        else if(animation == 4) {
            manager->playRun(frame);
            frame += 0.03 * animationSpeed;
        }
        else if(animation == 5) {
            manager->playJump(frame);
            frame += 0.02 * animationSpeed;
        }
        if(frame >= 0.99) {
            frame = 0;
        }
    }
    update();
}

/*
 * When we press a key
 */
void MainWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        //1 : Idle animation
        case Qt::Key_1:
            frame = 0;
            animation = 1;
            manager->playIdle();
            break;
        //2 : Hello animation
        case Qt::Key_2:
            frame = 0;
            animation = 2;
            isAnimating = true;
            break;
        //3 : Walk animation
        case Qt::Key_3:
            frame = 0;
            animation = 3;
            isAnimating = true;
            break;
        //4 : Run animation
        case Qt::Key_4:
            frame = 0;
            animation = 4;
            isAnimating = true;
            break;
        //5 : Jump animation
        case Qt::Key_5:
            frame = 0;
            animation = 5;
            isAnimating = true;
            break;
        //Up : Translates camera up
        case Qt::Key_Up:
            camera->input(FORWARD, 1000/FPS);
            break;
        //Down : Translates camera down
        case Qt::Key_Down:
            camera->input(BACKWARD, 1000/FPS);
            break;
        //Right : Translates camera right
        case Qt::Key_Right:
            camera->input(RIGHT, 1000/FPS);
            break;
        //Left : Translates camera left
        case Qt::Key_Left:
            camera->input(LEFT, 1000/FPS);
            break;
        //Enter : Changes animation speed
        case Qt::Key_Enter:
            try {
                double v = std::stod(line->text().toStdString());
                this->animationSpeed = v;
            }
            catch(std::exception &e) {
            }
            break;
        case Qt::Key_Return:
            try {
                double v = std::stod(line->text().toStdString());
                this->animationSpeed = v;
            }
            catch(std::exception &e) {
            }
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

    //Parses model file and creates the Model
    ColladaParser parser;
    string s = "resources\\human.dae";
    Model m = parser.loadColladaFile(s);

    scene = new Scene(m);
    manager = new AnimationManager(scene);
    camera = new Camera();

    timer.start((int)1000/FPS, this);
}

/*
 * Initializes the shaders
 */
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

    const qreal zNear = 1.0, zFar = 50.0, fov = 60.0;

    projection.setToIdentity();

    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    //Model in the middle and updates with camera
    matrix.translate(0.0, 0.5f, -6.0);
    matrix.translate(camera->getPosition());
    matrix.rotate(camera->getRotation());
    matrix.rotate(-90, 1, 0, 0);
    program.setUniformValue("mvp", projection * matrix);
    scene->drawScene(&program);
}
