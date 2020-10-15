//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"



#include ".\ComController.h"

SERIALIZABLE( ComControllerConfig );
SERIALIZABLE( ComController );

Component *ComControllerConfig::CreateCom( Entity * const pEnt )
{
	return new ComController( pEnt, ComControllerConfigPtr( this ) );
}


ComController::ComController( Entity * const pEnt, const ComControllerConfigPtr &config )
	:
	Component( pEnt )
{
}

ComController::~ComController()
{
}


