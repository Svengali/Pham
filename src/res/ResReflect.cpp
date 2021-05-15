//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "./ResReflect.h"

ResourcePtr ResReflect::create( const char * const pFilename, const util::Symbol &type )
{
	TiXmlDocument doc;

	doc.LoadFile( pFilename );
	
	const TiXmlElement * const pRoot = doc.RootElement();
	
	if( pRoot )
	{
		util::Symbol finalType = pRoot->Attribute( "type" ) ? util::Symbol( pRoot->Attribute( "type" ) ) : type;

		ResReflect * const pConfig = cast< ResReflect * >( Serialization::CreateClassFromTypeName_base( finalType ) );

		if( pConfig )
		{
			XMLReader reader( pFilename, pRoot );

			pConfig->DoReflection( reader );

			return ResourcePtr( pConfig );

			//return ResourcePtr( nullptr );
		}
	}
	else
	{
		// TODO LOG
	}
	
	return ResourcePtr( NULL );
}

void ResReflect::load( const char * const pFilename )
{
	TiXmlDocument doc;

	doc.LoadFile( pFilename );
	
	const TiXmlElement * const pRoot = doc.RootElement();
	
	if( pRoot )
	{
		util::Symbol finalType = pRoot->Attribute( "type" ) ? util::Symbol( pRoot->Attribute( "type" ) ) : Class();

		XMLReader reader( pFilename, pRoot );

		Reflection( reader );


	}
}
