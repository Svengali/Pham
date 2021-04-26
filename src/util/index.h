//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once














template< typename TIndex, typename TBase = int32_t >
class Index
{
public:
	typedef typename TBase Base;

	explicit Index( const TBase index )
		:
		m_index( index )
	{}

	TBase operator ()() const
	{
		return m_index;
	}

	bool operator <( const Index rhs ) const
	{
		return m_index < rhs.m_index;
	}

	bool operator ==( const Index rhs ) const
	{
		return m_index == rhs.m_index;
	}

	bool operator !=( const Index rhs ) const
	{
		return m_index != rhs.m_index;
	}

	bool operator >( const Index rhs ) const
	{
		return m_index > rhs.m_index;
	}


	bool operator ++()
	{
		return ++m_index;
	}


	// ???? :: Should we just auto 
	operator TBase() const
	{
		return m_index;
	}


private:
	TBase m_index;
};