#include "Light.h"

Light::Light()
{
	lightPos_ = { 0.0f,0.0f,0.0f };
	viewPos_ = { 0.0f,0.0f,0.0f };
	lightColor_ = { 0.0f,0.0f,0.0f };
	
	lightPosUniform_ = NULL;
	viewPosUniform_ = NULL;
	lightColorUniform_ = NULL;
}

Light::Light(vec3f lightPos, vec3f viewPos, vec3f color)
{
	lightPos_ = lightPos;
	viewPos_ = viewPos;
	lightColor_ = color;
}

void Light::initLight(Shader& shader, Camera& cam)
{
	//Static light position
	lightPosUniform_ = glGetUniformLocation(shader.getID(), "lightPos");
	glUniform3f(lightPosUniform_, lightPos_.x, lightPos_.y, lightPos_.z);

	//Camera position
	viewPos_ = cam.getCameraPos();
	viewPosUniform_ = glGetUniformLocation(shader.getID(), "viewPos");
	glUniform3f(viewPosUniform_, viewPos_.x, viewPos_.y, viewPos_.z);

	//Light color
	lightColorUniform_ = glGetUniformLocation(shader.getID(), "lightColor");
	glUniform3f(lightColorUniform_, lightColor_.x, lightColor_.y, lightColor_.z);
}

void Light::updateLight(Shader& shader, Camera& cam)
{
	//Camera position
	viewPos_ = cam.getCameraPos();
	viewPosUniform_ = glGetUniformLocation(shader.getID(), "viewPos");
	glUniform3f(viewPosUniform_, viewPos_.x, viewPos_.y, viewPos_.z);
}