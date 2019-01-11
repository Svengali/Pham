//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

#include "Resource.h"


class asIScriptEngine;
class asIScriptContext;

class ResScript : public Resource
{
public:

	static void CreateEngine();
	static asIScriptEngine *Engine();

	CLASS( ResScript, Resource );

	static ResourcePtr Create( const char * const pFilename, const util::Symbol &type );

	asIScriptEngine *GetEngine();
	asIScriptContext *GetContext();
	
	int GetFunctionIDByDecl( const char * const pFn ) const;
	
	virtual void Load  ( const char * const pFilename );
	
	//PROC_MEMBERS();
	
protected:

	/*
	template< typename TProc >
	void SubProcess( TProc * const pProc )
	{
		Resource::SubProcess( pProc );
	}
	*/

private:
	RuntimeString m_module;

};

SPtrDef( ResScript );
















// -