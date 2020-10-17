//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"


#if 0

#include ".\ComController.h"

SERIALIZABLE( ComControllerConfig );
SERIALIZABLE( ComController );

com::Component<ComControllerConfig>* ComControllerConfig::CreateCom(ent::Entity* const pEnt)
{
	return new ComController( pEnt, ComControllerConfigPtr( this ) );
}


ComController::ComController( ent::Entity * const pEnt, const ComControllerConfigPtr &config )
	:
	Component( pEnt, config )
{
}

ComController::~ComController()
{
}

#endif