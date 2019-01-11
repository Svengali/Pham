//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

#include "./Component.h"

SPtrFwd( ComPhysicalConfig );

namespace com
{

//This might be unnecessary
class ComPhysicalConfig : public ComponentConfig
{
public:
	CLASS( ComPhysicalConfig, ComponentConfig );

  REFLECT_BEGIN( ComPhysicalConfig, ComponentConfig );
		REFLECT( m_AABB );
  REFLECT_END();

	cb::Vec3 m_AABB;

	virtual Component<ComPhysicalConfig> *CreateCom( ent::Entity * const pEnt );


};

class ComPhysical : public Component<ComPhysicalConfig>
{

public:

	CLASS( ComPhysical, Component );

	ComPhysical( ent::Entity * const pEnt = NULL, const ComPhysicalConfigPtr &config = ComPhysicalConfigPtr( NULL ) );

	virtual ~ComPhysical();

  REFLECT_BEGIN( ComPhysical, Component );
		REFLECT( m_config );
		REFLECT( m_frame );
  REFLECT_END();

	const cb::Frame3 &GetFrame() const
	{
		return m_frame;
	}

private:
	ComPhysicalConfigPtr m_config;

	cb::Frame3 m_frame;
	
};


SPtrDef( ComPhysical );

}
















// -