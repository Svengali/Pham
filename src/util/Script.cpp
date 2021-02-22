//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"

#if 0

#include "./Script.h"

#include "../Resource/ResScript.h"

#include <angelscript.h>

Script *Script::s_curScript = NULL;


Script::~Script()
{
	m_pContext->Release();
}


void Script::Init( const char * const pFilename )
{
	m_script = ResourceMgr::GetResource<ResScript>( pFilename );
	
	m_pContext = m_script->GetContext();

	//ResScript::Engine()->Regi

	/*
	float val = m_pContext->GetReturnFloat();	
	
	gLog::Printf( "Value is %f\n", val );
	
	const float test1 = MakeFnCall<float>( "DoSomething" );
	
	const float test2 = MakeFnCall<float>( "DoSomething", 15 );

	const float test3 = MakeFnCall<float>( "DoSomething", &test2 );
	*/
	
		
	
}

template<>
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, float val )
{
	return pContext->SetArgFloat( whichArg, val );
};

template<>
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, double val )
{
	return pContext->SetArgDouble( whichArg, val );
};

template<>
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, int val )
{
	return pContext->SetArgDWord( whichArg, val );
};


void Script::MakeFnCall_raw( const RuntimeString &name, const RuntimeString &ret_type, const RuntimeString &args )
{
	char buf[ 4096 ];
	
	s_curScript = this;
	
	_snprintf( buf, 4096, "%s %s(%s)", ret_type.CStr(), name.CStr(), args.CStr() );

	const int functionID = m_script->GetFunctionIDByDecl( buf );
	
	if( functionID >= 0 )
	{
		m_pContext->Prepare( functionID );
		m_pContext->Execute();
	}
	else
	{
		cb::Log( "Error: Fn[%s] not found.\n", buf );
	}
		
	//m_pContext->Get
}

#endif
