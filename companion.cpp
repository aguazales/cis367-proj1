/* ============================================================================
 **
 ** Demonstration of spinning cube
 ** Copyright (C) 2005  Julien Guertault
 **
 ** This program is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU General Public License
 ** as published by the Free Software Foundation; either version 2
 ** of the License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 **
 ** ========================================================================= */

#include	<stdlib.h>
#include	<C:\MinGW\include\GL\freeglut.h>
#include	<math.h>

/* Display lists for objects */
GLuint cube;
GLuint face;
GLuint heart;
GLuint corner;
GLuint mid_bracket;
/*
 ** Function called to update rendering
 */
void		DisplayFunc(void)
{

	/* Clear the buffer, clear the matrix */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();




	//glCallList(cube);
	glCallList(heart);




	/* End */
	glFlush();
	glutSwapBuffers();

	/* Update again and again */
	//glutPostRedisplay();
}


/*
 ** Function called when the window is created or resized
 */
void		ReshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(20, width / (float) height, 5, 75);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}


/*
 ** Function called when a key is hit
 */
void KeyboardFunc(unsigned char key, int x, int y)
{
	if ('q' == key || 'Q' == key || 27 == key)
		exit(0);
}


/* Initialize display lists for render function */
void init()
{
	cube = glGenLists(1);
	heart = glGenLists(1);

	/* Cube display list (bare surfaces, no details) */
	glNewList(cube, GL_COMPILE);
		glPushMatrix();

		/* Move the object backward 50 units from the camera
		 * and rotate 30 degrees left on the x-axis and
		 * 30 degrees down on the y-axis*/
		glTranslatef(0, 0, -50);
		glRotatef(30, 1, 0, 0);
		glRotatef(30, 0, 1, 0);

		/* We tell we want to draw quads */
		glBegin(GL_QUADS);

		/* Every four calls to glVertex, a quad is drawn */

		/* Left face */
		glVertex3f(-5, -5, -5);
		glVertex3f(-5, -5,  5);
		glVertex3f(-5,  5,  5);
		glVertex3f(-5,  5, -5);

		glColor3ub(143, 143, 143);
		/* Right face */
		glVertex3f( 5,  5, -5);
		glVertex3f( 5,  5,  5);
		glVertex3f( 5, -5,  5);
		glVertex3f( 5, -5, -5);
		glColor3ub(153, 153, 153);

		/* Bottom face */
		glVertex3f(-5, -5, -5);
		glVertex3f(-5, -5,  5);
		glVertex3f( 5, -5,  5);
		glVertex3f( 5, -5, -5);
		glColor3ub(160, 160, 160);

		/* Top face */
		glVertex3f(-5,  5, -5);
		glVertex3f(-5,  5,  5);
		glVertex3f( 5,  5,  5);
		glVertex3f( 5,  5, -5);
		glColor3ub(148, 148, 148);

		/* Back face */
		glVertex3f(-5, -5, -5);
		glVertex3f(-5,  5, -5);
		glVertex3f( 5,  5, -5);
		glVertex3f( 5, -5, -5);
		glColor3ub(150, 150, 150);

		/* Front face */
		glVertex3f(-5, -5,  5);
		glVertex3f(-5,  5,  5);
		glVertex3f( 5,  5,  5);
		glVertex3f( 5, -5,  5);
		glColor3ub(140, 140, 140);

		glEnd();
		glPopMatrix();
	glEndList();


	/* Heart display list */
	glNewList(heart, GL_COMPILE);
		glPushMatrix();

		glRotatef(45, 0, 0, 1);
		glTranslatef(0, 0, -40);

		glBegin(GL_QUADS);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3ub(255, 153, 153);
			glVertex3f(0, 0, 0);
			glVertex3f(2, 0,  0);
			glVertex3f(2,  2,  0);
			glVertex3f(0,  2, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3ub(153, 153, 153);
		glEnd();
		glPopMatrix();
	glEndList();

}


int		main(int argc, char **argv)
{
	/* Creation of the window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Companion Cube (eventually)");

	/* OpenGL settings */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	init();

	/* Declaration of the callbacks */
	glutDisplayFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);

	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
}

/* ========================================================================= */
