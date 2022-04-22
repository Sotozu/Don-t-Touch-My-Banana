#include <windows.h>											// Header File For Windows
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library

#include "Renderer.h"

Renderer* Renderer::_Instance = NULL;

Renderer* Renderer::CreateInstance()
{
	if (_Instance != NULL) return _Instance;
	else _Instance = new Renderer();

	return _Instance;
}

void Renderer::DrawSquare(float x, float y)
{
    float halfside = 10.0f;

    glColor3d(0xFF, 0, 0);
    glBegin(GL_POLYGON);

    glVertex2d(x + halfside, y + halfside); // bot right
    glVertex2d(x - halfside, y + halfside); // bot left
    glVertex2d(x - halfside, y - halfside); // top left
    glVertex2d(x + halfside, y - halfside); // top right

    glEnd();
}

void Renderer::DrawSprite(float x, float y, unsigned int spriteID, float width, float height, int tex_col, int tex_row, int totalColumns, int totalRows, float extend_Y, float extend_X, bool flip)
{
    //Will give us texel coordinates (s,t) scaled to [0,1] range
    float tex_x_min;
    float tex_x_max;

    if (flip)
    {
        tex_x_max = static_cast<float>(tex_col) / totalColumns;
        tex_x_min = (tex_x_max + 1.f / totalColumns) * extend_X;
    }
    else
    {
        tex_x_min = static_cast<float>(tex_col) / totalColumns;
        tex_x_max = (tex_x_min + 1.f / totalColumns) * extend_X;
    }
    const float tex_y_min = static_cast<float>(tex_row) / totalRows;
    const float tex_y_max = (tex_y_min + 1.f / totalRows) * extend_Y;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, spriteID);
    glBegin(GL_QUADS);

    glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

    glTexCoord2f(tex_x_min, tex_y_max);
    glVertex3f(x - width, y + height, 0.0);

    glTexCoord2f(tex_x_min, tex_y_min);
    glVertex3f(x - width, y - height, 0.0);

    glTexCoord2f(tex_x_max, tex_y_min);
    glVertex3f(x + width, y - height, 0.0);

    glTexCoord2f(tex_x_max, tex_y_max);
    glVertex3f(x + width, y + height, 0.0);


    glEnd();

}