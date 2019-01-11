//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "stdafx.h"



#include "Serialization.h"

#include <hash_map>


typedef stdext::hash_map< util::Symbol, FnNewClassByName > MapTokenFnNew;
typedef stdext::hash_map< util::Symbol, FnPlacementNewClassByName > MapTokenFnPlacementNew;

//For safety.  You can guarantee that this map will be constructred before any of the create fns are called.
//Thus we Meyers Singleton the map.
MapTokenFnNew &GetNew()
{
	static MapTokenFnNew s_createFns;
	
	return s_createFns;
}

MapTokenFnPlacementNew &GetPlacementNew()
{
	static MapTokenFnPlacementNew s_createFns;
	
	return s_createFns;
}

void Serialization::RegNew( const util::Symbol &sym, FnNewClassByName fnCreate )
{
	GetNew()[ sym ] = fnCreate;
}

void Serialization::RegPlacementNew( const util::Symbol &sym, FnPlacementNewClassByName fnCreate )
{
	GetPlacementNew()[ sym ] = fnCreate;
}

void *Serialization::CreateClassFromTypeName_base( const util::Symbol &sym )
{
	MapTokenFnNew::iterator it = GetNew().find( sym );
	
	if( it != GetNew().end() )
	{
		return it->second();
	}
	else
	{
		ASSERT( false );
		
		return NULL;
	}
}

void *Serialization::CreateClassFromTypeName_base( const util::Symbol &sym, char *buffer )
{
	MapTokenFnPlacementNew::iterator it = GetPlacementNew().find( sym );
	
	if( it != GetPlacementNew().end() )
	{
		return it->second( buffer );
	}
	else
	{
		ASSERT( false );
		
		return NULL;
	}
}
