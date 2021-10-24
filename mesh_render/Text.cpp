#include "Text.h"

#include <glut.h>


void Text::glWrite(float x, float y, int* font, std::string text)
{
	glRasterPos2f(x, y);
	for (unsigned i = 0; i < text.size(); i++)
		glutBitmapCharacter(font, (int)text[i]);
}

void Text::drawFpsCounter(int x, int y, int fps)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 12, x + 150, glutGet(GLUT_WINDOW_HEIGHT) - y + 24);

	glColor3f(1.0f, 0.4f, 0.3f);
	this->glWrite(x, glutGet(GLUT_WINDOW_HEIGHT)-y,
		(int*)GLUT_BITMAP_TIMES_ROMAN_24, std::to_string(fps));
}
