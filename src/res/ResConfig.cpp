//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "stdafx.h"


#include ".\ResConfig.h"

//#include "../Core/XMLReader.h"

ResourcePtr ResConfig::Create( const char * const pFilename )
{
	TiXmlDocument doc;

	doc.LoadFile( pFilename );

	const TiXmlElement * const pElem = doc.RootElement();

	if( pElem != NULL )
	{
		const char * const pType = pElem->Attribute( "type" );
		
		if( pType )
		{
			ResConfig * const pResConfig = Serialization::CreateClassFromTypeName< ResConfig >( util::Symbol( pType ) );
			
			//pResConfig->SetFilename( pFilename );

			//XMLReader readXML( pElem );
			
			//pResConfig->

			
			return ResConfigPtr( pResConfig );
		}
		else
		{
			ASSERT( false && "Config file needs a type attribute" );
		}
	}
	else
	{
		ASSERT( false && "Could not load the doc" );
	}

	return ResourcePtr( NULL );
}



ResConfig::ResConfig( const char * const )
{
}

ResConfig::~ResConfig()
{
}


void ResConfig::Load( const TiXmlElement * const pElem )
{
	if( pElem != NULL )
	{
		//XMLReader readXML( pElem );
		
		
	}
}














// -