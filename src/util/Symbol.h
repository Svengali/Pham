//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

namespace util
{

class Symbol
{
public:

	/*! Symbol::s_empty
  		An empty Symbol.  
        Is asserted to not clash with any other created Symbol.
        Is asserted to equal Symbol( String::s_empty.CStr() )
		String::s_empty default and turned into a Symbol will match this
        (i.e. for by-Symbol lookups that return gPtr(NULL) as a default).
	**/
	//static Symbol s_empty;
	static const Symbol & Empty();

	enum EEmpty { eEmpty };

	// no default constructor, use Symbol(eEmpty)
	//Symbol();
	explicit Symbol( const EEmpty e );
	explicit Symbol( const char * const pStr );
	explicit Symbol( const util::RuntimeString &str );
	// default copy constructor is good

	uint32_t hash() const { return m_hash.GetHash(); }
	//void	SetHash(ulong h); // avoid this if possible, it kills debug strings
	
	//void	SetULong(const ulong z) { m_hash = CRC(z); } // @@ should clear m_string

	inline bool operator ==( const Symbol &tkn ) const { return m_hash == tkn.m_hash; }
	inline bool operator < ( const Symbol &tkn ) const { return m_hash <  tkn.m_hash; }

	inline operator size_t () const { return (size_t) m_hash.GetHash(); }

	MAKE_COMPARISONS_FROM_LESS_AND_EQUALS(Symbol)

	const char * const GetString( void ) const;

private:
	FORBID_DEFAULT_CTOR(Symbol);

	cb::CRC m_hash;

	util::RuntimeString	m_string;
};


}
