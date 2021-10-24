#include "Mesh.h"

#include <algorithm>
#include <fstream>
#include <strstream>

#include <glut.h>

mat4x4 matProj, matRotZ, matRotX;
vec3f vCamera = { 0.0f, 0.0f, 0.0f };
vec3f light_direction = { 0.0f, 1.0f, -3.0f };

void vec3f::set(float first, float second, float third)
{
	x = first;
	y = second;
	z = third;
}

mesh::mesh()
{
	
}

mesh::mesh(std::vector <triangle> input)
{
	this->tris = std::vector <triangle>(input);
}

void mesh::drawMesh(float r, float g, float b)
{
	// Store triagles for rastering later
	std::vector<triangle> vecTrianglesToRaster;
	for (auto& tri: tris)
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
		triTranslated.p[0].z = triRotatedZX.p[0].z + 8.0f;
		triTranslated.p[1].z = triRotatedZX.p[1].z + 8.0f;
		triTranslated.p[2].z = triRotatedZX.p[2].z + 8.0f;

		// Use Cross-Product to get surface normal
		vec3f normal, line1, line2;
		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

		normal.x = line1.y * line2.z - line1.z * line2.y;
		normal.y = line1.z * line2.x - line1.x * line2.z;
		normal.z = line1.x * line2.y - line1.y * line2.x;

		//Normalising to unit vector
		float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= l; normal.y /= l; normal.z /= l;
		if (normal.x * (triTranslated.p[0].x - vCamera.x) +
			normal.y * (triTranslated.p[0].y - vCamera.y) +
			normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
		{
			float l = sqrtf(light_direction.x * light_direction.x 
				+ light_direction.y * light_direction.y 
				+ light_direction.z * light_direction.z);
			light_direction.x /= l; light_direction.y /= l; light_direction.z /= l;

			// How similar is normal to light direction
			float dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

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
			triProjected.dp = dp;

			// Store triangle for sorting
			vecTrianglesToRaster.push_back(triProjected);
		}
	}
	// Sort triangles from back to front
	std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
		{
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
		});

	for (auto& triProjected : vecTrianglesToRaster)
	{
		//rasterise trianles
		glBegin(GL_TRIANGLES);
		glColor3f(r * triProjected.dp, g * triProjected.dp, b * triProjected.dp);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glVertex2f(triProjected.p[1].x, triProjected.p[1].y);
		glVertex2f(triProjected.p[2].x, triProjected.p[2].y);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glVertex2f(triProjected.p[1].x, triProjected.p[1].y);
		glVertex2f(triProjected.p[2].x, triProjected.p[2].y);
		glVertex2f(triProjected.p[0].x, triProjected.p[0].y);
		glEnd();
	}
}

bool mesh::loadFromObjectFile(std::string sFilename)
{
	std::ifstream f(sFilename);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<vec3f> verts;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char lineType;

		if (line[0] == 'v')
		{
			vec3f v;
			s >> lineType >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}
		else if (line[0] == 'f')
		{
			int f[3];
			s >> lineType >> f[0] >> f[1] >> f[2];
			tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
		}
	}

	return true;
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

void initProjectionMatrix(float zNear, float zFar, float Fov)
{
	float fNear = zNear;
	float fFar = zFar;
	float fFov = Fov;
	float fAspectRatio = (float)glutGet(GLUT_WINDOW_HEIGHT) / (float)glutGet(GLUT_WINDOW_WIDTH);
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
}
