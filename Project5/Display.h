#pragma once

#include "glut.h"

class Display
{


private :
	
	 
	
	int width, height;
	char * title;
	GLubyte* pixels;
	GLuint texture;
	 
	
	 
public:
 
	
	 
	Display(int  width, int height, const char* title);
	~Display();



	 
	void setPicture(GLubyte* pic);
	void show();
 
	int getWidth();
	int getHeight();

 
 
	


};

