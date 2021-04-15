//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "./Config.h"

ResourcePtr Config::create( const char * const pFilename, const util::Symbol &type )
{
	TiXmlDocument doc;

	doc.LoadFile( pFilename );
	
	const TiXmlElement * const pRoot = doc.RootElement();
	
	if( pRoot )
	{
		util::Symbol finalType = pRoot->Attribute( "type" ) ? util::Symbol( pRoot->Attribute( "type" ) ) : type;

		Config * const pConfig = cast< Config * >( Serialization::CreateClassFromTypeName_base( finalType ) );

		if( pConfig )
		{
			/* PORT: Fix when we get XML reader up and running */
			XMLReader reader( pRoot );

			pConfig->DoReflection( reader );

			return ResourcePtr( pConfig );

			//return ResourcePtr( nullptr );
		}
	}
	
	return ResourcePtr( NULL );
}

void Config::load( const char * const pFilename )
{
	TiXmlDocument doc;

	doc.LoadFile( pFilename );
	
	const TiXmlElement * const pRoot = doc.RootElement();
	
	if( pRoot )
	{
		util::Symbol finalType = pRoot->Attribute( "type" ) ? util::Symbol( pRoot->Attribute( "type" ) ) : Class();

		XMLReader reader( pRoot );

		Reflection( reader );


	}
}
