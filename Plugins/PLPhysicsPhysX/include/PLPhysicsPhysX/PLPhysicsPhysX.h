/*********************************************************\
 *  File: PLPhysicsPhysX.h                               *
 *      Main header file of this project
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the �Software�), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


/**
*  @mainpage PLPhysicsPhysX
*
*  @section intro_sec Introduction
*
*  This is the PLPhysicsPhysX reference.
*/


#ifndef __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
#define __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
#pragma once


//[-------------------------------------------------------]
//[ OS definitions                                        ]
//[-------------------------------------------------------]
// Windows platform
#ifdef WIN32
	#include "PLPhysicsPhysX/PLPhysicsPhysXWindows.h"
#endif

// Linux platform
#ifdef LINUX
	#include "PLPhysicsPhysX/PLPhysicsPhysXLinux.h"
#endif


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4100) // "'identifier' : unreferenced formal parameter"
	PL_WARNING_DISABLE(4244) // "'conversion' conversion from 'type1' to 'type2', possible loss of data"
	PL_WARNING_DISABLE(4512) // "'class' : assignment operator could not be generated"
	#include <NxPhysics.h>
PL_WARNING_POP


#endif // __PLPHYSICSPHYSX_PLPHYSICSPHYSX_H__
