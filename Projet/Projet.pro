#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T11:01:10
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    Parser/colladaparser.cpp \
    model.cpp \
    Parser/colladaparser.cpp \
    main.cpp \
    mainwidget.cpp \
    model.cpp \
    bone.cpp \
    mesh.cpp

HEADERS += \
        mainwidget.h \
    mainwidget.h \
    Parser/colladaparser.h \
    model.h \
    assimp/Compiler/poppack1.h \
    assimp/Compiler/pstdint.h \
    assimp/Compiler/pushpack1.h \
    assimp/port/AndroidJNI/AndroidJNIIOSystem.h \
    assimp/ai_assert.h \
    assimp/anim.h \
    assimp/BaseImporter.h \
    assimp/Bitmap.h \
    assimp/BlobIOSystem.h \
    assimp/ByteSwapper.h \
    assimp/camera.h \
    assimp/cexport.h \
    assimp/cfileio.h \
    assimp/cimport.h \
    assimp/color4.h \
    assimp/config.h \
    assimp/CreateAnimMesh.h \
    assimp/DefaultIOStream.h \
    assimp/DefaultIOSystem.h \
    assimp/DefaultLogger.hpp \
    assimp/Defines.h \
    assimp/defs.h \
    assimp/Exceptional.h \
    assimp/Exporter.hpp \
    assimp/fast_atof.h \
    assimp/GenericProperty.h \
    assimp/Hash.h \
    assimp/Importer.hpp \
    assimp/importerdesc.h \
    assimp/IOStream.hpp \
    assimp/IOStreamBuffer.h \
    assimp/IOSystem.hpp \
    assimp/irrXMLWrapper.h \
    assimp/light.h \
    assimp/LineSplitter.h \
    assimp/LogAux.h \
    assimp/Logger.hpp \
    assimp/LogStream.hpp \
    assimp/Macros.h \
    assimp/material.h \
    assimp/MathFunctions.h \
    assimp/matrix3x3.h \
    assimp/matrix4x4.h \
    assimp/MemoryIOWrapper.h \
    assimp/mesh.h \
    assimp/metadata.h \
    assimp/NullLogger.hpp \
    assimp/ParsingUtils.h \
    assimp/pbrmaterial.h \
    assimp/postprocess.h \
    assimp/Profiler.h \
    assimp/ProgressHandler.hpp \
    assimp/qnan.h \
    assimp/quaternion.h \
    assimp/RemoveComments.h \
    assimp/scene.h \
    assimp/SceneCombiner.h \
    assimp/SGSpatialSort.h \
    assimp/SkeletonMeshBuilder.h \
    assimp/SmoothingGroups.h \
    assimp/SpatialSort.h \
    assimp/StandardShapes.h \
    assimp/StreamReader.h \
    assimp/StreamWriter.h \
    assimp/StringComparison.h \
    assimp/StringUtils.h \
    assimp/Subdivision.h \
    assimp/texture.h \
    assimp/TinyFormatter.h \
    assimp/types.h \
    assimp/vector2.h \
    assimp/vector3.h \
    assimp/version.h \
    assimp/Vertex.h \
    assimp/XMLTools.h \
    Parser/colladaparser.h \
    mainwidget.h \
    model.h \
    bone.h \
    mesh.h

FORMS += \
        mainwidget.ui

DISTFILES += \
    resources/human.blend \
    resources/human.blend1 \
    resources/human.dae \
    assimp-vc140-mt.dll


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Projet-Desktop_Qt_5_10_1_MSVC2017_64bit-Debug/release/ -lassimp-vc140-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Projet-Desktop_Qt_5_10_1_MSVC2017_64bit-Debug/debug/ -lassimp-vc140-mt
else:unix: LIBS += -L$$PWD/../../build-Projet-Desktop_Qt_5_10_1_MSVC2017_64bit-Debug/ -lassimp-vc140-mt

INCLUDEPATH += $$PWD/../../build-Projet-Desktop_Qt_5_10_1_MSVC2017_64bit-Debug/debug
DEPENDPATH += $$PWD/../../build-Projet-Desktop_Qt_5_10_1_MSVC2017_64bit-Debug/debug
