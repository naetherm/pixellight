/*********************************************************\
 *  File: FibonacciHeapTest.cpp                          *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLCore/Container/FibonacciHeap.h>
#include "PLTestBase/General/FibonacciHeapTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *FibonacciHeapTest::GetName() const
{
	return "Fibonacci heap";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void FibonacciHeapTest::Test()
{
	bool bResult;

	// Perform general tests
	FibonacciHeap<int, String> heapFibonacciHeap;
	bResult = HeapTestCase::Test(heapFibonacciHeap);

	// IsNormalized()
	StartTask("IsNormalized()");
	// Add some elements...
	heapFibonacciHeap.Clear();
	heapFibonacciHeap.Add(5, "Fifth");
	heapFibonacciHeap.Add(2, "Second");
	heapFibonacciHeap.Add(1, "First");
	// The heap should not be normalized (in fact, the heap should be a stupid double linked list :)
	bResult = true;
	if (heapFibonacciHeap.IsNormalized()) bResult = false;
	// Consolidate (cleanup)
	if (!heapFibonacciHeap.Consolidate()) bResult = false;
	// NOW the heap should be normalized!
	if (!heapFibonacciHeap.IsNormalized()) bResult = false;
	EndTask(bResult);
}
