#pragma once

class Renderer
{
public:
	static Renderer* CreateInstance();
	static Renderer* GetInstance() { return _Instance; };

	void DrawSquare(float x, float y);
	void DrawSprite(float x, float y, unsigned int spriteID, float width, float height, int tex_col = 0, int tex_row = 0, int totalColumns = 1, int totalRows = 1, float extend_Y = 1.0f, float extend_X = 1.0f, bool flip = false);

private:
	static Renderer* _Instance;

};