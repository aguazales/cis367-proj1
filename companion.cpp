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

/* Used to control camera position */
// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;


/* =======================================
 * Computes the position of the camera in space
 * ======================================= */
void computePos(float deltaMove)
{
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}



/* =======================================
 * Computes the camera angle in space
 * ======================================= */
void computeDir(float deltaAngle)
{
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}



/* =======================================
 * Function called to update rendering
 * ======================================= */
void DisplayFunc(void)
{
//	if (deltaMove)
//			computePos(deltaMove);
//	if (deltaAngle)
//		computeDir(deltaAngle);

	/* Clear the buffer, clear the matrix */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

//	// Set the camera
//	gluLookAt(	x, 1.0f, z,
//			x+lx, 1.0f,  z+lz,
//			0.0f, 1.0f,  0.0f);


//	gluLookAt(0, 0, 0, 0, 1, 0, 0, 1, 0);

	glPushMatrix();
		glTranslatef(0, 0, -50);
		glRotatef(30, 0, 1, 0);
		glRotatef(30, 1, 0, 0);
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

	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
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

			// Place heart
			glPushMatrix();
				// move the heart out in front of the cube face and center it
				glTranslatef(0, -1.5, 5.2);
				glRotatef(45, 0, 0, 1);
				glCallList(heart);
			glPopMatrix();

			// Bottom left corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(-5, -5, 5.2);
				glCallList(corner);
			glPopMatrix();

			// Top left corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(-5, 5, 5.2);
				glRotatef(270, 0, 0, 1);
				glCallList(corner);
			glPopMatrix();

			// Bottom right corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(5, -5, 5.2);
				glRotatef(90, 0, 0, 1);
				glCallList(corner);
			glPopMatrix();

			// Top right corner
			glPushMatrix();
				// move the corner out in front of the cube face
				glTranslatef(5, 5, 5.2);
				glRotatef(180, 0, 0, 1);
				glCallList(corner);
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

		glPopMatrix(); // end of left face display lists



		// **********************************************
		// draw the right face and all included objects
			glPushMatrix();
				//glLoadIdentity();
				glRotatef(90, 0, 1, 0);
				glCallList(face);

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

			glPopMatrix(); // end of right face display lists


			// *******************************************
			// draw the top face and all included objects
			glPushMatrix();
				//glLoadIdentity();
				glRotatef(-90, 1, 0, 0);
				glCallList(face);

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

			glPopMatrix(); // end of top face display lists


			// *******************************************
			// draw the back face and all included objects
			glPushMatrix();
				//glLoadIdentity();

				glRotatef(180, 1, 0, 0);
				glCallList(face);

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

			glPopMatrix(); // end of back face display lists


			// *******************************************
			// draw the bottom face and all included objects
			glPushMatrix();
				//glLoadIdentity();

				glRotatef(90, 1, 0, 0);
				glCallList(face);

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

			glPopMatrix(); // end of bottom face display lists


			// *******************************************
			// draw the front face and all included objects
			glPushMatrix();
				//glLoadIdentity();

				glCallList(face);

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
	glEndList(); // end of corner piecedisplay list


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
	// line used to form cross across center of each cube face
	glNewList(line, GL_COMPILE);
		glBegin(GL_LINES);
			glColor3ub(255, 135, 250);
			glVertex3f(0, 0, 0);
			glVertex3f(4, 0, 0);
		glEnd();
	glEndList(); // end of heart line display list

} // END init



/* =======================================
 * Function called when normal keys are hit
 * ======================================= */
void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);

	if (key == 'w' || key == 'W')
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glLineWidth(1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCallList(cube);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glutSwapBuffers();
	}

	if (key == 'f' || key == 'F')
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glLineWidth(1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCallList(cube);
		glutSwapBuffers();
	}
}



/* =======================================
 * Function called when a key is pressed down
 * ======================================= */
void pressKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}



/* =======================================
 * Function called when a key is released
 * ======================================= */
void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
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
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
} // END main

/* ========================================================================= */
