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

void WorldMatrix::translate(Shader& shader, float x, float y, float z)
{
	GLfloat m[16];
	glTranslatef(x, y, z);

	glGetFloatv(GL_PROJECTION_MATRIX, m);
	matProj.convertArrayToMatrix(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	matModelView.convertArrayToMatrix(m);
	MVP = matModelView * matProj;
	
	MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);
}

void WorldMatrix::rotate(Shader& shader, float angle, vec3f vRotateAround)
{
	GLfloat m[16];
	glRotatef(angle, vRotateAround.x, vRotateAround.y, vRotateAround.z);

	glGetFloatv(GL_PROJECTION_MATRIX, m);
	matProj.convertArrayToMatrix(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	matModelView.convertArrayToMatrix(m);
	MVP = matModelView * matProj;

	MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);
}

void WorldMatrix::scale(Shader& shader, float scaleX, float scaleY, float scaleZ)
{
	GLfloat m[16];
	glScalef(scaleX, scaleY, scaleZ);

	glGetFloatv(GL_PROJECTION_MATRIX, m);
	matProj.convertArrayToMatrix(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	matModelView.convertArrayToMatrix(m);
	MVP = matModelView * matProj;

	MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);
}

