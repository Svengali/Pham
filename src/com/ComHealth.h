//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once


#include "./Component.h"

//#include "../Renderer/Geometry.h"

/*
PPtrFwd( ComHealthConfig );
PPtrFwd( RenderContext );
*/


namespace com
{

class ComHealthCfg : public ComponentCfg
{
public:
	CLASS( ComHealthCfg, ComponentCfg );

	ComHealthCfg() {}

	virtual void DoReflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( ComHealthCfg, ComponentCfg );
		REFLECT( m_maxHealth );
	REFLECT_END();

	double m_maxHealth;

	//virtual Component *CreateCom( ent::Entity * const pEnt );


};

PtrDef( ComHealthCfg );

class ComHealth : public Component<ComHealthCfg>
{

public:

	CLASS( ComHealth, Component );

	using Component::Component;

	ComHealth() {}

	ComHealth( ent::EntityBase *const pEnt, const ComHealthCfgPtr &cfg );

	virtual ~ComHealth();

  REFLECT_BEGIN( ComHealth, Component<ComHealthCfg> );
	  REFLECT( m_health );
  REFLECT_END();

private:
	double m_health;

};

PtrDef( ComHealth );

}

