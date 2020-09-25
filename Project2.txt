#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//Taskoudis Dimitris
//ID: 45
//Project 2

//initial scaling and rotation parameters
static GLfloat angle = 0.0;
static GLfloat x = 1.0, y = 1.0, z = 1.0;

//parameters for creating menu
static GLint scale = 1;
static int window;
static int menu_id;
static int submenu_id;
static int value = 0;


//Destroy the window when the exit button is pressed
void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
  }
  glutPostRedisplay();
}

//create menu
void createMenu(void){
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("A", 1);
    glutAddMenuEntry("B", 2);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Create the cube
void Cube (void)
{
	glNewList(1,GL_COMPILE);
		glBegin(GL_QUADS);
			glVertex3f(-1.0f,-1.0f,0.0f);
			glVertex3f(-1.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f,-1.0f,0.0f);
		glEnd();
	glEndList();


	// top face
	glPushMatrix();
	glColor3f(0.7,1,0.6);
	glTranslatef(0,1,0);
	glRotatef(90,1,0,0);
	glCallList(1);
	glPopMatrix();

    // down face
	glPushMatrix();
	glColor3f(0.9,0.5,0.1);
	glTranslatef(0,-1,0);
	glRotatef(90,1,0,0);
	glCallList(1);
	glPopMatrix();

    //right face
	glPushMatrix();
	glColor3f(0.4,1,0.8);
	glTranslatef(1,0,0);
	glRotatef(90,0,1,0);
	glCallList(1);
	glPopMatrix();

    // left face
	glPushMatrix();
	glColor3f(0.7,0.4,0.6);
	glTranslatef(-1,0,0);
	glRotatef(90,0,1,0);
	glCallList(1);
	glPopMatrix();

    // front face
	glPushMatrix();
	glColor3f(0.3,0.5,0);
	glTranslatef(0,0,1);
	glCallList(1);
	glPopMatrix();

    // back face
	glPushMatrix();
	glColor3f(0.5,0,0.7);
	glTranslatef(0,0,-1);
	glCallList(1);
	glPopMatrix();

}

//create Scene
void DrawScene (void)
{
    //black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//clipping plane coordinates
    glOrtho(-100.0, 100.0, -100.0, 100.0, 20.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
	//b=110 translate to z negatives
	glTranslatef(0,0,-110);
	//a=6 cube rectangle
	glScalef(3.0, 3.0, 3.0);
	//// rotational vector = [1,1,1]
    if(value == 2){
	glRotatef(angle, 1.0, 1.0, 1.0);
    }
    // draw cube
	glPushMatrix();
	glTranslatef(6,0,0);
	//rotate around itself
	glRotatef(angle, 1.0, 1.0, 1.0);
	glScalef(x, y, z);
	Cube();
	glPopMatrix();

	glutSwapBuffers();

}


// rotation and scaling adjustments
void idle(void)
{
	angle += 0.2;
	if ( angle > 360.0 )
	{
		angle -= 360.0;
	}

	if (scale==0)
	{
		if(x>=1)
			x -=0.03;
		else
			scale=1;

		if(z>=1)
			z -=0.03;
		else
			scale=1;

		if(y>=1)
			y -=0.03;
		else
			scale=1;
	}

	if (scale==1)
	{
		if(y<2)
			y +=0.03;
		else
			scale=0;

		if(x<2)
			x +=0.03;
		else
			scale=0;

		if(z<2)
			z +=0.03;
		else
			scale=0;
	}

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cubes");
	glutDisplayFunc(DrawScene);
    createMenu();
	glutIdleFunc(idle);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
