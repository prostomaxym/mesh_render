#include "Mesh.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <strstream>

#include <glut.h>

#include "../main.h"


mesh::mesh()
{
	
}

mesh::mesh(std::vector <triangle> polygons)
{
	this->tris = std::vector <triangle>(polygons);
}

void mesh::drawMesh(float r, float g, float b)
{
	// Store triagles for rastering later
	for (auto& tri : tris)
	{
		//rasterise triangles
		glBegin(GL_TRIANGLES);
		glBindTexture(GL_TEXTURE_2D, texture);

		glColor3f(r, g, b);
		/*glTexCoord3f(t.t[0].u, t.t[0].v, t.t[0].w); glVertex2f(t.p[0].x, t.p[0].y);
		glTexCoord3f(t.t[1].u, t.t[1].v, t.t[1].w); glVertex2f(t.p[1].x, t.p[1].y);
		glTexCoord3f(t.t[2].u, t.t[2].v, t.t[2].w); glVertex2f(t.p[2].x, t.p[2].y);*/

		glTexCoord2f(tri.t[0].u, tri.t[0].v);  
		glVertex3f(tri.p[0].x, tri.p[0].y, tri.p[0].z);
		glTexCoord2f(tri.t[1].u, tri.t[1].v);  
		glVertex3f(tri.p[1].x, tri.p[1].y, tri.p[1].z);
		glTexCoord2f(tri.t[2].u, tri.t[2].v);  
		glVertex3f(tri.p[2].x, tri.p[2].y, tri.p[2].z);

		glEnd();
	}
}

bool mesh::loadFromObjectFile(std::string sFilename, bool bHasTexture)
{
	std::ifstream f(sFilename);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<vec3f> verts;
	std::vector<vec2f> texs;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			if (line[1] == 't')
			{
				vec2f v;
				s >> junk >> junk >> v.u >> v.v;
				// A little hack for the spyro texture
				//v.u = 1.0f - v.u;
				//v.v = 1.0f - v.v;
				texs.push_back(v);
			}
			else
			{
				vec3f v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
		}

		if (!bHasTexture)
		{
			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}
		else
		{
			if (line[0] == 'f')
			{
				s >> junk;

				std::string tokens[6];
				int nTokenCount = -1;

				while (!s.eof())
				{
					char c = s.get();
					if (c == ' ' || c == '/')
						nTokenCount++;
					else
						tokens[nTokenCount].append(1, c);
				}

				tokens[nTokenCount].pop_back();

				tris.push_back({ verts[stoi(tokens[0]) - 1], verts[stoi(tokens[2]) - 1], verts[stoi(tokens[4]) - 1],
					texs[stoi(tokens[1]) - 1], texs[stoi(tokens[3]) - 1], texs[stoi(tokens[5]) - 1] });
			}
		}
	}
	return true;
}
