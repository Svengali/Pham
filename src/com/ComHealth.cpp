//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "./ComHealth.h"

	
namespace com
{
	SERIALIZABLE( ComHealthConfig );
	SERIALIZABLE( ComHealth );

/*
Component *ComHealthConfig::CreateCom( ent::Entity * const pEnt )
{
	return new ComHealth( pEnt, ComHealthConfigPtr( this ) );
}
*/

ComHealth::ComHealth( ent::Entity * const pEnt, const ComHealthConfigPtr &config )
	:
	Component( pEnt, config )
{
	m_health = config->m_maxHealth;
}

ComHealth::~ComHealth()
{
}



}
