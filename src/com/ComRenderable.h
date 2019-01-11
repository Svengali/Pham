//////////////////////////////////////////////////////////////////////////////
//
//   S p a c e
//
// copyright 2005-2008 Marc Hernandez
#pragma once

#include "./Component.h"

#include "../Renderer/Geometry.h"

SPtrFwd( ComRenderableConfig );
SPtrFwd( RenderContext );

class ComRenderableConfig : public ComponentConfig
{
public:
	CLASS( ComRenderableConfig, ComponentConfig );

  REFLECT_BEGIN( ComRenderableConfig, ComponentConfig );
		REFLECT( m_geo );
  REFLECT_END();

	GeometryPtr m_geo;

	virtual Component *CreateCom( Entity * const pEnt );


};

class ComRenderable : public Component
{

public:

	CLASS( ComRenderable, Component );

	ComRenderable( Entity * const pEnt = NULL, const ComRenderableConfigPtr &config = ComRenderableConfigPtr( NULL ) );

	virtual ~ComRenderable();

	void Render( const RenderContextPtr &rcon, const Frame3 &frame );

  REFLECT_BEGIN( ComRenderable, Component );
		REFLECT( m_config );
  REFLECT_END();

private:
	ComRenderableConfigPtr m_config;

};


SPtrDef( ComRenderable );














// -