//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
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

		std::vector< com::ComponentCfgPtr > m_coms;
	};

	PtrDef( EntityConfig );

	class EntityBase
	{

	public:
		CLASS( EntityBase );

	protected:
		EntityBase( const EntityId id, const EntityConfigPtr &cfg )
			:
			m_id( id ),
			m_config( cfg )
		{

		}


		EntityId id() const { return m_id; }


		REFLECT_BEGIN_ROOT( EntityBase );
			REFLECT( m_id );
			REFLECT( m_config );
		REFLECT_END();


	protected:
		EntityId m_id;
		EntityConfigPtr m_config;


	};

	PtrDef( EntityBase );




	template< typename TCFG >
	class Entity: public EntityBase
	{

	public:
		CLASS( EntityWithConfig );

		EntityId id() const { return m_id; }

		const std::shared_ptr<TCFG> &cfg() const
		{
			return std::static_pointer_cast<std::shared_ptr<TCFG>>( m_config );
		}

	protected:
		Entity( const EntityId id, const std::shared_ptr<TCFG> &cfg )
			:
			EntityBase( id, shared_cast<EntityConfig>( cfg ) )
		{

		}


		REFLECT_BEGIN( Entity, EntityBase );
		REFLECT_END();



	private:
	};



}


