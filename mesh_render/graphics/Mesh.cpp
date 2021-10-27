#include "Mesh.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <strstream>

#include <glut.h>


mesh::mesh()
{
	
}

mesh::mesh(std::vector <triangle> polygons)
{
	this->tris = std::vector <triangle>(polygons);
}

void mesh::drawMesh(float r, float g, float b, 
		World& world,
		mat4x4& matView,
		vec3f& vCamera, 
		vec3f& light_direction)
{
	// Store triagles for rastering later
	std::vector<triangle> vecTrianglesToRaster;
	for (auto& tri: tris)
	{
		triangle triProjected, triTransformed, triViewed;

		// World Matrix Transform
		triTransformed.p[0] = MatrixMultiplyVector(world.matWorld, tri.p[0]);
		triTransformed.p[1] = MatrixMultiplyVector(world.matWorld, tri.p[1]);
		triTransformed.p[2] = MatrixMultiplyVector(world.matWorld, tri.p[2]);

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

			triViewed.p[0] = MatrixMultiplyVector(matView, triTransformed.p[0]);
			triViewed.p[1] = MatrixMultiplyVector(matView, triTransformed.p[1]);
			triViewed.p[2] = MatrixMultiplyVector(matView, triTransformed.p[2]);

			// Clip Viewed Triangle against near plane, this could form two additional
			// additional triangles. 
			int nClippedTriangles = 0;
			triangle clipped[2];
			nClippedTriangles = TriangleClipAgainstPlane({ 0.0f, 0.0f , 0.1f }, { 0.0f, 0.0f, 1.0f },
				triViewed, clipped[0], clipped[1]);

			for (int n = 0; n < nClippedTriangles; n++)
			{
				// Project triangles from 3D --> 2D
				triProjected.p[0] = MatrixMultiplyVector(world.matProj, clipped[n].p[0]);
				triProjected.p[1] = MatrixMultiplyVector(world.matProj, clipped[n].p[1]);
				triProjected.p[2] = MatrixMultiplyVector(world.matProj, clipped[n].p[2]);

				// Scale into view
				triProjected.p[0] = triProjected.p[0] / triProjected.p[0].w;
				triProjected.p[1] = triProjected.p[1] / triProjected.p[1].w;
				triProjected.p[2] = triProjected.p[2] / triProjected.p[2].w;

				// Offset verts into visible normalised space
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
	}
	// Sort triangles from back to front
	std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
		{
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
		});

	for (auto& t : vecTrianglesToRaster)
	{
		//rasterise triangles
		glBegin(GL_TRIANGLES);
		glColor3f(r * t.dp, g * t.dp, b * t.dp);
		glVertex2f(t.p[0].x, t.p[0].y);
		glVertex2f(t.p[1].x, t.p[1].y);
		glVertex2f(t.p[2].x, t.p[2].y);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(t.p[0].x, t.p[0].y);
		glVertex2f(t.p[1].x, t.p[1].y);
		glVertex2f(t.p[2].x, t.p[2].y);
		glVertex2f(t.p[0].x, t.p[0].y);
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

int TriangleClipAgainstPlane(vec3f plane_p, vec3f plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2)
{
	// Make sure plane normal is indeed normal
	plane_n.normalise();

	// Return signed shortest distance from point to plane, plane normal must be normalised
	auto dist = [&](vec3f& p)
	{
		p.normalise();
		vec3f n = p;
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - plane_n * plane_p);
	};

	// Create two temporary storage arrays to classify points either side of plane
	// If distance sign is positive, point lies on "inside" of plane
	vec3f* inside_points[3];  int nInsidePointCount = 0;
	vec3f* outside_points[3]; int nOutsidePointCount = 0;

	// Get signed distance of each point in triangle to plane
	float d0 = dist(in_tri.p[0]);
	float d1 = dist(in_tri.p[1]);
	float d2 = dist(in_tri.p[2]);

	if (d0 >= 0)	inside_points[nInsidePointCount++] = &in_tri.p[0];
	else  outside_points[nOutsidePointCount++] = &in_tri.p[0];

	if (d1 >= 0)  inside_points[nInsidePointCount++] = &in_tri.p[1]; 
	else  outside_points[nOutsidePointCount++] = &in_tri.p[1]; 

	if (d2 >= 0)  inside_points[nInsidePointCount++] = &in_tri.p[2]; 
	else  outside_points[nOutsidePointCount++] = &in_tri.p[2]; 

	// Now classify triangle points, and break the input triangle into 
	// smaller output triangles if required.

	if (nInsidePointCount == 0)
	{
		// All points lie on the outside of plane, so clip whole triangle
		// It ceases to exist
		return 0; // No returned triangles are valid
	}

	if (nInsidePointCount == 3)
	{
		// All points lie on the inside of plane, so do nothing
		// and allow the triangle to simply pass through
		out_tri1 = in_tri;
		return 1; // Just the one returned original triangle is valid
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		// Triangle should be clipped. As two points lie outside
		// the plane, the triangle simply becomes a smaller triangle
		// Copy appearance info to new triangle
		out_tri1.dp = in_tri.dp;

		// The inside point is valid, so keep that...
		out_tri1.p[0] = *inside_points[0];

		// but the two new points are at the locations where the 
		// original sides of the triangle (lines) intersect with the plane
		out_tri1.p[1].intersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out_tri1.p[2].intersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

		return 1; // Return the newly formed single triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		// Triangle should be clipped. As two points lie inside the plane,
		// the clipped triangle becomes a "quad". Fortunately, we can
		// represent a quad with two new triangles

		// Copy appearance info to new triangles
		out_tri1.dp = in_tri.dp;
		out_tri2.dp = in_tri.dp;

		// The first triangle consists of the two inside points and a new
		// point determined by the location where one side of the triangle
		// intersects with the plane
		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = *inside_points[1];
		out_tri1.p[2].intersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

		// The second triangle is composed of one of he inside points, a
		// new point determined by the intersection of the other side of the 
		// triangle and the plane, and the newly created point above
		out_tri2.p[0] = *inside_points[1];
		out_tri2.p[1] = out_tri1.p[2];
		out_tri2.p[2].intersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

		return 2; // Return two newly formed triangles which form a quad
	}
}