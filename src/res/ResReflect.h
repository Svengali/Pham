//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once


#include "../res/Resource.h"

#include "../util/XMLReader.h"

class ResReflect : public Resource//, public Root_XMLReader
{
public:
	CLASS( ResReflect, Resource );


	virtual void DoReflection( XMLReader &reader ) = 0;
	REFLECT_BEGIN( ResReflect, Resource );
	REFLECT_END();


	static ResourcePtr create( const char * const pFilename, const util::Symbol &type );

	virtual void load( const char * const pFilename );


};









// -