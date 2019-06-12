#include "camera.h"

Camera::Camera()
{
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->front = QVector3D(0.0f, 0.0, -0.1f);
    this->right = QVector3D(-0.1f, 0.0f, 0.0f);
    this->speed = SPEED;
}

void Camera::move(QVector2D p) {
    // Mouse release position - mouse press position
    QVector2D diff = p - mousePressPosition;

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

void Camera::update() {
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    }
    else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
}

QQuaternion Camera::getRotation() {
    return this->rotation;
}

QVector3D Camera::getPosition() {
    return this->position;
}

qreal Camera::getAngularSpeed() {
    return this->angularSpeed;
}

void Camera::setMousePressPosition(QVector2D p) {
    this->mousePressPosition = p;
}

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

void Camera::setInitialPosition() {
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->rotationAxis = QVector3D(0.0f, 0.0f, 0.0f);
    this->angularSpeed = 0;
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed);
}

