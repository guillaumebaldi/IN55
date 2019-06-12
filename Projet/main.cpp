#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseDesktopOpenGL);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    a.setApplicationName("IN55 - Animation de personnage");
    a.setApplicationVersion("1.0");

#ifndef QT_NO_OPENGL
    MainWidget widget;

    widget.setMinimumSize(800, 640);
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return a.exec();
}
