#include "Text.h"

#include <glut.h>

void Text::rasterText(float x, float y, int* font, std::string text)
{
	glRasterPos2f(x, y);
	for (unsigned i = 0; i < text.size(); i++)
		glutBitmapCharacter(font, (int)text[i]);
}

void Text::drawText(int x, int y,std::string text, int number, float r, float g, float b)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_WIDTH));
	glColor3f(r, g, b);
	rasterText(x, glutGet(GLUT_WINDOW_HEIGHT) - y,
		(int*)GLUT_BITMAP_TIMES_ROMAN_24, text + std::to_string(number));
}
