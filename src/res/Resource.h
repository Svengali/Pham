//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once


class Resource //: public cb::hasReflection
{

public:
	CLASS( Resource );
	
	Resource();
	virtual ~Resource();
	
	REFLECT_BEGIN_ROOT( Resource );
		REFLECT( m_filename );
		//REFLECT( m_lastUsedTime );
	REFLECT_END();
	
	virtual void load( const char * const pFilename ) = 0;
	
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
    BoolAsType_True     hasReflection;
    BoolAsType_False	isPrimitive;
    BoolAsType_False	ioBytes;
};



StdPtr( Resource );


















// -