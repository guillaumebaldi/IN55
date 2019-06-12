#ifndef CAMERA_H
#define CAMERA_H

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
#include <QMouseEvent>
#include <cmath>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera();
    void move(QVector2D p);
    void update();
    QQuaternion getRotation();
    QVector3D getPosition();
    qreal getAngularSpeed();
    void setMousePressPosition(QVector2D p);

    QMatrix4x4 getViewMatrix();
    void input(Camera_Movement m, float t);
    void setInitialPosition();
private:
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    QVector2D mousePressPosition;

    QVector3D position;
    QVector3D front;
    QVector3D right;
    float speed;
    const float SPEED       =  0.1f;
};

#endif // CAMERA_H
