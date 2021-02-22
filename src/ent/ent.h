//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

#include "../com/Component.h"


namespace ent
{

/*
class ComConfig: public Config
{
public:
	CLASS( ComConfig, Config );

	REFLECT_BEGIN( ComConfig, Config );
	REFLECT_END();

};
*/

class EntityConfig: public Config
{
public:
	CLASS( EntityConfig, Config );

	virtual void DoReflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( EntityConfig, Config );
		REFLECT( m_coms );
	REFLECT_END();

	std::vector< com::ComponentConfigPtr > m_coms;
};

PtrDef( EntityConfig );

class Entity
{

public:
	CLASS( Entity );

protected:
	Entity( const EntityId id, const EntityConfigPtr &cfg )
        :
        m_id( id ),
		m_config( cfg )
    {

    }


    EntityId id() const { return m_id; }


	REFLECT_BEGIN_ROOT( Entity );
		REFLECT( m_id );
		REFLECT( m_config );
	REFLECT_END();



protected:
    EntityId m_id;
	EntityConfigPtr m_config;


};

PtrDef( Entity );




template< typename TCFG >
class EntityWithConfig: public Entity
{

public:
	CLASS( EntityWithConfig );

	EntityId id() const { return m_id; }

	const std::shared_ptr<TCFG> &cfg() const
	{
		return std::static_pointer_cast<std::shared_ptr<TCFG>>( m_config );
	}

protected:
	EntityWithConfig( const EntityId id, const std::shared_ptr<TCFG> &cfg )
		:
		Entity( id, shared_cast<EntityConfig>( cfg ) )
	{

	}


	REFLECT_BEGIN( EntityWithConfig, Entity );
	REFLECT_END();



private:
};



}


