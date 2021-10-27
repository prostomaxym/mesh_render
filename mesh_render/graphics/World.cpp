#include "World.h"

void World::makeProjection(float fNear, float fFar, float fFov)
{
	this->matProj.makeProjection(fNear, fFar, fFov);
}

void World::makeRotation(float fXang, float fYang, float fZang)
{
	this->matRotX.rotateX(fXang);
	this->matRotY.rotateY(fYang);
	this->matRotZ.rotateZ(fZang);
}

void World::makeTranslation(float x, float y, float z)
{
	this->matTrans.makeTranslation(x, y, z);
}

void World::makeIdentity()
{
	this->matWorld.makeIdentity();
}

void World::update()
{
	this->matWorld = matRotX * matRotZ * matRotY; //transform by rotation
	this->matWorld = matWorld * matTrans;  //transform by translation
}