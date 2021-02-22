//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

namespace ent
{

class EntityId
{
public:

    const static EntityId invalid;

    EntityId()
        :
        m_id( invalid.m_id )
    {
    }

    EntityId( const EntityId &id )
        :
        m_id( id.m_id )
    {
    }

    static EntityId initStartingEntityId( const uint64_t raw )
    {
        return s_nextId = EntityId( raw );
    }

    static EntityId makeNext()
    {
        const EntityId next = s_nextId;
        s_nextId = next.next();
        return next;
    }

	const EntityId next() const
	{
		return EntityId( m_id + 1 );
	}

    bool operator <(const EntityId rhs) const
    {
        return m_id < rhs.m_id;
    }

    // MH TODO Use a specialization of getting the hash value rather than making an implicit conversion functions
    operator size_t() const
    {
        return m_id;
    }


private:

    EntityId( const uint64_t id )
        :
        m_id( id )
    {
    }

    static EntityId s_nextId;

    uint64_t m_id;
};

}