#ifndef MESH_RENDER_GRAPHICS_VECTOR_H_
#define MESH_RENDER_GRAPHICS_VECTOR_H_

struct vec2f
{
	float u = 0.0f;
	float v = 0.0f;
	float w = 1.0f;
};


struct vec3f
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	vec3f operator+(vec3f& other);  //add 2 vectors
	vec3f operator-(vec3f& other);  //subtruct 2 vectors
	vec3f operator*(float k);  //multiply vector by scalar
	vec3f operator/(float k);  //divide vector by scalar (k!=0) else do nothing

	float operator*(vec3f& other);  //dot product of 2 vectors
	vec3f operator^(vec3f& other);  //cross product of 2 vectors

	float getLength();
	void normalise();
	void intersectPlane(vec3f& plane_p, vec3f& plane_n, vec3f& lineStart, vec3f& lineEnd, float& t);
};
#endif  // MESH_RENDER_GRAPHICS_VECTOR_H_