/*********************************************************\
 *  File: Application.cpp                                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "MyClass.h"
#include <PLCore/Typebase/Tuple.h>

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLRefl;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_begin_class(MyClass)
	pl_class_method(Foo)
//.Method("Foo", PLCore::Function<decltype(&_Clss::Foo)>(nullptr, &_Clss::Foo))
pl_end_class()

template <typename Func>
struct S
{
	S(Func _f) : f(_f) {}
	Func f;

	template <typename... Args>
	void Exec(Args... args)
	{
		f(args...);
	}
};

class B
{
public:
	virtual void f(int, float)
	{}
};

class D : public B
{
public:
	virtual void f(int ii, float ff) override
	{
		ii=ii;
	}
};

//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MyClass::MyClass()
{
	D inst;
	PLCore::Function<decltype(&B::f)> d(&inst, &B::f);
	d(1, 2.0f);

	//auto l = [this](int i, float f) {};
	//S<decltype(l)> s(l);
	//s.Exec(1, 1.0f);
	//PLCore::Function<decltype(l)> dl;

	PLCore::Tuple<int, float> t;
	int& i = PLCore::TupleGet<0>(t) = 2;
	float& f = PLCore::TupleGet<1>(t) = 2.0f;
	i = 108;
	f = 1.08f;

	d(t);
}

/**
*  @brief
*    Destructor
*/
MyClass::~MyClass()
{
}

/**
*  @brief
*    Dummy function
*/
int MyClass::Foo(int i, float f)
{
	return 0;
}