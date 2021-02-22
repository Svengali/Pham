//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

/*
TODO:
x) How can we lookup resources that have contexts.  
x) What about shared generated assets?  Filename->asset maybe?
x) 
*/

#pragma once

PtrFwd( Resource );

namespace ResourceMgr
{

	void AppStart();
	void AppStop();

	void Tick();

	
	//typedef ResourcePtr (*FnCreator) ( const char * const fileName, const util::Symbol &type );

	typedef std::function<ResourcePtr(const char * const pFilename, const util::Symbol type)> FnCreator;


	//void RegisterCreator( const char * const pExtension, FnCreator func );
	void RegisterCreator( const char * const pExtension, const util::Symbol &type, FnCreator func );

	void AddResource( const char *const pResName, const ResourcePtr &ptr );

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
