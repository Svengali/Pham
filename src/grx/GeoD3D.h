
//////////////////////////////////////////////////////////////////////////////
//
//   S p a c e
//
// copyright 2005-2008 Marc Hernandez
#pragma once

#include "Geometry.h"

#include <d3dx9mesh.h>

SPtrFwd( ResXMesh );
SPtrFwd( RenderContext );

struct ID3DXEffect;
//struct D3DXEFFECTINSTANCE;

class GeoD3D : public Geometry
{

public:
	CLASS( Geometry, GeoD3D );
	
	GeoD3D();
	
	GeoD3D( const char * const pMesh );
	
	virtual ~GeoD3D();
	
	virtual void Render( const RenderContextPtr &rcon, const Frame3 &frame );
	
	REFLECT_BEGIN( GeoD3D, Geometry );
		REFLECT( m_mesh );
	REFLECT_END();

private:
	
	void SetEffectDefaults( ID3DXEffect * const pEffect, const D3DXEFFECTINSTANCE &effectInst );
	
	ResXMeshPtr m_mesh;
};


SPtrDef( GeoD3D );














// -