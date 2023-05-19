#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

//Taskoudis Dimitris
//ID: 45

//Project 3

//parameters for creating menu
static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

//initial parameters
static float spotAngle = 30.0;
static float spotExponent = 0.0;

//Regular tetrahedron inscribed in the unit sphere
typedef float point[4];

point v[]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
          {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};



//External product of two vectors located
//at the level of the polygon
void ext_product(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d)
{
	d[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
	d[1]=(b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
	d[2]=(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[2]);
}


//external product of the triangle
void ext_product_tri(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d)
{
	GLfloat temp1[3];
	ext_product(a,b,c,temp1);
	int i;
	for (i=0;i<3;i++)
	{
		d[i]=temp1[i];
	}
}



//external product of the rectangle
void ext_product_rect(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d,GLfloat *e)
{
	GLfloat temp1[3];
	ext_product(a,b,c,temp1);
	int i;
	for (i=0;i<3;i++)
	{
		e[i]=temp1[i];
	}
}

//rotate the camera around a point
class Camera {
  double theta;      // determines the x and z positions
  double y;          // the current y position
  double dTheta;     // increment in theta for swinging the camera around
  double dy;         // increment in y for moving the camera up/down
public:
  Camera(): theta(80), y(10), dTheta(0.04), dy(0.2) {}
  double getX() {return 10 * cos(theta);}
  double getY() {return y;}
  double getZ() {return 10 * sin(theta);}
  void moveRight()
  {theta += dTheta;}
  void moveLeft()
  {theta -= dTheta;}
  void moveUp()
  {y += dy;}
  void moveDown()
  {if (y > dy) y -= dy;}
};

Camera camera;

//keys about camera's moves
void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
  }
  glutPostRedisplay();
}


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
    glutAddMenuEntry("Flat", 1);
    glutAddMenuEntry("Short", 2);
    glutAddMenuEntry("Tall", 3);
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Grass", submenu_id);
    glutAddMenuEntry("LightOn", 4);
    glutAddMenuEntry("LightOff", 5);
    glutAddMenuEntry("SmoothShading", 6);
    glutAddMenuEntry("FlatShading", 7);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}



//initial triangle that will then become a sphere
void Triangle_Sphere(point a, point b, point c)

{
	glBegin(GL_POLYGON);
		glNormal3fv(a);
		glVertex3fv(a);
		glNormal3fv(b);
		glVertex3fv(b);
		glNormal3fv(c);
		glVertex3fv(c);
    	glEnd();
}



//create square
void Square()
{
    GLfloat sq1[3]={-5.0,5.0,10.0};
	GLfloat sq2[3]={-5.0,0.0,10.0};
	GLfloat sq3[3]={5.0,0.0,10.0};
	GLfloat sq4[3]={5.0,5.0,10.0};
	GLfloat n[3];
    ext_product_rect(sq1,sq2,sq3,sq4,n);
      glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(sq1);
	    glVertex3fv(sq2);
 	    glVertex3fv(sq3);
	    glVertex3fv(sq4);
	  glEnd();
}

//create triangle
void Triangle()
{
    GLfloat tr1[]={-5.0,0.0,0.0};
	GLfloat tr2[]={5.0,0.0,0.0};
	GLfloat tr3[]={0.0,sqrt(75),0.0};
	GLfloat n[3];
	ext_product_tri(tr1,tr2,tr3,n);
     glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(tr1);
	    glVertex3fv(tr2);
 	    glVertex3fv(tr3);
	  glEnd();
}

//create rectangle
void Orthogonio()
{
    GLfloat rec1[3]={-5.0,0.0,10.0};
	GLfloat rec2[3]={5.0,0.0,10.0};
	GLfloat rec3[3]={5.0,0.0,-10.0};
	GLfloat rec4[3]={-5.0,0.0,-10.0};
    GLfloat n[3];
	ext_product_rect(rec1,rec2,rec3,rec4,n);

      glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(rec1);
	    glVertex3fv(rec2);
 	    glVertex3fv(rec3);
	    glVertex3fv(rec4);
	  glEnd();
}

//create grass
void Grass()
{
    GLfloat gras1[]={-80.0, 0.0, -80.0};
	GLfloat gras2[]={-80.0, 0.0, 80.0};
	GLfloat gras3[]={80.0, 0.0, 80.0};
	GLfloat gras4[]={80.0, 0.0, -80.0};
    GLfloat n[3];
	ext_product_rect(gras1,gras2,gras3,gras4,n);
    glBegin(GL_POLYGON);
    glNormal3fv(n);
    glVertex3fv(gras1);
    glVertex3fv(gras2);
    glVertex3fv(gras3);
    glVertex3fv(gras4);
    glEnd();
}

//create short grass with many polygons
void Grass_Short_Many_Polygons()
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 100; i++) {
    glVertex3f(40.0f, 0.5f, i+(-40.0f));
    glVertex3f(-40.0f, -0.5f, i+(-40.0f));
    glVertex3f(-40.0f, 0.5f, i+(-40.0f));
    glVertex3f(40.0f, -0.5f, i+(-40.0f));
    }
    glEnd();
}


//create tall grass with many polygons
void Grass_Tall_Many_Polygons()
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 100; i++) {
    glVertex3f((40.0f), 2.5f, i+(-40.0f));
    glVertex3f((-40.0f), 1.5f, i+(-40.0f));
    glVertex3f((-40.0f), 2.5f, i+(-40.0f));
    glVertex3f((40.0f), 1.5f, i+(-40.0f));
    }
    glEnd();
}



//Normalization of the points of the retroactive subdivision
void normalize(point p)
{
    float d =0.0;
    int i;
    for(i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d>0.0) for(i=0; i<3; i++) p[i]/=d;

}


//retroactive subdivision of triangles
void subdivision(point a, point b, point c,int m)
{

    point v1, v2, v3;
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++) v1[j]=a[j]+b[j];
        normalize(v1);
        for(j=0; j<3; j++) v2[j]=a[j]+c[j];
        normalize(v2);
        for(j=0; j<3; j++) v3[j]=b[j]+c[j];
        normalize(v3);
        subdivision(a, v1, v2, m-1);
        subdivision(c, v2, v3, m-1);
        subdivision(b, v3, v1, m-1);
        subdivision(v1, v3, v2, m-1);
    }
    else(Triangle_Sphere(a,b,c));
}



//repeat the process in all triangles
void sphere(void)
{

    subdivision(v[0], v[1], v[2],4);
    subdivision(v[3], v[2], v[1],4);
    subdivision(v[0], v[3], v[1],4);
    subdivision(v[0], v[2], v[3],4);

}


//create lists
void createDL()
{
    glNewList(1,GL_COMPILE);

        Square();

	glEndList();


    glNewList(2,GL_COMPILE);

        Triangle();

	glEndList();

    glNewList(3,GL_COMPILE);

        Orthogonio();

	glEndList();

    glNewList(4,GL_COMPILE);

        Grass();

	glEndList();

	glNewList(5,GL_COMPILE);

       sphere();

    glEndList();

    glNewList(6,GL_COMPILE);

       Grass_Short_Many_Polygons();

    glEndList();

    glNewList(7,GL_COMPILE);

       Grass_Tall_Many_Polygons();

    glEndList();
}


//sun angle
float angle_sun=0;

//movement only on the positives of the y axis
void Idle()
{
    angle_sun+=0.1;
	if (angle_sun >= 180)
	{
	angle_sun=angle_sun-180;
	}

	glutPostRedisplay();

}



//create Scene
void SceneCreation()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GLfloat light_pos1[]={ 0.0,0.0,0.0,1.0};
    GLfloat light_pos2[]={-15.0,25.0,-15.0,1.0};
    GLfloat spotDirection[] = {0.0, -1.0, 0.0};

    glClearColor (0.0, 0.0, 0.0, 1.0);

	//parameters of light 1
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    //parameters of light 2
	GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };



	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);



    if(value == 4){
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);

    glEnable(GL_LIGHT1);
    }

    if(value == 5){
    glDisable(GL_LIGHT1);
    }

    if(value == 6){
	glEnable(GL_SMOOTH);
    }

    if(value == 7){
    glEnable(GL_FLAT);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    createDL();
    glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-60.0,60.0,-60.0,60.0, -20.0, 400.0);
	glMatrixMode(GL_MODELVIEW);



    GLfloat house_specular[]={0.0,0.0,0.0,1.0};
	GLfloat house_dif_amb[]={0.54, 0.27, 0.07,1.0};
	GLfloat roof_specular[]={0.80,0.80,0.80,1.0};
	GLfloat roof_dif_amb[]={0.5,0.5,0.5,1.0};
	GLfloat grass_dif[]={0.5,1.0,0.0,1.0};
	GLfloat no_mat[]={0.0,0.0,0.0,1.0};
	GLfloat high_shine[]={100.0}; //syntelesths gyaladas
	GLfloat no_shine[]={0.0};
	GLfloat emission[]={1.0,1.0,0.0,1.0};

	//house surfaces
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,house_dif_amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,house_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix();
	glCallList(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-20);
	glCallList(1);
	glPopMatrix();


	glPushMatrix();
	glRotatef(90,0,0,1);
	glTranslatef(0,-5,0);
    glRotatef(180,1,0,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,0,0);
	glRotatef(90,0,0,1);
	glCallList(3);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,-5,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,5,0);
	glCallList(3);
	glPopMatrix();

	//roof of house
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,roof_dif_amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,roof_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,high_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix();
	//left roof
	glTranslatef(-5,5,0);
	glRotatef(60,0,0,1);
	glTranslatef(5,0,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix();
	//right roof
	glTranslatef(5,5,0);
	glRotatef(-60,0,0,1);
	glTranslatef(-5,0,0);
	glCallList(3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,5,10);
    glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,5,-10);
    glCallList(2);
	glPopMatrix();

	//grass lighting
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,grass_dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix();
	glCallList(4);
	glPopMatrix();

	//sun lighting
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);

	glPushMatrix();
	glRotatef(-angle_sun,0,0,1);
	glTranslatef(-50,0,0);
	//direction of parallel motion in homogeneous coordinates
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
	glScalef(2,2,2);
	glCallList(5);
	glPopMatrix();


	//grass lighting
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,grass_dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


    if(value == 2){
    glScalef(1,1,1);
	glCallList(6);
	glPopMatrix();
    }

    if(value == 3){
    glScalef(1,1,1);
	glCallList(7);
	glPopMatrix();
    }

	glutSwapBuffers();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_NORMALIZE);
	SceneCreation();


}


void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 800.0f);
}


int main(int argc, char** argv)
{
   	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (800, 800);
   	glutInitWindowPosition (0, 0);
	glutCreateWindow("Sun + House");
    glutSpecialFunc(special);
    createMenu();
	glutDisplayFunc(display);
	glutIdleFunc (Idle);
	glEnable(GL_DEPTH_TEST);
   	glutMainLoop();

}
