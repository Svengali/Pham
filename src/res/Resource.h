//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#pragma once


class Resource : public std::enable_shared_from_this<Resource>
{

public:
	CLASS( Resource );
	
	Resource();
	virtual ~Resource();
	
	REFLECT_BEGIN_ROOT( Resource );
		REFLECT( m_filename );
		//REFLECT( m_lastUsedTime );
	REFLECT_END();
	
	// @@@@ TODO Not a fan of this at all.
	virtual void load( const char * const pFilename, const util::Symbol type ) {}
	
	virtual void onPreLoad();
	virtual void onPostLoad();
	
	virtual void onPreChange();
	virtual void onPostChange();
	
	void use();
		
	void ResourceMgr_setFilename( const util::RuntimeString &filename );
	
private:
	util::RuntimeString  m_filename;
	AbsoluteTime m_lastUsedTime;
	
};



template <> 
struct cb::TypeTraits<Resource>
{
    BoolAsType_True		hasReflection;
    BoolAsType_False	isPrimitive;
    BoolAsType_False	ioBytes;
};


PtrDef( Resource );


template<>
inline std::shared_ptr<Resource> cast_from_string( const char *const pStr )
{
	return nullptr;
}
