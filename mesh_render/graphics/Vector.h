#ifndef MESH_RENDER_VECTOR_H_
#define MESH_RENDER_VECTOR_H_

struct vec3f
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;


	vec3f operator+(vec3f& other); //add 2 vectors
	vec3f operator-(vec3f& other); //subtruct 2 vectors
	vec3f operator*(float k);  //multiply vector by scalar
	vec3f operator/(float k);  //divide vector by scalar (k!=0) else do nothing

	float operator*(vec3f& other); //dot product of 2 vectors
	vec3f operator^(vec3f& other);  //cross product of 2 vectors

	float getLength();
	void normalise(); //normalise by its lenght
};

extern vec3f vCamera;
extern vec3f light_direction;

#endif  // MESH_RENDER_VECTOR_H_