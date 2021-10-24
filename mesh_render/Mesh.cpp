#include "Mesh.h"

#include <algorithm>
#include <fstream>
#include <strstream>

#include <glut.h>

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
		triangle triProjected, triTransformed, triViewed;

		// World Matrix Transform
		triTransformed.p[0] = MatrixMultiplyVector(matWorld, tri.p[0]);
		triTransformed.p[1] = MatrixMultiplyVector(matWorld, tri.p[1]);
		triTransformed.p[2] = MatrixMultiplyVector(matWorld, tri.p[2]);

		// Use Cross-Product to get surface normal
		vec3f normal, line1, line2;
		line1 = triTransformed.p[1] - triTransformed.p[0];
		line2 = triTransformed.p[2] - triTransformed.p[0];
		normal = line1 ^ line2;  //operator^ overloaded - cross product
		normal.normalise();

		vec3f vCameraRay = triTransformed.p[0] - vCamera;

		if (normal * vCameraRay < 0.0f)
		{
			//Illumination
			light_direction.normalise();

			//How aligned are light direction and triangle surface normal
			float dp = std::max(0.1f, light_direction * normal);

			// Project triangles from 3D --> 2D
			triProjected.p[0] = MatrixMultiplyVector(matProj,triTransformed.p[0]);
			triProjected.p[1] = MatrixMultiplyVector(matProj, triTransformed.p[1]);
			triProjected.p[2] = MatrixMultiplyVector(matProj, triTransformed.p[2]);

			triProjected.p[0] = triProjected.p[0] / triProjected.p[0].w;
			triProjected.p[1] = triProjected.p[1] / triProjected.p[1].w;
			triProjected.p[2] = triProjected.p[2] / triProjected.p[2].w;

			// Scale into view
			vec3f vOffsetView = { 1,1,0 };
			triProjected.p[0] = triProjected.p[0] + vOffsetView;
			triProjected.p[1] = triProjected.p[1] + vOffsetView;
			triProjected.p[2] = triProjected.p[2] + vOffsetView;

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