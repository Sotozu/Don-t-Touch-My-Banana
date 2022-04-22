#pragma once
void endOpenGLDrawing();
void startOpenGLDrawing();
void initOpenGLDrawing( GL_Window *window, Keys *keys, float backRed, float backGreen, float backBlue);

#ifdef _GLOBALS
#define extern 
#endif

extern GL_Window*	g_window;
extern Keys*		g_keys;
extern float		deltaTime;

#undef extern