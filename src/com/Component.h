//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once



namespace ent
{
class EntityBase;
}

namespace com
{

class ComponentBase;

//This might be unnecessary
class ComponentCfg: public Config
{
public:
	CLASS( ComponentCfg, Config );

	ComponentCfg() {}

	//virtual void Reflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( ComponentCfg, Config );
	REFLECT_END();

};


PtrDef( ComponentCfg );



class ComponentBase : std::enable_shared_from_this<ComponentBase>
{

public:

	CLASS( ComponentBase );

	ComponentBase() {}

	ComponentBase( ent::EntityBase *const pEnt, const ComponentCfgPtr &cfg )
		:
		m_pEntity( pEnt ),
		m_cfg( cfg )
	{
	}

	virtual ~ComponentBase()
	{
	}

	ComponentCfgPtr cfg()
	{
		return m_cfg;
	}

	REFLECT_BEGIN_ROOT( Component );
		REFLECT( m_pEntity );
		REFLECT( m_cfg );
	REFLECT_END();

protected:
	ent::EntityBase *entity() const
	{
		return m_pEntity;
	}

private:
	//Wholly owned by this guy.  
	ent::EntityBase *m_pEntity;

	ComponentCfgPtr m_cfg;

};


PtrDef( ComponentBase );

template< typename TCFG >
class Component: public ComponentBase
{

public:

	CLASS( Component );

	Component() {}

	Component( ent::EntityBase * const pEnt, const std::shared_ptr<TCFG> &config )
		:
		ComponentBase( pEnt, config )
	{
	}

	virtual ~Component()
	{
	}

	std::shared_ptr<const TCFG> cfg()
	{
		return ComponentBase::cfg();
	}

	REFLECT_BEGIN( Component, ComponentBase );
	REFLECT_END();


private:
};
}


