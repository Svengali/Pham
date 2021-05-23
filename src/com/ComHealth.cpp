//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "./ComHealth.h"

	
namespace com
{
	SERIALIZABLE( ComHealthCfg );

	SERIALIZABLE( ComHealth );

/*
Component *ComHealthConfig::CreateCom( ent::Entity * const pEnt )
{
	return new ComHealth( pEnt, ComHealthConfigPtr( this ) );
}
*/

ComHealth::ComHealth( ent::EntityBase * const pEnt, const ComHealthCfgPtr &cfg )
	:
	Component( pEnt, cfg )
{
	m_health = cfg->m_maxHealth;
}

ComHealth::~ComHealth()
{
}



}
