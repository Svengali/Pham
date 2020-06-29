//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once



namespace ent
{
class Entity;
}

namespace com
{

template<typename TCFG>
class Component;

//This might be unnecessary
class ComponentConfig: public Config
{
public:
	CLASS( ComponentConfig, Config );


	REFLECT_BEGIN( ComponentConfig, Config );
	REFLECT_END();

};

// ???
PtrDef( ComponentConfig );

template< typename TCFG >
class Component : std::enable_shared_from_this<Component<TCFG>>
{

public:

	CLASS( Component );

	Component( ent::Entity * const pEnt, const std::shared_ptr<TCFG> &config )
		:
		m_pEntity( pEnt ),
		m_config( config )
	{
	}

	virtual ~Component()
	{
	}

	std::shared_ptr<const TCFG> cfg()
	{
		return m_config;
	}

	REFLECT_BEGIN_ROOT( Component );
		REFLECT( m_pEntity );
		REFLECT( m_config );
	REFLECT_END();

protected:
	ent::Entity *entity() const
	{
		return m_pEntity;
	}

private:
	//Wholly owned by this guy.  
	ent::Entity *m_pEntity;

	std::shared_ptr<TCFG> m_config;

};
}


