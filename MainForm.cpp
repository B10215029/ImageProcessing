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
	glClearColor(0, 0, 0, 1);
	wglMakeCurrent(NULL, NULL);

	return hGLRC;
}

void ImageProcessing::MainForm::drawImage()
{
	wglMakeCurrent(hDC, hGLRC);
	glClear(GL_COLOR_BUFFER_BIT);

	wglMakeCurrent(NULL, NULL);
}
