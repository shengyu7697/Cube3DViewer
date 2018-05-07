#ifndef GLUTIL_H
#define GLUTIL_H

#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <GL/glew.h>
#endif

namespace GLUtil {
    void drawCube();
    void drawAxis(float len);
}

#endif // GLUTIL_H
