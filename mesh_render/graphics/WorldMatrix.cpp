#include "WorldMatrix.h"

WorldMatrix::WorldMatrix() :
	matProj { 0.0f },
	matModelView { 0.0f },
	MVP { 0.0f }
{
	MVPmatUniform = NULL;
}

void WorldMatrix::init(Shader& shader)
{
	GLfloat m[16];
	glGetFloatv(GL_PROJECTION_MATRIX, m);
	matProj.convertArrayToMatrix(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	matModelView.convertArrayToMatrix(m);

	MVP = matModelView * matProj;
	GLuint MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);
}

void WorldMatrix::update(Shader& shader)
{
	GLfloat m[16];
	glGetFloatv(GL_PROJECTION_MATRIX, m);
	matProj.convertArrayToMatrix(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	matModelView.convertArrayToMatrix(m);

	MVP =  matModelView * matProj;
	MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);
}
