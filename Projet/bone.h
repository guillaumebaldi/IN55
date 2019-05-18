#ifndef BONE_H
#define BONE_H

#include <QVector3D>
#include <QMatrix4x4>

using namespace std;

class Bone
{
public:
    Bone();
    Bone(string, QMatrix4x4);
    Bone(QMatrix4x4);
    QMatrix4x4 getTransform();
    void setTransform(QMatrix4x4 m);
    string getId();
    void setId(string id);
private:
    string id;
    QMatrix4x4 transform;
};

#endif // BONE_H
