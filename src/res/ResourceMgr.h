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

template<typename T>
void fillInRes( T *pT )
{
	lprintf( "Skip fill in %s resource.\n", T::SClass() );
}

template<typename T>
void createDefaultRes( T **ppT )
{
	T *pT = cast<T*>( Serialization::CreateClassFromTypeName_base( T::SClass() ) );
	fillInRes( pT );
	*ppT = pT;
}











class ResCreator
{
public:
	CLASS( ResCreator );

	virtual ~ResCreator() = default;

	virtual ResourcePtr create() const = 0;

};

class ResNullCreator: public ResCreator
{

public:
	ResNullCreator( const char *pStr )
	{
		lprinterr( "Error trying to create %s\n", pStr );
	}

	ResNullCreator() = default;

	virtual ResourcePtr create() const
	{
		return nullptr;
	}


};


template <bool t_bool>
struct CreatorBoolToType
{
	enum { value = t_bool };
};

typedef CreatorBoolToType<true>		CreatorBoolAsType_True;
typedef CreatorBoolToType<false>	CreatorBoolAsType_False;


template <typename T>
struct CreatorTraits
{
	CreatorBoolAsType_False hasACustomCreator;
	typedef ResNullCreator Creator;
};

enum class ResFlags
{
	fUnique = 1 << 0,
};

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
	ResourcePtr GetResource( const char *const pResName, const util::Symbol &type );

	bool RemResource( const char *const pResName );

	ResourcePtr GetResource( const char *const pResName, const ResCreator * const pCreator );


	template< typename T >
	std::shared_ptr<T> GetResource( const char * const pResName )
	{
		ResourcePtr ptr = GetResource(pResName, T::SClass());

		std::shared_ptr<T> ret = std::static_pointer_cast<T>(ptr);

		return ret;

		//This is wrong.
		//return std::shared_ptr<T>( static_cast< T * >( GetResource( pResName, T::SClass() ).get() ) );
	}
	
	/* 
	template< typename T >
	std::shared_ptr<T> GetTypedResource( const char * const pResName )
	{
		ResourcePtr resource = LookupResource( pResName );
		
		if( resource != NULL ) return std::shared_ptr<T>( static_cast< T * >( resource.get() ) );
		
		return T::Create( pResName );
	}
	*/

	template< typename T >
	std::shared_ptr<T> LookupResource( const char *const pResName )
	{
		ResourcePtr resource = LookupResource( pResName );

		if( resource != NULL ) return std::shared_ptr<T>( static_cast<T *>( resource.get() ) );

		return nullptr;
	}




};
