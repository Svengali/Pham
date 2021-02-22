//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

#include "Resource.h"

#if 0 

SPtrFwd( ResXEffect );

struct ID3DXEffect;

class ResXEffect : public Resource
{
public:
	CLASS( ResXEffect, Resource );

	static ResourcePtr Create( const char * const pFilename, const Symbol &type );

	virtual ~ResXEffect();
	
	
	virtual void Load  ( const char * const pFilename );
	
	ID3DXEffect *GetD3DEffect() const
	{
		return m_pEffect;
	}

	REFLECT_BEGIN( ResXEffect, Resource );
		REFLECT( m_pEffect );
	REFLECT_END();
	
private:

	ID3DXEffect *m_pEffect;

};

#endif
