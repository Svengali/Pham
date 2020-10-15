//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"



#include ".\ComPhysical.h"

namespace com
{

SERIALIZABLE( ComPhysicalConfig );
SERIALIZABLE( ComPhysical );

Component<ComPhysicalConfig> *ComPhysicalConfig::CreateCom( ent::Entity * const pEnt )
{
	return new ComPhysical( pEnt, new ComPhysicalConfigPtr( this ) );
}


ComPhysical::ComPhysical( ent::Entity * const pEnt, const ComPhysicalConfigPtr &config )
	:
	Component( pEnt ),
	m_frame( cb::Frame3::eIdentity )
{
}

ComPhysical::~ComPhysical()
{
}


}
