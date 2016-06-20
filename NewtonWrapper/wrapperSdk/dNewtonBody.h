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

#ifndef _D_NEWTON_BODY_H_
#define _D_NEWTON_BODY_H_

#include "stdafx.h"
#include "dAlloc.h"

class dMatrix;
class NewtonBody;
class dNewtonWorld;
class dNewtonCollision;


class dNewtonBody: public dAlloc
{
	public:

	class ScopeLock
	{
		public:
		ScopeLock(unsigned int* const lock);
		~ScopeLock();
		unsigned* m_atomicLock;
	};

	dNewtonBody(const dMatrix* const matrix);
	virtual void Destroy();
	void* GetPosition();
	void* GetRotation();

	virtual void AddForceAndTorque(dFloat* const force, dFloat* const torque);
	

	protected:
	virtual ~dNewtonBody();

	// called from newton update
	virtual void OnForceAndTorque(dFloat timestep, int threadIndex);

	// call each time the physics update the body transformation 
	virtual void OnBodyTransform(const dFloat* const matrix, int threadIndex);

	virtual void InitForceAccumulators();

/*
	dBodyType GetType() const {return m_bodyType;}
	bool GetSleepState() const;
	void SetSleepState(bool state) const;
	bool GetAutoSleepMode() const;
	void SetAutoSleepMode(bool mode);
	void SetMatrix (const dFloat* const matrix);
	void GetMatrix (dFloat* const matrix) const;
	void GetVisualMatrix (dFloat param, dFloat* const matrix) const;
	void SetVeloc (const dFloat* const veloc);
	void GetVeloc (dFloat* const veloc) const;
	void SetOmega (const dFloat* const omega);
	void GetOmega (dFloat* const omega) const;
	void SetForce (const dFloat* const force);
	void AddForce (const dFloat* const force);
	//void GetForce (dFloat* const force) const;
	void SetTorque (const dFloat* const torque);
	void AddTorque (const dFloat* const torque);
	//void GetTorque (dFloat* const torque) const;
	dFloat GetLinearDrag () const;
	void SetLinearDrag (const dFloat drag);
	void GetAngularDrag (dFloat* const drag) const;
	void SetAngularDrag (const dFloat* const drag);
//	void  NewtonBodySetLinearDamping (const NewtonBody* const body, dFloat linearDamp);
//	void  NewtonBodySetAngularDamping (const NewtonBody* const body, const dFloat* const angularDamp);
	void GetCenterOfMass (dFloat* const com) const;
	void SetCenterOfMass (const dFloat* const com);
    void SetMassAndInertia (dFloat mass, dFloat Ixx, dFloat Iyy, dFloat Izz);
	void SetMassAndInertia (dFloat mass, const dNewtonCollision* const collision);
	void GetMassAndInertia (dFloat& mass, dFloat& Ixx, dFloat& Iyy, dFloat& Izz) const;
	void SetCCDMode (bool mode);
	bool GetCCDMode () const;
	// applications can overload this to update game object information each time there transformation changes 
	virtual void OnApplicationPostTransform (dFloat timestep) {};


	virtual void OnContactProcess (dNewtonContactMaterial* const contactMaterial, dFloat timestep, int threadIndex) const {}

	void* GetUserData() const;
	void SetUserData(void* const userData);
	
	dNewtonBody* GetParent() const;
	dNewtonBody* GetChild() const;
	dNewtonBody* GetSibling() const;
	void AttachChild (dNewtonBody* const child);

	void* GetBoneArticulation() const;
	void SetBoneArticulation(void* const boneArticulation);
	
	dNewton* GetNewton () const;

	NewtonBody* GetNewtonBody () const;
	dNewtonCollision* GetCollision() const;
	void SetCollision(const dNewtonCollision* const collision) const;

	protected:
	dNewtonBody(dBodyType type, dNewtonBody* const parent);
	virtual void SetBody  (NewtonBody* const body);
*/
	protected:



	static void OnBodyDestroy (const NewtonBody* const body);
	static void OnForceAndTorqueCallback (const NewtonBody* body, dFloat timestep, int threadIndex);
	static void OnBodyTransformCallback(const NewtonBody* const body, const dFloat* const matrix, int threadIndex);

	
	NewtonBody* m_body;

	dVector m_posit0;
	dVector m_posit1;
	dVector m_interpolatedPosit;
	dQuaternion m_rotation0;
	dQuaternion m_rotation1;
	dQuaternion m_interpolatedRotation;
	unsigned m_lock;

	friend class dNewtonWorld;
};

class dNewtonDynamicBody: public dNewtonBody
{
	public:
	dNewtonDynamicBody(dNewtonWorld* const world, dNewtonCollision* const collision, const void* const matrixPtr, dFloat mass);

	private:
	virtual void OnForceAndTorque(dFloat timestep, int threadIndex);
	virtual void InitForceAccumulators();
//	OnApplyForceAndTorqueCallback m_forceCallback;

	virtual void AddForceAndTorque(dFloat* const force, dFloat* const torque);

	dVector m_externalForce;
	dVector m_externalTorque;
};

#endif
