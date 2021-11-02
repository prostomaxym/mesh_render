#include "Light.h"

#include "..\main.h"

Light::Light()
{
	lightPos_ = { 0.0f,0.0f,0.0f };
	viewPos_ = { 0.0f,0.0f,0.0f };
	lightColor_ = { 0.0f,0.0f,0.0f };
	lightDistance_ = 0.0f;
	lightPower_ = 0.0f;
	dayPeriod_ = 0.0f;
	
	lightPosUniform_ = NULL;
	viewPosUniform_ = NULL;
	lightColorUniform_ = NULL;
	lightPowerUniform_ = NULL;
}

Light::Light(vec3f lightPos, float power, vec3f color, float period)
{
	lightPos_ = lightPos;
	viewPos_ = {0.0f, 0.0f, 0.0f };
	lightColor_ = color;
	lightPower_ = power;
	lightDistance_ = sqrtf(lightPos_.x * lightPos_.x + lightPos_.y * lightPos_.y + lightPos_.z * lightPos_.z);
	dayPeriod_ = lightDistance_ * 2.0f / period;

	lightPosUniform_ = NULL;
	viewPosUniform_ = NULL;
	lightColorUniform_ = NULL;
	lightPowerUniform_ = NULL;
}

Light::Light(float distance, float power, vec3f color, float zOffset, float period)
{
	lightDistance_ = distance;
	lightPos_ = { 0.0f, distance, zOffset };
	viewPos_ = { 0.0f, 0.0f, 0.0f };
	lightColor_ = color;
	lightPower_ = power;
	dayPeriod_ = 2.0f * lightDistance_ / (period * 1000.0f);

	lightPosUniform_ = NULL;
	viewPosUniform_ = NULL;
	lightColorUniform_ = NULL;
	lightPowerUniform_ = NULL;
}

void Light::initLight(Shader& shader, Camera& cam)
{
	//Light source position
	lightPosUniform_ = glGetUniformLocation(shader.getID(), "lightPos");
	glUniform3f(lightPosUniform_, lightPos_.x, lightPos_.y, lightPos_.z);

	//Camera position
	viewPos_ = cam.getCameraPos();
	viewPosUniform_ = glGetUniformLocation(shader.getID(), "viewPos");
	glUniform3f(viewPosUniform_, viewPos_.x, viewPos_.y, viewPos_.z);

	//Light color
	lightColorUniform_ = glGetUniformLocation(shader.getID(), "lightColor");
	glUniform3f(lightColorUniform_, lightColor_.x, lightColor_.y, lightColor_.z);

	//Light power
	lightPowerUniform_ = glGetUniformLocation(shader.getID(), "lightPower");
	glUniform1f(lightPowerUniform_, lightPower_);
}

void Light::updateStaticLight(Shader& shader, Camera& cam)
{
	//Camera position
	viewPos_ = cam.getCameraPos();
	glUniform3f(viewPosUniform_, viewPos_.x, viewPos_.y, viewPos_.z);
}

void Light::updateDynamicLight(Shader& shader, Camera& cam)
{
	//Day time based light position
	if (lightPos_.x > lightDistance_) lightPos_.x = -lightDistance_;
	lightPos_.x += dt * dayPeriod_;
	lightPos_.y = sqrtf(lightDistance_ * lightDistance_ - lightPos_.x * lightPos_.x);
	glUniform3f(lightPosUniform_, lightPos_.x, lightPos_.y, lightPos_.z);

	//Camera position
	viewPos_ = cam.getCameraPos();
	glUniform3f(viewPosUniform_, viewPos_.x, viewPos_.y, viewPos_.z);
}