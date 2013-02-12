/* ============================================================================
 **
 ** Author: Jacob Payne
 ** Author: Shannon Jones
 **
 ** CIS 367 Project 1
 ** Winter 2013
 **
 ** 3D drawing of the Weighted Companion Cube from
 ** Valve's Portal video game series
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
GLuint middle;
GLuint line;
GLdouble radius;



/* =======================================
 * Function called to update rendering
 * ======================================= */
void DisplayFunc(void)
{
	/* Clear the buffer, clear the matrix */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		glTranslatef(0, 0, -50);
		glRotatef(30, 0, 1, 0);
		glRotatef(30, 1, 0, 0);
		glScalef(2, 2, 2);
		glCallList(cube);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}




/* =======================================
 * Called when the window is created or resized
 * ======================================= */
void ReshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (float) height, 0.1, 100);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
} // END ReshapeFunc



/* =======================================
 * Initialize display lists for render function
 * ======================================= */
void init()
{
	cube = glGenLists(1);
	heart = glGenLists(1);
	face = glGenLists(1);
	corner = glGenLists(1);
	middle = glGenLists(1);
	line = glGenLists(1);

	glNewList(cube, GL_COMPILE);
		// ********************************************
		// draw the left face and all included objects
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glCallList(face);
		glPopMatrix(); // end of left face display lists


		// **********************************************
		// draw the right face and all included objects
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glCallList(face);
		glPopMatrix(); // end of right face display lists


		// *******************************************
		// draw the top face and all included objects
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glCallList(face);
		glPopMatrix(); // end of top face display lists


		// *******************************************
		// draw the back face and all included objects
		glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glCallList(face);
		glPopMatrix(); // end of back face display lists


		// *******************************************
		// draw the bottom face and all included objects
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glCallList(face);
		glPopMatrix(); // end of bottom face display lists

		// *******************************************
		// Draw the front face (no transformations needed)
		glCallList(face);

	glEndList(); // end of cube display list


    // =======================================
	/* Companion cube face display list */
	glNewList(face, GL_COMPILE);
		glBegin(GL_QUADS);
			glColor3ub(143, 143, 143);
			glVertex3f(-5, -5,  5);
			glVertex3f(-5,  5,  5);
			glVertex3f( 5,  5,  5);
			glVertex3f( 5, -5,  5);
			glColor3ub(143, 143, 143);
		glEnd();

		// *******************************************
		// draw the front face and all included objects
		glPushMatrix();
			// Place heart
			glPushMatrix();
				// move the heart out in front of the cube face and center it
				glTranslatef(0, -1.5, 5.2);
				glRotatef(45, 0, 0, 1);
				glCallList(heart);
				glColor3ub(153, 153, 153);
			glPopMatrix();

			// Bottom left corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(-5, -5, 5.2);
				glCallList(corner);
				glColor3ub(153, 153, 153);
			glPopMatrix();

			// Top left corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(-5, 5, 5.2);
				glRotatef(270, 0, 0, 1);
				glCallList(corner);
				glColor3ub(153, 153, 153);
			glPopMatrix();

			// Bottom right corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(5, -5, 5.2);
				glRotatef(90, 0, 0, 1);
				glCallList(corner);
				glColor3ub(153, 153, 153);
			glPopMatrix();

			// Top right corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(5, 5, 5.2);
				glRotatef(180, 0, 0, 1);
				glCallList(corner);
				glColor3ub(153, 153, 153);
			glPopMatrix();

			// top tiny middle cube
			glPushMatrix();
				// move the tiny middle cube out in front of the cube face
				glTranslatef(-0.5, 4, 5.2);
				glCallList(middle);
			glPopMatrix();

			// bottom tiny middle cube
			glPushMatrix();
				// move the tiny middle cube out in front of the cube face
				glTranslatef(-0.5, -5, 5.2);
				glCallList(middle);
			glPopMatrix();

			// left tiny middle cube
			glPushMatrix();
				// move the tiny middle cube out in front of the cube face
				glTranslatef(-5, -0.5, 5.2);
				glCallList(middle);
			glPopMatrix();

			// right tiny middle cube
			glPushMatrix();
				// move the tiny middle cube out in front of the cube face
				glTranslatef(4, -0.5, 5.2);
				glCallList(middle);
			glPopMatrix();

			// horizontal line to the right of the heart
			glPushMatrix();
				glLineWidth(5);
				// move the line out in front of the cube face
				glTranslatef(0, 0, 5.1);
				glCallList(line);
				glLineWidth(1);
			glPopMatrix();

			// vertical line on top of the heart
			glPushMatrix();
				glLineWidth(5);
				// move the line out in front of the cube face
				glTranslatef(0, 0, 5.1);
				glRotatef(90, 0, 0, 1);
				glCallList(line);
				glLineWidth(1);
			glPopMatrix();

			// horizontal line to the left of the heart
			glPushMatrix();
				glLineWidth(5);
				// move the line out in front of the cube face
				glTranslatef(-5, 0, 5.1);
				glCallList(line);
				glLineWidth(1);
			glPopMatrix();

			// vertical line underneath the heart
			glPushMatrix();
				glLineWidth(5);
				// move the line out in front of the cube face
				glTranslatef(0, 0, 5.1);
				glRotatef(-90, 0, 0, 1);
				glCallList(line);
				glLineWidth(1);
			glPopMatrix();

		glPopMatrix(); // end face
	glEndList();


     // =======================================
	/* Heart display list */
	glNewList(heart, GL_COMPILE);
		// draw the square center of the heart
		glBegin(GL_QUADS);
			glColor3ub(255, 153, 153);
			glVertex3f(0, 0, 0);
			glVertex3f(2, 0, 0);
			glVertex3f(2, 2, 0);
			glVertex3f(0, 2, 0);
			glColor3ub(153, 153, 153);
		glEnd();

		// draw the left top semi-circle of the heart
		glBegin(GL_TRIANGLE_FAN);
			glColor3ub(255, 153, 153);

				radius = 1;

				// draw a whole circle and only the top edge
				// will show over the top of the box
				for(int j = 0; j < 360; j++)
				{
					float theta = j * (M_PI/180.0f);

					float x = (float)radius * cos(theta)+1;
					float y = (float)radius * sin(theta)+2;
					glVertex3f(x, y, 0);
				}
		glEnd();

		// draw a whole circle and only the top edge
		// will show over the top of the box
		glBegin(GL_TRIANGLE_FAN);
			glColor3ub(255, 153, 153);

			radius = 1;

			for(int j = 0; j < 360; j++)
			{
				float theta = j * (M_PI/180.0f);

				float x = (float)radius * cos(theta)+2;
				float y = (float)radius * sin(theta)+1;
				glVertex3f(x, y, 0);
			}
		glEnd();

	glEndList(); // end of heart display list


	// =======================================
	// corner piece for companion cube
	glNewList(corner, GL_COMPILE);

		/* front face */
		glBegin(GL_QUAD_STRIP);
			glColor3ub(204, 204, 204);
			glVertex3f(3, 1, 1);
			glVertex3f(3, 0, 1);
			glVertex3f(1, 1, 1);
			glVertex3f(0, 0, 1);
			glVertex3f(1, 3, 1);
			glVertex3f(0, 3, 1);
		glEnd();

		/* back face */
		glBegin(GL_QUAD_STRIP);
			glColor3ub(210, 210, 210);
			glVertex3f(3, 1, 0);
			glVertex3f(3, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 3, 0);
			glVertex3f(0, 3, 0);
		glEnd();

		/* top face */
		glBegin(GL_QUAD_STRIP);
			glColor3ub(198, 198, 198);
			glVertex3f(3, 1, 0);
			glVertex3f(3, 1, 1);
			glVertex3f(1, 1, 0);
			glVertex3f(1, 1, 1);
			glVertex3f(1, 3, 0);
			glVertex3f(1, 3, 1);
			glVertex3f(0, 3, 0);
			glVertex3f(0, 3, 1);
		glEnd();

		/* bottom face */
		glBegin(GL_QUAD_STRIP);
			glColor3ub(214, 214, 214);
			glVertex3f(3, 1, 0);
			glVertex3f(3, 1, 1);
			glVertex3f(3, 0, 0);
			glVertex3f(3, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(0, 3, 0);
			glVertex3f(0, 3, 1);
		glEnd();

		/* triangle fans face */
		glBegin(GL_TRIANGLE_FAN);
			glColor3ub(204, 204, 204);
			glVertex3f(1, 1, 1);
			glVertex3f(3, 1, 1);
			glVertex3f(2.75, 1.75, 1);
			glVertex3f(2, 2, 1);
			glVertex3f(1.75, 2.75, 1);
			glVertex3f(1, 3, 1);
		glEnd();

		/* Quads in between corner fan and cube face  */
		glBegin(GL_QUAD_STRIP);
			glColor3ub(214, 214, 214);
			glVertex3f(3, 1, 0);
			glVertex3f(3, 1, 1);
			glVertex3f(2.75, 1.75, 0);
			glVertex3f(2.75, 1.75, 1);
			glVertex3f(2, 2, 0);
			glVertex3f(2, 2, 1);
			glVertex3f(1.75, 2.75, 0);
			glVertex3f(1.75, 2.75, 1);
			glVertex3f(1, 3, 0);
			glVertex3f(1, 3, 1);
		glEnd();
	glEndList(); // end of corner piece display list


	// =======================================
	/* draw tiny middle cube */
	glNewList(middle, GL_COMPILE);
		/* Quads in between corner fan and cube face  */
		/* front face middle cube */
		glBegin(GL_QUADS);
		glColor3ub(204, 204, 204);
			glVertex3f(0, 0, .5);
			glVertex3f(0, 1, .5);
			glVertex3f(1, 1, .5);
			glVertex3f(1, 0, .5);
		glEnd();

		/* back face middle cube */
		glBegin(GL_QUADS);
			glColor3ub(214, 214, 214);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 1, 0);
		glEnd();

		/* top face middle cube */
		glBegin(GL_QUADS);
			glColor3ub(198, 198, 198);
			glVertex3f(1, 1, .5);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 1, .5);
		glEnd();

		/* bottom face middle cube */
		glBegin(GL_QUADS);
			glColor3ub(210, 210, 210);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, .5);
			glVertex3f(1, 0, .5);
			glVertex3f(1, 0, 0);
		glEnd();

		/* right face middle cube */
		glBegin(GL_QUADS);
			glColor3ub(200, 200, 200);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(1, 1, .5);
			glVertex3f(1, 0, .5);
		glEnd();

		/* left face middle cube */
		glBegin(GL_QUADS);
			glColor3ub(208, 208, 208);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 1, .5);
			glVertex3f(0, 0, .5);
		glEnd();
	glEndList(); // end of tiny middle cube display list


	// =======================================
	// line used to form cross across center
	// of each cube face
	glNewList(line, GL_COMPILE);
		glBegin(GL_LINES);
			glColor3ub(255, 135, 250);
			glVertex3f(0, 0, 0);
			glVertex3f(4, 0, 0);
		glEnd();
	glEndList(); // end of heart line display list

} // END init



/* =======================================
 * Handles keypresses to enable/disable
 * wireframe mode andswitch between camera views
 * ======================================= */
void processNormalKeys(unsigned char key, int xx, int yy) {

	// if either 'esc' or 'q' are pressed, quit the program
	if (key == 27 || key == 'q')
		exit(0);

	// if 'w' is pressed, render every polygon with
	// GL_LINE rather than the normal GL_FILL
	//(approximating wireframe mode)
	if (key == 'w' || key == 'W')
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glLineWidth(1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -50);
			glRotatef(30, 0, 1, 0);
			glRotatef(30, 1, 0, 0);
			glScalef(2, 2, 2);
			glCallList(cube);
		glPopMatrix();
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glutSwapBuffers();
	}

	// if 'f' is pressed, re-render the cube with PolygonMode
	// set to GL_FILL (reverse the wireframe mode set with 'w')
	if (key == 'f' || key == 'F')
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glLineWidth(1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -50);
			glRotatef(30, 0, 1, 0);
			glRotatef(30, 1, 0, 0);
			glScalef(2, 2, 2);
			glCallList(cube);
		glPopMatrix();
		glutSwapBuffers();
	}

	// if '1' is pressed, render camera position 1 (default)
	if (key == '1')
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -50);
			glRotatef(30, 0, 1, 0);
			glRotatef(30, 1, 0, 0);
			glScalef(2, 2, 2);
			glCallList(cube);
		glPopMatrix();
		glutSwapBuffers();
	}

	// if '2' is pressed, render camera position 2
	if (key == '2')
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -40);
			glRotatef(-30, 0, 1, 0);
			glRotatef(45, 1, 0, 0);
			glScalef(1, 1, 1);
			glCallList(cube);
		glPopMatrix();
		glutSwapBuffers();
	}

	// if '3' is pressed, render camera position 3
	if (key == '3')
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -45);
			glRotatef(-30, 0, 1, 0);
			glRotatef(30, 0, 0, 1);
			glScalef(2, 2, 2);
			glCallList(cube);
		glPopMatrix();
		glutSwapBuffers();
	}

	// if '4' is pressed, render camera position 4
	if (key == '4')
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0, 0, -50);
			glRotatef(30, 0, 1, 0);
			glRotatef(145, 0, 0, 1);
			glScalef(2, 2, 2);
			glCallList(cube);
		glPopMatrix();
		glutSwapBuffers();
	}
}



/* =======================================
 * Main function
 * ======================================= */
int	main(int argc, char **argv)
{
	/* Creation of the window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Companion Cube: CIS 367 Proj 1");

	/* OpenGL settings */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	init();

	/* Declaration of the callbacks */
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);

	// handle key presses
	glutKeyboardFunc(processNormalKeys);
	glutIgnoreKeyRepeat(1);

	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
} // END main

/* ========================================================================= */
