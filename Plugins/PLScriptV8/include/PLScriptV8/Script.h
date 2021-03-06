/*********************************************************\
 *  File: Script.h                                       *
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


#ifndef __PLSCRIPTV8_SCRIPT_H__
#define __PLSCRIPTV8_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4127) // "conditional expression is constant" (within "v8.h")
	#include <V8/v8.h>
PL_WARNING_POP
#include <PLCore/Script/Script.h>
#include "PLScriptV8/PLScriptV8.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptV8 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    V8 (ECMA-262 compliant JavaScript engine, see http://code.google.com/p/v8/) script implementation
*/
class Script : public PLCore::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class_def(PLSCRIPTV8_API)
	pl_class_def_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLSCRIPTV8_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTV8_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Script functions               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual bool IsGlobalFunction(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual bool AddGlobalFunction(const PLCore::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual bool RemoveAllGlobalFunctions() override;

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual PLCore::String GetSourceCode() const override;
		PLSCRIPTV8_API virtual bool SetSourceCode(const PLCore::String &sSourceCode) override;
		PLSCRIPTV8_API virtual void GetAssociatedFilenames(PLCore::Array<PLCore::String> &lstFilenames) override;
		PLSCRIPTV8_API virtual bool Execute(const PLCore::String &sSourceCode) override;

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual void GetGlobalVariables(PLCore::Array<PLCore::String> &lstGlobalVariables, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual bool IsGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual PLCore::String GetGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual void SetGlobalVariable(const PLCore::String &sName, const PLCore::DynVar &cValue, const PLCore::String &sNamespace = "") override;

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual bool BeginCall(const PLCore::String &sFunctionName, const PLCore::String &sFunctionSignature, const PLCore::String &sNamespace = "") override;
		PLSCRIPTV8_API virtual void PushArgument(bool bValue) override;
		PLSCRIPTV8_API virtual void PushArgument(float fValue) override;
		PLSCRIPTV8_API virtual void PushArgument(double fValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::int8 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::int16 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::int32 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::int64 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::uint8 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::uint16 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::uint32 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::uint64 nValue) override;
		PLSCRIPTV8_API virtual void PushArgument(const PLCore::String &sString) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::Object *pObject) override;
		PLSCRIPTV8_API virtual void PushArgument(PLCore::Object &cObject) override;
		PLSCRIPTV8_API virtual bool EndCall() override;
		PLSCRIPTV8_API virtual bool GetReturn(bool nValue) override;
		PLSCRIPTV8_API virtual float GetReturn(float nValue) override;
		PLSCRIPTV8_API virtual double GetReturn(double nValue) override;
		PLSCRIPTV8_API virtual PLCore::int8 GetReturn(PLCore::int8 nValue) override;
		PLSCRIPTV8_API virtual PLCore::int16 GetReturn(PLCore::int16 nValue) override;
		PLSCRIPTV8_API virtual PLCore::int32 GetReturn(PLCore::int32 nValue) override;
		PLSCRIPTV8_API virtual PLCore::int64 GetReturn(PLCore::int64 nValue) override;
		PLSCRIPTV8_API virtual PLCore::uint8 GetReturn(PLCore::uint8 nValue) override;
		PLSCRIPTV8_API virtual PLCore::uint16 GetReturn(PLCore::uint16 nValue) override;
		PLSCRIPTV8_API virtual PLCore::uint32 GetReturn(PLCore::uint32 nValue) override;
		PLSCRIPTV8_API virtual PLCore::uint64 GetReturn(PLCore::uint64 nValue) override;
		PLSCRIPTV8_API virtual PLCore::String GetReturn(PLCore::String nValue) override;
		PLSCRIPTV8_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue) override;
		PLSCRIPTV8_API virtual PLCore::Object &GetReturn(PLCore::Object &nValue) override;


	//[-------------------------------------------------------]
	//[ Private static V8 callback functions                  ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    V8 function callback
		*
		*  @param[in] vV8Arguments
		*    V8 arguments
		*
		*  @return
		*    V8 function result
		*/
		static v8::Handle<v8::Value> V8FunctionCallback(const v8::Arguments &vV8Arguments);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    A global function
		*/
		struct GlobalFunction {
			PLCore::String   sFunction;		/**< Function name used inside the script to call the global function */
			PLCore::DynFunc *pDynFunc;		/**< Dynamic function to be called, always valid, destroy when done */
			PLCore::String   sNamespace;	/**< Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on) */
		};

		/**
		*  @brief
		*    V8 namespace
		*/
		class V8Namespace {
			public:
				v8::Local<v8::ObjectTemplate>				  cV8ObjectTemplate;	/**< V8 object template representing this namespace */
				PLCore::HashMap<PLCore::String, V8Namespace > mapNamespaces;		/**< Map of nested namespaces */
				bool operator ==(const V8Namespace &cOther) { return false; }
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Script(const Script &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Script &operator =(const Script &cSource);

		/**
		*  @brief
		*    Clears the script
		*/
		void Clear();

		/**
		*  @brief
		*    Write a string into the log
		*
		*  @param[in] nLogLevel
		*    Log level
		*  @param[in] sText
		*    Text which should be written into the log
		*  @param[in] cTryCatch
		*    "v8::TryCatch" instance
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The text is written to the log only if the current
		*    log level is greater or equal to the specified value.
		*    This method is an extension of "PLCore::Log::Output()"
		*    which also adds the name of the script to the given
		*    text and the "v8::TryCatch" line and exception.
		*/
		bool LogOutputTryCatch(PLCore::uint8 nLogLevel, const PLCore::String &sText, const v8::TryCatch &cTryCatch);

		/**
		*  @brief
		*    Adds a V8 function
		*
		*  @param[in] cV8Namespace
		*    Current V8 namespace
		*  @param[in] sFunction
		*    Name of the function
		*  @param[in] cV8Function
		*    V8 function to add
		*  @param[in] sNamespace
		*    Namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on)
		*/
		void AddV8Function(V8Namespace &cV8Namespace, const PLCore::String &sFunction, v8::Local<v8::ObjectTemplate> cV8Function, const PLCore::String &sNamespace) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String							  m_sSourceCode;		/**< Script source code */
		v8::Persistent<v8::Context>				  m_cV8Context;			/**< V8 context */
		PLCore::String							  m_sCurrentFunction;	/**< Name of the current function */
		v8::Persistent<v8::Value>				  m_cV8CurrentResult;	/**< Current V8 function */
		PLCore::Array<v8::Persistent<v8::Value> > m_lstV8Arguments;		/**< Current V8 arguments */
		PLCore::Array<GlobalFunction*>			  m_lstGlobalFunctions;	/**< List of global functions */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8


#endif // __PLSCRIPTV8_SCRIPT_H__
