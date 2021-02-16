//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once


#include "../res/Resource.h"

//#include "XMLReader.h"

class Root_XMLReader
{
public:
	template <class U>
	void Reflection( U &functor );

	virtual void Reflection( XMLReader &reader ) = 0;
};

class Does_XMLReader
{
public:
	template <class U>
	void Reflection( U &functor );

	virtual void Reflection( XMLReader &reader ) { Reflection<XMLReader>( reader ); }
};

class Config : public Resource, public Root_XMLReader
{
public:
	CLASS( Config, Resource );


	virtual void Reflection( XMLReader &reader ) { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( Config, Resource );
	REFLECT_END();


	//static ResourcePtr Create( const char * const pFilename, const util::Symbol &type );

	virtual void load( const char * const pFilename );


};

template< typename T, typename TCFG >
class Createable
{
public:
	virtual std::shared_ptr<T> create()
	{
		return T::shared_from_this();
	}
};

template< typename T >
T *LoadTypedConfig( const char * const pResourceName, const TiXmlElement * const pElem )
{	
	XMLReader reader( pElem );
	
	T * const pConfig = new T( pResourceName );
	
	if( pElem != NULL )
	{
		pConfig->Reflection( reader );
	}
	
	return pConfig;
}

template< typename T >
T *LoadTypedConfig( const char * const pFile )
{
	TiXmlDocument doc;

	doc.LoadFile( pFile );

	return LoadTypedConfig<T>( pFile, doc.RootElement() );
}
















// -