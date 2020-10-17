//////////////////////////////////////////////////////////////////////////////
//
//   S p a c e
//
// copyright 2005-2008 Marc Hernandez
#pragma once

#include "Geometry.h"

//#include <d3dx9mesh.h>

#if 0

SPtrFwd( ResXMesh );
SPtrFwd( RenderContext );

struct ID3DXEffect;
//struct D3DXEFFECTINSTANCE;

class GeoD3DDynamic : public Geometry
{

public:
	CLASS( GeoD3DDynamic, Geometry );
	
	GeoD3DDynamic();
	
	GeoD3DDynamic( const char * const pMesh );
	
	virtual ~GeoD3DDynamic();
	
	virtual void Render( const RenderContextPtr &rcon, const cb::Frame3 &frame );
	
	REFLECT_BEGIN( GeoD3DDynamic, Geometry );
	REFLECT_END();

private:
};


SPtrDef( GeoD3DDynamic );

#endif
