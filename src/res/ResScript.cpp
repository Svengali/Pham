//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"


#include ".\ResScript.h"

#include <angelscript.h>

static asIScriptEngine *s_pEngine = NULL;
static int s_instance_count = 0;

void ResScript::CreateEngine()
{
	s_pEngine = asCreateScriptEngine( ANGELSCRIPT_VERSION );
}

asIScriptEngine *ResScript::Engine()
{
	return s_pEngine;
}


ResourcePtr ResScript::Create( const char * const pFilename, const Symbol &type )
{
	ResScriptPtr script( new ResScript() );
	
	char buf[256];
	
	_snprintf( buf, 256, "%s|%i", pFilename, s_instance_count );
	
	script->Load( pFilename );

	++s_instance_count;

	return script;
}


class ErrorOutput : public asIOutputStream
{
public:
	virtual void Write(const char *text)
	{
		cb::Log( "Script Error: [%s]\n", text );
	};

};

void ResScript::Load( const char * const pFilename )
{
	int r;

	m_module = pFilename;

	char buf[256];
	
	strcpy( buf, pFilename );
	
	size_t endOfString = strlen( buf );
	
	while( endOfString > 0 )
	{
		if( buf[endOfString] == '|' )
		{
			buf[endOfString] = 0;
			
			endOfString = 0;
		}
		
		
		--endOfString;
	}
	
	

	// We will load the script from a file on the disk.
	FILE * const f = fopen( pFilename, "rb");
	if( f == NULL )
	{
		//Log::Error( "Failed to open the script file [%s].\n", pFilename );
		return;
	}

	// Determine the size of the file	
	fseek(f, 0, SEEK_END);
	const int len = ftell(f);
	fseek(f, 0, SEEK_SET);

	// On Win32 it is possible to do the following instead
	// int len = _filelength(_fileno(f));

	// Read the entire file
	std::string str( len + 2, ' ' );
	
	size_t c =	fread((void *)str.c_str(), len, 1, f);
	fclose(f);

	if( c == 0 ) 
	{
		//gLog::Error( "Failed to load the script file [%s].\n", pFilename );
		return;
	}

	// Add the script sections that will be compiled into executable code.
	// If we want to combine more than one file into the same script, then 
	// we can call AddScriptSection() several times for the same module and
	// the script engine will treat them all as if they were one. The script
	// section name, will allow us to localize any errors in the script code.
	r = s_pEngine->AddScriptSection( m_module.CStr(), "script", str.c_str(), len, 0, false);
	if( r < 0 ) 
	{
		//gLog::Error( "AddScriptSection failed on script file [%s].\n", pFilename );
		return;
	}
	
	ErrorOutput err;
	
	s_pEngine->SetCommonMessageStream( &err );
	
	// Compile the script. If there are any compiler messages they will
	// be written to the message stream that we set right after creating the 
	// script engine. If there are no errors, and no warnings, nothing will
	// be written to the stream.
	r = s_pEngine->Build( m_module.CStr() );
	if( r < 0 )
	{
		//gLog::Error( "Build failed on script file [%s].\n", pFilename );
		return;
	}

	// The engine doesn't keep a copy of the script sections after Build() has
	// returned. So if the script needs to be recompiled, then all the script
	// sections must be added again.

	// If we want to have several scripts executing at different times but 
	// that have no direct relation with each other, then we can compile them
	// into separate script modules. Each module use their own namespace and 
	// scope, so function names, and global variables will not conflict with
	// each other.
}

asIScriptEngine *ResScript::GetEngine()
{
	return s_pEngine;
}


asIScriptContext *ResScript::GetContext()
{
	return s_pEngine->CreateContext();
}


int ResScript::GetFunctionIDByDecl( const char * const pFn ) const
{
	return s_pEngine->GetFunctionIDByDecl( m_module.CStr(), pFn );
}











// -