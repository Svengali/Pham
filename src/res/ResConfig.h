//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

#include "Resource.h"


class TiXmlElement;

class ResConfig : public Resource
{
public:
	static ResourcePtr Create( const char * const pFilename );

	ResConfig( const char * const pFilename );
	virtual ~ResConfig();
	
	
	//virtual void Load( const char * const pFilename );
	virtual void Load( const TiXmlElement * const pElem );

	//PROC_ABSTRACT_MEMBERS();
	
protected:

	template< typename TProc >
	void SubProcess( TProc * const pProc )
	{
		Resource::SubProcess( pProc );
		
		//PROC( m_pMeshTexture );
	}
	
private:
	//TiXmlDocument m_doc;

};


PtrDef( ResConfig );
















// -