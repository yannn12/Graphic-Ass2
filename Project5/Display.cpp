
#include <string>

#include "Display.h"
#include "glut.h"
 

 
static void displayFunc();
static GLuint currentTexture;
static int currentWidth, currentHeight;
 

Display::Display(int  width, int height, const char* title_) : width(width), height(height)
{

	title = (char*)malloc(strlen(title_) + 1);
	strcpy_s(title, strlen(title_) + 1, title_);
	

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	glEnable(GL_TEXTURE_2D);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, -2.0);
	glClearColor(0, 0, 0, 0);

}

Display::~Display()
{
	delete (title);
}


 
void Display::setPicture(GLubyte* pic)
{
	pixels=pic;
	 
	glGenTextures(1, &texture);  //generate place for new texture
	glBindTexture(GL_TEXTURE_2D, texture); // initialize  texure 

	//texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//build texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	
 
}
void Display::show()
{

	
	currentHeight = height;
	currentWidth = width;
	currentTexture = texture;
	glutDisplayFunc(displayFunc);
	glutMainLoop();
}
 
int Display::getWidth() { return width; }
int Display::getHeight(){ return height;}

 
void displayFunc()
{	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glViewport(0, 0, currentWidth, currentHeight);
	glBindTexture(GL_TEXTURE_2D, currentTexture);
	glColor3f(1.0f, 1.0f, 1.0f);

	

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); //adapt texture to shape
	glVertex3f(-1.0, -1.0f, 1.0);

	glTexCoord2f(1, 0);  //adapt texture to shape
	glVertex3f(1.0, -1.0f, 1.0);

	glTexCoord2f(1, 1);//adapt texture to shape
	glVertex3f(1.0, 1.0f, 1.0);

	glTexCoord2f(0, 1);//adapt texture to shape
	glVertex3f(-1.0, 1.0f, 1.0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();

	glFlush();

}

