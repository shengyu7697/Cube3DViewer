#include "GLUtil.h"

#include <GL/glew.h>

namespace GLUtil {

void drawCube()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // green
    glVertex3f( 1.0, 1.0,-1.0);
    glVertex3f(-1.0, 1.0,-1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f( 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f( 1.0,-1.0, 1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f( 1.0,-1.0,-1.0);
    glColor3f(1.0, 0.0, 0.0); // red
    glVertex3f( 1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glVertex3f( 1.0,-1.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f( 1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0, 1.0,-1.0);
    glVertex3f( 1.0, 1.0,-1.0);
    glColor3f(0.0, 0.0, 1.0); // blue
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0); // white
    glVertex3f( 1.0, 1.0,-1.0);
    glVertex3f( 1.0, 1.0, 1.0);
    glVertex3f( 1.0,-1.0, 1.0);
    glVertex3f( 1.0,-1.0,-1.0);
    glEnd();
}

void drawAxis(float len)
{
	glBegin(GL_LINES);
	// x axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(len, 0.0, 0.0);

	// y axis
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, len, 0.0);

	// z axis
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, len);
	glEnd();
}

} // namespace GLUtil