// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Newton.h>
#include <dMathDefines.h>
#include <dVector.h>
#include <dMatrix.h>
#include <dQuaternion.h>
#include <dLinearAlgebra.h>

#include <dContainersAlloc.h>
#include <dList.h>
#include <dTree.h>

#include <dCustomJointLibraryStdAfx.h>
#include <dCustomAlloc.h>
#include <dCustomJoint.h>
#include <dCustomBallAndSocket.h>
#include <dCustomGear.h>
#include <dCustomPlane.h>
#include <dCustomHinge.h>
#include <dCustomSlider.h>
#include <dCustomDoubleHinge.h>
#include <dCustomHingeActuator.h>
#include <dCustomSlidingContact.h>
#include <dCustomSliderActuator.h>
#include <dCustomDoubleHingeActuator.h>
#include <dCustomVehicleControllerManager.h>

#define RAD_TO_DEGREES	(180.0f / 3.141592f)
#define DEGREES_TO_RAD	(3.141592f / 180.0f)


