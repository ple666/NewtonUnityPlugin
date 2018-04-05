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
#include "dNewtonJointUniversal.h"

dNewtonJointUniversal::dNewtonJointUniversal(const dMatrix pintAndPivotMatrix, void* const body0, void* const body1)
	:dNewtonJoint()
{
	dMatrix bodyMatrix;

	NewtonBody* const netwonBody0 = (NewtonBody*)body0;
	NewtonBody* const netwonBody1 = (NewtonBody*)body1;
	NewtonBodyGetMatrix(netwonBody0, &bodyMatrix[0][0]);

	dMatrix matrix(pintAndPivotMatrix * bodyMatrix);
	dCustomUniversal* const joint = new dCustomUniversal(matrix, netwonBody0, netwonBody1);
	SetJoint(joint);
}

void dNewtonJointUniversal::SetLimits_0(bool enable, dFloat minVal, dFloat maxAngle)
{
	dCustomUniversal* const joint = (dCustomUniversal*)m_joint;
	joint->EnableLimit_0(enable);
	if (enable) {
		joint->SetLimits_0(dMin(minVal * DEGREES_TO_RAD, 0.0f), dMax(maxAngle * DEGREES_TO_RAD, 0.0f));
	}
}

void dNewtonJointUniversal::SetLimits_1(bool enable, dFloat minVal, dFloat maxAngle)
{
	dCustomUniversal* const joint = (dCustomUniversal*)m_joint;
	joint->EnableLimit_1(enable);
	if (enable) {
		joint->SetLimits_1(dMin(minVal * DEGREES_TO_RAD, 0.0f), dMax(maxAngle * DEGREES_TO_RAD, 0.0f));
	}
}


dNewtonJointUniversalActuator::dNewtonJointUniversalActuator(const dMatrix pintAndPivotMatrix, void* const body0, void* const body1)
	:dNewtonJoint()
{
	dMatrix bodyMatrix;
	NewtonBody* const netwonBody0 = (NewtonBody*)body0;
	NewtonBody* const netwonBody1 = (NewtonBody*)body1;
	NewtonBodyGetMatrix(netwonBody0, &bodyMatrix[0][0]);

	dMatrix matrix(pintAndPivotMatrix * bodyMatrix);
	dCustomUniversalActuator* const joint = new dCustomUniversalActuator(matrix, netwonBody0, netwonBody1);
	SetJoint(joint);
	joint->SetEnableFlag0(true);
	joint->SetEnableFlag1(true);
}

dFloat dNewtonJointUniversalActuator::GetAngle0() const
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*) m_joint;
	return joint->GetJointAngle_0() * RAD_TO_DEGREES;
}

void dNewtonJointUniversalActuator::SetMaxToque0(dFloat torque)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*) m_joint;
	joint->SetMaxTorquePower0(dAbs(torque));
}

void dNewtonJointUniversalActuator::SetAngularRate0(dFloat rate)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*) m_joint;
	joint->SetAngularRate0(rate * DEGREES_TO_RAD);
}

void dNewtonJointUniversalActuator::SetTargetAngle0(dFloat angle, dFloat minLimit, dFloat maxLimit)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*) m_joint;
	//joint->SetMinAngularLimit0(dMin(minLimit * DEGREES_TO_RAD, dFloat(0.0f)));
	//joint->SetMaxAngularLimit0(dMax(maxLimit * DEGREES_TO_RAD, dFloat(0.0f)));
	joint->SetLimits_0(dMin(minLimit * DEGREES_TO_RAD, dFloat(0.0f)), dMax(maxLimit * DEGREES_TO_RAD, dFloat(0.0f)));
	joint->SetTargetAngle0(dClamp (angle * DEGREES_TO_RAD, joint->GetMinAngularLimit_0(), joint->GetMaxAngularLimit_0()));
}


dFloat dNewtonJointUniversalActuator::GetAngle1() const
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*)m_joint;
	return joint->GetJointAngle_1() * RAD_TO_DEGREES;
}

void dNewtonJointUniversalActuator::SetMaxToque1(dFloat torque)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*)m_joint;
	joint->SetMaxTorquePower1(dAbs(torque));
}

void dNewtonJointUniversalActuator::SetAngularRate1(dFloat rate)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*)m_joint;
	joint->SetAngularRate1(rate * DEGREES_TO_RAD);
}

void dNewtonJointUniversalActuator::SetTargetAngle1(dFloat angle, dFloat minLimit, dFloat maxLimit)
{
	dCustomUniversalActuator* const joint = (dCustomUniversalActuator*)m_joint;
	joint->SetLimits_1(dMin(minLimit * DEGREES_TO_RAD, dFloat(0.0f)), dMax(maxLimit * DEGREES_TO_RAD, dFloat(0.0f)));
	joint->SetTargetAngle1(dClamp(angle * DEGREES_TO_RAD, joint->GetMinAngularLimit_1(), joint->GetMaxAngularLimit_1()));
}
