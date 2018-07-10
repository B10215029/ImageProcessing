#include "MainForm.h"
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>

HGLRC ImageProcessing::MainForm::initializeOpenGLContext(HDC hDC)
{
	HGLRC hGLRC = NULL;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
		1,                                // version number 
		PFD_DRAW_TO_WINDOW |              // support window 
		PFD_SUPPORT_OPENGL,               // support OpenGL 
		PFD_TYPE_RGBA,                    // RGBA type 
		24,                               // 24-bit color depth 
		0, 0, 0, 0, 0, 0,                 // color bits ignored 
		0,                                // no alpha buffer 
		0,                                // shift bit ignored 
		0,                                // no accumulation buffer 
		0, 0, 0, 0,                       // accum bits ignored 
		32,                               // 32-bit z-buffer     
		0,                                // no stencil buffer 
		0,                                // no auxiliary buffer 
		PFD_MAIN_PLANE,                   // main layer 
		0,                                // reserved 
		0, 0, 0                           // layer masks ignored 
	};

	int cpf = ChoosePixelFormat(hDC, &pfd);
	if (!cpf) {
		std::cerr << "Choose Pixel Format Error\n";
		return false;
	}

	SetPixelFormat(hDC, cpf, &pfd);

	hGLRC = wglCreateContext(hDC);
	if (!hGLRC) {
		std::cerr << "Create Render Context Error\n";
		return false;
	}

	if (!wglMakeCurrent(hDC, hGLRC)) {
		hGLRC = NULL;
		std::cerr << "wglMakeCurrent Error\n";
		return false;
	}

	glViewport(0, 0, panel1->Width, panel1->Height);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	wglMakeCurrent(NULL, NULL);

	return hGLRC;
}

void ImageProcessing::MainForm::updateTexture()
{
	wglMakeCurrent(hDC, hGLRC);

	if (this->texture) {
		GLuint texture = this->texture;
		glDeleteTextures(1, &texture);
		this->texture = 0;
	}

	if (image) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gLNEARESTToolStripMenuItem->Checked ? GL_NEAREST : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gLNEARESTToolStripMenuItem->Checked ? GL_NEAREST : GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		this->texture = texture;
	}

	wglMakeCurrent(NULL, NULL);
	draw();
}

void ImageProcessing::MainForm::draw()
{
	wglMakeCurrent(hDC, hGLRC);
	glViewport(0, 0, panel1->Width, panel1->Height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (texture) {
		float scaleX = ((float)image->width / image->height) / ((float)panel1->Width / panel1->Height);
		float scaleY = ((float)image->height / image->width) / ((float)panel1->Height / panel1->Width);
		float offsetX = (float)image->offsetX / panel1->Width * 2;
		float offsetY = -(float)image->offsetY / panel1->Height * 2;
		scaleX = (scaleX < 1 ? scaleX : 1) * pow(1.5, image->scale);
		scaleY = (scaleY < 1 ? scaleY : 1) * pow(1.5, image->scale);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0, -1);
		glVertex2f(-scaleX + offsetX, scaleY + offsetY);
		glTexCoord2f(1, -1);
		glVertex2f(scaleX + offsetX, scaleY + offsetY);
		glTexCoord2f(1, 0);
		glVertex2f(scaleX + offsetX, -scaleY + offsetY);
		glTexCoord2f(0, 0);
		glVertex2f(-scaleX + offsetX, -scaleY + offsetY);
		glEnd();
	}

	wglMakeCurrent(NULL, NULL);
}
