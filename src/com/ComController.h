//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

#include "./Component.h"

#if 0

SPtrFwd( ComController );
SPtrFwd( ComControllerConfig );
SPtrFwd( ComConPlayerConfig );


//This might be unnecessary
class ComControllerConfig : public com::ComponentConfig
{
public:
	CLASS( ComControllerConfig, ComponentConfig );

  REFLECT_BEGIN( ComControllerConfig, ComponentConfig );
  REFLECT_END();

	virtual com::Component<ComControllerConfig> *CreateCom( ent::Entity * const pEnt );
};

class ComController : public com::Component<ComControllerConfig>
{
public:

	CLASS( ComController, Component );

	ComController(ent::Entity* const pEnt = NULL, const ComControllerConfigPtr& config = ComControllerConfigPtr(NULL));

	virtual ~ComController();

  REFLECT_BEGIN( ComController, Component );
		REFLECT( m_config );
  REFLECT_END();

private:
	ComControllerConfigPtr m_config;
};

//Player controller
class ComConPlayerConfig : public ComControllerConfig
{
public:
	CLASS( ComConPlayerConfig, ComControllerConfig );

  REFLECT_BEGIN( ComConPlayerConfig, ComControllerConfig );
  REFLECT_END();

	virtual com::Component<ComControllerConfig>* CreateCom(ent::Entity* const pEnt);
};

class ComConPlayer : public ComController
{
public:

	CLASS( ComConPlayer, ComController );

	ComConPlayer(ent::Entity* const pEnt = NULL, const ComConPlayerConfigPtr& config = ComConPlayerConfigPtr(NULL));

	virtual ~ComConPlayer();

  REFLECT_BEGIN( ComConPlayer, ComController );
		REFLECT( m_config );
  REFLECT_END();

private:
	ComConPlayerConfigPtr m_config;
};

#endif