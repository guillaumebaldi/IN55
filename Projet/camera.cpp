#include "camera.h"

Camera::Camera()
{
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->front = QVector3D(0.0f, 0.0, -0.1f);
    this->right = QVector3D(-0.1f, 0.0f, 0.0f);
    this->speed = SPEED;
}

/*
 * Moves the camera for rotation
 */
void Camera::move(QVector2D p) {
    QVector2D diff = p - mousePressPosition;

    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    qreal acc = diff.length() / 100.0;

    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    angularSpeed += acc;
}

/*
 * Updates rotation of camera
 */
void Camera::update() {
    angularSpeed *= 0.99;

    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    }
    else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
}

/*
 * Returns rotation of camera
 */
QQuaternion Camera::getRotation() {
    return this->rotation;
}

/*
 * Returns position of camera
 */
QVector3D Camera::getPosition() {
    return this->position;
}

/*
 * Returns angular speed of camera
 */
qreal Camera::getAngularSpeed() {
    return this->angularSpeed;
}

/*
 * Sets mouse press position
 */
void Camera::setMousePressPosition(QVector2D p) {
    this->mousePressPosition = p;
}

/*
 * Translates camera
 */
void Camera::input(Camera_Movement m, float t) {
    float velocity = speed * t;
    if(m == FORWARD) {
        position += front * velocity;
    }
    if(m == BACKWARD) {
        position -= front * velocity;
    }
    if(m == LEFT) {
        position -= right * velocity;
    }
    if(m == RIGHT) {
        position += right * velocity;
    }
}

/*
 * Puts the camera at its initial position
 */
void Camera::setInitialPosition() {
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->rotationAxis = QVector3D(0.0f, 0.0f, 0.0f);
    this->angularSpeed = 0;
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed);
}

