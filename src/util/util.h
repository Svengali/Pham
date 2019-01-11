//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once


// Generic utility functions



template< typename TO, typename FROM >
TO cast( FROM from )
{
    return static_cast<TO>( from );
}

#define StdPtr(CLASS) \
class CLASS; \
typedef std::shared_ptr<CLASS> CLASS ## Ptr; \
//#end define StdPtr



template< typename TO, typename FROM >
const std::shared_ptr<TO> shared_cast( const std::shared_ptr<FROM> &from )
{
	return std::shared_ptr<TO>( cast<TO *>( from.get() ) );
}
