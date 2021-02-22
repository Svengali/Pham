//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once


#include "./Component.h"

//#include "../Renderer/Geometry.h"

/*
PPtrFwd( ComHealthConfig );
PPtrFwd( RenderContext );
*/


namespace com
{

class ComHealthConfig : public ComponentConfig
{
public:
	CLASS( ComHealthConfig, ComponentConfig );

	virtual void DoReflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( ComHealthConfig, ComponentConfig );
		REFLECT( m_maxHealth );
	REFLECT_END();

	double m_maxHealth;

	//virtual Component *CreateCom( ent::Entity * const pEnt );


};

PtrDef( ComHealthConfig );

class ComHealth : public Component<ComHealthConfig>
{

public:

	CLASS( ComHealth, Component );

	ComHealth( ent::Entity * const pEnt = NULL, const ComHealthConfigPtr &config = ComHealthConfigPtr( NULL ) );

	virtual ~ComHealth();

  REFLECT_BEGIN( ComHealth, Component<ComHealthConfig> );
	  REFLECT( m_health );
  REFLECT_END();

private:
	double m_health;

};

PtrDef( ComHealth );

}

