#include "Mesh.h"

#include <glut.h>

mat4x4 matProj, matRotZ, matRotX;

void mesh::drawMesh(float r, float g, float b)
{
	for (auto tri: tris)
	{
		triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

		// Rotate in Z-Axis
		MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
		MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
		MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

		// Rotate in X-Axis
		MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
		MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
		MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

		// Offset into the screen
		triTranslated = triRotatedZX;
		triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
		triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
		triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

		// Project triangles from 3D --> 2D
		MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
		MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
		MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

		// Scale into view
		triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
		triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
		triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
		triProjected.p[0].x *= 0.5f * (float)glutGet(GLUT_WINDOW_WIDTH);
		triProjected.p[0].y *= 0.5f * (float)glutGet(GLUT_WINDOW_HEIGHT);
		triProjected.p[1].x *= 0.5f * (float)glutGet(GLUT_WINDOW_WIDTH);
		triProjected.p[1].y *= 0.5f * (float)glutGet(GLUT_WINDOW_HEIGHT);
		triProjected.p[2].x *= 0.5f * (float)glutGet(GLUT_WINDOW_WIDTH);
		triProjected.p[2].y *= 0.5f * (float)glutGet(GLUT_WINDOW_HEIGHT);

		/*glBegin(GL_TRIANGLES);
		glColor3f(r,g,b);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glVertex2f(triProjected.p[1].x, triProjected.p[1].y);
		glVertex2f(triProjected.p[2].x, triProjected.p[2].y);
		glEnd();*/

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glVertex2f(triProjected.p[1].x, triProjected.p[1].y);
		glVertex2f(triProjected.p[2].x, triProjected.p[2].y);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glEnd();
	}
}

void MultiplyMatrixVector(vec3f& i, vec3f& o, mat4x4& m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}