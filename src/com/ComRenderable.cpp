//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"



#include "./ComRenderable.h"

#include "../grx/Geometry.h"

namespace com
{


SERIALIZABLE( ComRenderableConfig );
SERIALIZABLE( ComRenderable );

/*
Component *ComRenderableConfig::CreateCom( ent::Entity * const pEnt )
{
	return new ComRenderable( pEnt, ComRenderableConfigPtr( this ) );
}
*/

ComRenderable::ComRenderable( ent::Entity * const pEnt, const ComRenderableConfigPtr &config )
	:
    Component(pEnt, config)
{
}

ComRenderable::~ComRenderable()
{
}

void ComRenderable::Render( const RenderContextPtr &rcon, const cb::Frame3 &frame )
{
	
	this->cfg()->m_geo->render(rcon, frame);
}


}