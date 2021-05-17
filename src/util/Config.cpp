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

	const bool loadRes = doc.LoadFile( pFilename );

	if( loadRes )
	{
		const TiXmlElement *const pRoot = doc.RootElement();

		if( pRoot )
		{
			util::Symbol finalType = pRoot->Attribute( "type" ) ? util::Symbol( pRoot->Attribute( "type" ) ) : type;

			Config *const pConfig = cast< Config * >( Serialization::CreateClassFromTypeName_base( finalType ) );

			if( pConfig )
			{
				XMLReader reader( pFilename, pRoot );

				pConfig->DoReflection( reader );

				return ResourcePtr( pConfig );
			}
			else
			{
				lprintf( "%s: Failure creating %s. Could not create class\n", pFilename, type.GetString() );
			}
		}
		else
		{
			lprintf( "%s: Failure finding root document\n", pFilename, type.GetString() );
		}
	}
	else
	{
		lprintf( "%s: Loading failed. Got %s\n", pFilename, doc.ErrorDesc() );
	}

	lprintf( "%s: Returning nullptr of %s\n", pFilename, type.GetString() );
	Config *const pConfig = nullptr; //cast< Config * >( Serialization::CreateClassFromTypeName_base( type ) );
	return ResourcePtr( pConfig );
	
}

void Config::load( const char * const pFilename )
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
