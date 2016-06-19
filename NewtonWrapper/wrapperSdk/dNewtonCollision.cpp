/* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 
* 3. This notice may not be removed or altered from any source distribution.
*/


#include "stdafx.h"
#include "dNewtonBody.h"
#include "dNewtonWorld.h"
#include "dNewtonCollision.h"


dMatrix dNewtonCollision::m_primitiveAligment(dVector(0.0f, 1.0f, 0.0f, 0.0f), dVector(-1.0f, 0.0f, 0.0f, 0.0f), dVector(0.0f, 0.0f, 1.0f, 0.0f), dVector(0.0f, 0.0f, 0.0f, 1.0f));

#if 0
dNewtonCollision::dNewtonCollision(const dNewtonCollision& srcCollision, NewtonCollision* const shape)
//	:dNewtonAlloc()
	:dNewtonMaterial(srcCollision)
	,m_shape (shape)
	,m_userData(srcCollision.m_userData)
	,m_type (srcCollision.m_type)
{
	SetShape(shape);
}



void* dNewtonCollision::GetUserData() const
{
	return m_userData;
}

void dNewtonCollision::SetUserData(void* const userData)
{
	m_userData = userData;
}

dFloat dNewtonCollision::GetVolume () const
{
	return NewtonConvexCollisionCalculateVolume (m_shape);
}


void dNewtonCollision::GetMatrix (dFloat* const matrix) const
{
	NewtonCollisionGetMatrix(m_shape, matrix);
}


void dNewtonCollision::GetScale(dFloat& x, dFloat& y, dFloat& z) const
{
	NewtonCollisionGetScale(m_shape, &x, &y, &z);
}


NewtonCollision* dNewtonCollision::GetShape() const
{
	return m_shape;
}






void dNewtonCollision::CalculateAABB (const dFloat* const matrix, dFloat* const p0, dFloat* const p1) const
{
	NewtonCollisionCalculateAABB (m_shape, matrix, p0, p1);
}

void dNewtonCollision::CalculateBuoyancyAcceleration (const dFloat* const matrix, const dFloat* const shapeOrigin, const dFloat* const gravityVector, const dFloat* const fluidPlane, dFloat fluidDensity, dFloat fluidViscosity, dFloat* const accel, dFloat* const alpha)
{
	NewtonConvexCollisionCalculateBuoyancyAcceleration (m_shape, matrix, shapeOrigin, gravityVector, fluidPlane, fluidDensity, fluidViscosity, accel, alpha);
}




dNewtonCollisionMesh::dNewtonCollisionMesh(dNewton* const world, dLong collisionMask)
	:dNewtonCollision(m_mesh, collisionMask)
{
	SetShape (NewtonCreateTreeCollision(world->GetNewton(), 0));
}

dNewtonCollisionMesh::dNewtonCollisionMesh (dNewton* const world, const dNewtonMesh& mesh, dLong collisionMask)
	:dNewtonCollision(m_mesh, collisionMask)
{
	SetShape (NewtonCreateTreeCollisionFromMesh (world->GetNewton(), mesh.GetMesh(), 0));
}



void dNewtonCollisionMesh::BeginFace()
{
	NewtonTreeCollisionBeginBuild(m_shape);
}

void dNewtonCollisionMesh::AddFace(int vertexCount, const dFloat* const vertexPtr, int strideInBytes, int faceAttribute)
{
	NewtonTreeCollisionAddFace (m_shape, vertexCount, vertexPtr, strideInBytes, faceAttribute);
}

void dNewtonCollisionMesh::EndFace()
{
	//NewtonTreeCollisionEndBuild (m_shape, 1);
	NewtonTreeCollisionEndBuild (m_shape, 0);
}


dNewtonCollisionScene::dNewtonCollisionScene(dNewton* const world, dLong collisionMask)
	:dNewtonCollision(m_scene, collisionMask)
{
	SetShape (NewtonCreateSceneCollision(world->GetNewton(), 0));
}


void dNewtonCollisionScene::BeginAddRemoveCollision()
{
	NewtonSceneCollisionBeginAddRemove (m_shape);	
}

void* dNewtonCollisionScene::AddCollision(const dNewtonCollision* const collision)
{
	return NewtonSceneCollisionAddSubCollision (m_shape, collision->GetShape());
}

void dNewtonCollisionScene::RemoveCollision (void* const handle)
{
	NewtonSceneCollisionRemoveSubCollision (m_shape, handle);
}

void dNewtonCollisionScene::EndAddRemoveCollision()
{
	NewtonSceneCollisionEndAddRemove(m_shape);	
}

void* dNewtonCollisionScene::GetFirstNode () const 
{
	return NewtonSceneCollisionGetFirstNode (m_shape);
}

void* dNewtonCollisionScene::GetNextNode (void* const collisionNode) const 
{
	return NewtonSceneCollisionGetNextNode (m_shape, collisionNode);
}

dNewtonCollision* dNewtonCollisionScene::GetChildFromNode(void* const collisionNode) const
{
	NewtonCollision* const collision = NewtonSceneCollisionGetCollisionFromNode (m_shape, collisionNode);
	return (dNewtonCollision*) NewtonCollisionGetUserData (collision);
}


dNewtonCollisionConvexHull::dNewtonCollisionConvexHull (dNewton* const world, const dNewtonMesh& mesh, dLong collisionMask)
	:dNewtonCollision(m_convex, collisionMask)
{
	SetShape (NewtonCreateConvexHullFromMesh (world->GetNewton(), mesh.GetMesh(), 0.001f, 0));
}

dNewtonCollisionCompound::dNewtonCollisionCompound (dNewton* const world, const dNewtonMesh& mesh, dLong collisionMask)
	:dNewtonCollision(m_compound, collisionMask)
{
	SetShape (NewtonCreateCompoundCollisionFromMesh (world->GetNewton(), mesh.GetMesh(), 0.001f, 0, 0));
	
	for (void* node = GetFirstNode(); node; node = GetNextNode(node)) {
		NewtonCollision* const collision = NewtonCompoundCollisionGetCollisionFromNode (m_shape, node);
		dAssert (NewtonCollisionGetType (collision) == SERIALIZE_ID_CONVEXHULL);
		new dNewtonCollisionConvexHull (collision, collisionMask);
	}
}


void dNewtonCollisionCompound::BeginAddRemoveCollision()
{
	NewtonCompoundCollisionBeginAddRemove (m_shape);	
}

void* dNewtonCollisionCompound::AddCollision(const dNewtonCollision* const collision)
{
	return NewtonCompoundCollisionAddSubCollision(m_shape, collision->GetShape());
}

void dNewtonCollisionCompound::RemoveCollision (void* const handle)
{
	NewtonCompoundCollisionRemoveSubCollision (m_shape, handle);
}

void dNewtonCollisionCompound::EndAddRemoveCollision()
{
	NewtonCompoundCollisionEndAddRemove(m_shape);	
}

void* dNewtonCollisionCompound::GetFirstNode () const 
{
	return NewtonCompoundCollisionGetFirstNode (m_shape);
}

void* dNewtonCollisionCompound::GetNextNode (void* const collisionNode) const 
{
	return NewtonCompoundCollisionGetNextNode (m_shape, collisionNode);
}

dNewtonCollision* dNewtonCollisionCompound::GetChildFromNode(void* const collisionNode) const
{
	NewtonCollision* const collision = NewtonCompoundCollisionGetCollisionFromNode (m_shape, collisionNode);
	return (dNewtonCollision*) NewtonCollisionGetUserData (collision);
}

#endif

dNewtonCollision::dNewtonCollision(dNewtonWorld* const world, dLong collisionMask)
	:dAlloc()
	,m_shape(NULL)
	,m_myWorld(world)
{
}

dNewtonCollision::~dNewtonCollision()
{
	DeleteShape();
}

void dNewtonCollision::DeleteShape()
{
	if (m_shape) {
		NewtonDestroyCollision(m_shape);
		m_myWorld->m_collisionCache.Remove(m_collisionCacheNode);
		NewtonCollisionSetUserData(m_shape, NULL);
		m_shape = NULL;
		m_collisionCacheNode = NULL;
	}
}


void dNewtonCollision::SetShape(NewtonCollision* const shape)
{
	m_shape = shape;
	NewtonCollisionSetUserData(m_shape, this);
	m_collisionCacheNode = m_myWorld->m_collisionCache.Append(this);
}

void dNewtonCollision::DebugRenderCallback(void* userData, int vertexCount, const dFloat* faceVertec, int id)
{
	dPoints* const polygon = (dPoints*)faceVertec;
	DrawFaceCallback callback = (DrawFaceCallback)userData;
	callback(polygon, vertexCount);
}

void dNewtonCollision::DebugRender(DrawFaceCallback callback)
{
	dMatrix matrix(dGetIdentityMatrix());
	NewtonCollisionForEachPolygonDo(m_shape, &matrix[0][0], DebugRenderCallback, callback);
}

void dNewtonCollision::SetScale(dFloat scaleX, dFloat scaleY, dFloat scaleZ)
{
	scaleX = dMax(0.01f, dAbs(scaleX));
	scaleY = dMax(0.01f, dAbs(scaleY));
	scaleZ = dMax(0.01f, dAbs(scaleZ));
	NewtonCollisionSetScale(m_shape, scaleX, scaleY, scaleZ);
}

void dNewtonCollision::SetMatrix(const void* const matrixPtr)
{
	dMatrix matrix((dFloat*)matrixPtr);
	NewtonCollisionSetMatrix(m_shape, &matrix[0][0]);
}



dNewtonCollisionNull::dNewtonCollisionNull(dNewtonWorld* const world)
	:dNewtonCollision(world, 0)
{
	SetShape(NewtonCreateNull(m_myWorld->m_world));
}



dNewtonCollisionSphere::dNewtonCollisionSphere(dNewtonWorld* const world, dFloat r)
	:dNewtonCollision(world, 0)
{
	SetShape(NewtonCreateSphere(m_myWorld->m_world, r, 0, NULL));
}


dNewtonCollisionBox::dNewtonCollisionBox(dNewtonWorld* const world, dFloat x, dFloat y, dFloat z)
	:dNewtonCollision(world, 0)
{
	SetShape(NewtonCreateBox(m_myWorld->m_world, x, y, z, 0, NULL));
}

dNewtonCollisionCylinder::dNewtonCollisionCylinder(dNewtonWorld* const world, dFloat radio0, dFloat radio1, dFloat height)
	:dNewtonCollision(world, 0)
{
	SetShape(NewtonCreateCylinder(m_myWorld->m_world, radio0, radio1, height, 0, NULL));
}

void dNewtonCollisionCylinder::SetScale(dFloat x, dFloat y, dFloat z)
{
	dVector scale(m_primitiveAligment.RotateVector(dVector(x, y, z, 0.0f)));
	dNewtonCollision::SetScale(scale.m_x, scale.m_y, scale.m_z);
}

void dNewtonCollisionCylinder::SetMatrix(const void* const matrixPtr)
{
	dMatrix matrix((dFloat*)matrixPtr);
	matrix = m_primitiveAligment * matrix;
	dNewtonCollision::SetMatrix(&matrix[0][0]);
}

