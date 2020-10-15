//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"



#include "./ComRenderable.h"

#include "../Renderer/Geometry.h"

SERIALIZABLE( ComRenderableConfig );
SERIALIZABLE( ComRenderable );

Component *ComRenderableConfig::CreateCom( Entity * const pEnt )
{
	return new ComRenderable( pEnt, ComRenderableConfigPtr( this ) );
}


ComRenderable::ComRenderable( Entity * const pEnt, const ComRenderableConfigPtr &config )
	:
	Component( pEnt ),
	m_config( config )
{
}

ComRenderable::~ComRenderable()
{
}

void ComRenderable::Render( const RenderContextPtr &rcon, const Frame3 &frame )
{
	m_config->m_geo->Render( rcon, frame );
}


