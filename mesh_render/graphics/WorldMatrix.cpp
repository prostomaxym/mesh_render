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

	GLuint modelViewUniform = glGetUniformLocation(shader.getID(), "modelview");
	glUniformMatrix4fv(modelViewUniform, 1, GL_FALSE, &matModelView.m[0][0]);

	MVP =  matModelView * matProj;
	GLuint MVPmatUniform = glGetUniformLocation(shader.getID(), "MVP");
	glUniformMatrix4fv(MVPmatUniform, 1, GL_FALSE, &MVP.m[0][0]);

	GLfloat inv[16], tr[16];
	invertMatrix(m, inv);
	transposeMatrix(&inv[0], &tr[0], 4, 4);
	GLuint matNormal = glGetUniformLocation(shader.getID(), "matNormal");
	glUniformMatrix4fv(matNormal, 1, GL_FALSE, &tr[0]);
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
