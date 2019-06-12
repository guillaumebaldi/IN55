#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFile>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QPixmap>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Parser/colladaparser.h"
#include "model.h"
#include "bone.h"
#include "scene.h"
#include "animationmanager.h"
#include "camera.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
using namespace std;

class Scene;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void setCameraInitialPosition();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QLineEdit *line;
    QLabel *label;
    QPushButton *button;
    QBasicTimer timer;
    Scene *scene;
    AnimationManager *manager;
    Camera *camera;
    QOpenGLShaderProgram program;

    QMatrix4x4 projection;

    int FPS = 60;
    int animation = 0;
    bool isAnimating = false;
    double frame = 0;
    double animationSpeed = 1;
};

#endif // MAINWIDGET_H
