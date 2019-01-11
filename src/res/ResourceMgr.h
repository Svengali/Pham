//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

StdPtr( Resource );

namespace ResourceMgr
{

	void AppStart();
	void AppStop();

	void Tick();

	
	typedef ResourcePtr (*CreatorFuncPtr) ( const char * const fileName, const util::Symbol &type );

	//void RegisterCreator( const char * const pExtension, CreatorFuncPtr func );
	void RegisterCreator( const char * const pExtension, const util::Symbol &type, CreatorFuncPtr func );

	//returns resource.  Does not load if not found
	ResourcePtr LookupResource( const char * const pResName );

	//Loads resource if it doesnt find it.
	ResourcePtr GetResource( const char * const pResName, const util::Symbol &type );
	
	template< typename T >
	std::shared_ptr<T> GetResource( const char * const pResName )
	{
		return std::shared_ptr<T>( static_cast< T * >( GetResource( pResName, T::SClass() ).get() ) );
	}
	
	template< typename T >
	std::shared_ptr<T> GetTypedResource( const char * const pResName )
	{
		ResourcePtr resource = LookupResource( pResName );
		
		if( resource != NULL ) return std::shared_ptr<T>( static_cast< T * >( resource.get() ) );
		
		return T::Create( pResName );
	}





};
