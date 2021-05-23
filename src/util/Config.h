//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once


#include "../res/Resource.h"

#include "XMLReader.h"

class Root
{
public:
	//template <class T>
	//void Reflection( T &functor );
};

class Root_XMLReader : public Root
{
public:
	//template <class T>
	//void Reflection( T &functor );

	virtual void Reflection( XMLReader &reader ) = 0;
};

/*
class Does_XMLReader: public Root, public Root_XMLReader
{
public:
	template <class T>
	void Reflection( T &functor );

	virtual void Reflection( XMLReader &reader ) override { Reflection<XMLReader>( reader ); }
};
*/

class Config : public Resource//, public Root_XMLReader
{
public:
	CLASS( Config, Resource );

	Config() {};

	virtual void DoReflection( XMLReader &reader ) = 0;
	REFLECT_BEGIN( Config, Resource );
	REFLECT_END();


	static ResourcePtr create( const char * const pFilename, const util::Symbol &type );

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
T *loadTypedConfig( const char * const pResourceName, const TiXmlElement * const pElem )
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
T *loadTypedConfig( const char * const pFile )
{
	TiXmlDocument doc;

	doc.LoadFile( pFile );

	return loadTypedConfig<T>( pFile, doc.RootElement() );
}
















// -