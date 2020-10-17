//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

#include "Resource.h"

#if 0 

SPtrFwd( ResXTex );

struct IDirect3DTexture9;

class ResXTex : public Resource
{
public:
	CLASS( ResXTex, Resource );

	static ResourcePtr Create( const char * const pFilename, const Symbol &type );

	virtual ~ResXTex();
	
	
	virtual void Load  ( const char * const pFilename );
	
	IDirect3DTexture9 *GetD3DTexture() const
	{
		return m_pMeshTexture;
	}

private:

	IDirect3DTexture9 *m_pMeshTexture;

};

#endif
