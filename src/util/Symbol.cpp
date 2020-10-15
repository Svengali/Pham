//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"



#include "Symbol.h"

namespace util
{

/*static*/ const Symbol & Symbol::Empty()
{
	static Symbol s_empty(Symbol::eEmpty);
	return s_empty;
}

// don't use any statics in this, since Symbol(eEmpty) can be made from other static intializers
Symbol::Symbol( const EEmpty ) 
	:
	m_hash( "" ),
	m_string( "" )
{
}

Symbol::Symbol( const char * const pStr ) 
	:
	m_hash( pStr ),
	m_string( pStr )
{
}

Symbol::Symbol( const util::RuntimeString &str )
	:
	m_hash( str.c_str() ),
	m_string( str )
{
}

const char * const Symbol::GetString( void ) const
{
	return m_string.c_str();
}

}
