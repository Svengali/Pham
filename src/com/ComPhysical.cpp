//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include ".\ComPhysical.h"

namespace com
{

SERIALIZABLE( ComPhysicalConfig );
SERIALIZABLE( ComPhysical );

/*
Component<ComPhysicalConfig> *ComPhysicalConfig::CreateCom( ent::Entity * const pEnt )
{
	return new ComPhysical( pEnt, new ComPhysicalConfigPtr( this ) );
}
*/

ComPhysical::ComPhysical( ent::EntityBase * const pEnt, const ComPhysicalConfigPtr &config )
	:
	Component( pEnt, config ),
	m_frame( cb::Frame3::eIdentity )
{
}

ComPhysical::~ComPhysical()
{
}


}
