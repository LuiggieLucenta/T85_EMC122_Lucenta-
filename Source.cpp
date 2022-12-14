#include <iostream>
#include <glut.h>


#include "imageloader.h"

void update(int);
GLuint loadTexture(Image* image);
void reshape(int, int);
void display();

GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat directedLightPos[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light[] = { 0.5, 0.5, 0.5 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat static_ambient[] = { 0.8, 0.8, 0.8, 1.0 };

float angle = 0; //rotation angle

GLuint _build1;
GLuint _build2;//The id of the texture
GLuint _build3;
GLuint _build4;
GLuint _build5;
GLuint _build6;

GLuint _textureBall;
GLUquadric* ball;

void initRendering() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	Image* image1 = loadBMP("1.bmp");
	_build1 = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("2.bmp");
	_build2 = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("3.bmp");
	_build3 = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("4.bmp");
	_build4 = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("5.bmp");
	_build5 = loadTexture(image5);
	delete image5;

	Image* image6 = loadBMP("6.bmp");
	_build6 = loadTexture(image6);
	delete image6;

	Image* image_sky = loadBMP("skybox.bmp");
	_textureBall = loadTexture(image_sky);
	delete image_sky;

	ball = gluNewQuadric();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("M2A2_Skyscrapers");
	initRendering();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / 60, update, 0); //add timer
	glutMainLoop();
	return 0;
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------SKYBOX-----------------------//
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBall);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, static_ambient); //add ambient lighting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1, 1, 1); // needed to make the skybox visible
	gluQuadricTexture(ball, 1);
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	gluSphere(ball, 1000, 128, 128);

	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//---------SKYBOX-----------------------//
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess

	glTranslatef(0.0f, 0.0f, -15.0f);

	//Building 1
	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(5.5f, 0.0f, 0.0f);

	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(-5.5f, 0.0f, 0.0f);

	//Building2
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(1.5f, 0.0f, 2.0f);

	//Building4
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0.0f, -0.5f, 0.0f);

	//Building4
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build6);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(4.5f, 0.0f, -3.0f);

	//Building4
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(-4.5f, 0.0f, -5.0f);

	//Building4
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _build4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(-2.2f, 0.0f, -3.0f);

	//Building4
	glBegin(GL_QUADS);

	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinate
	glNormal3f(-0.12f, -0.99f, 0.f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.99f, 0.f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(0.12f, -0.99f, 0.0f);
	glVertex3f(1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	glNormal3f(0.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.97f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.12f, -0.97f, -0.18f);
	glVertex3f(1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glNormal3f(-0.12f, -0.99f, 0.0f);
	glVertex3f(-1.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.12f, -0.99f, -0.18f);
	glVertex3f(-1.0f, -8.0f, -1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); //texture coordinates
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 2000.0);
}


void update(int)
{


	//looping animation logic
	angle += 0.8;
	if (angle > 360.0f)
		angle = angle - 360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);

}