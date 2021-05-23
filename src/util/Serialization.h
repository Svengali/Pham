//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

//typedef void (T::*ReflectionXMLReaderFor##T)( XMLReader & );

/*
class XMLReader;

typedef void (*FnReflectXMLReader)( void *, XMLReader &t );

void ReflectXMLReader##T( T * t, XMLReader &reader ) { t->Reflection( reader ); } \

	Serialization::RegClassReflection( sym, (FnReflectXMLReader)ReflectXMLReader##T ); \


	void RegClassReflection( const util::Symbol &sym, FnReflectXMLReader fnCreate );
*/

enum class ESerializable
{
	eConstruct = 1
};


template<typename T>
T *construct_for_serialization()
{
	return new T();
}



#define SERIALIZABLE( T ) \
void *NewSerializableClass##T() \
{ \
	return (void *)construct_for_serialization<T>(); \
} \
void *PlacementNewSerializableClass##T( char *buffer ) \
{ \
	return (void *)new(buffer) T(); \
} \
bool RegisterSerializableClass##T( const util::Symbol &sym ) \
{ \
	Serialization::RegNew( sym, NewSerializableClass##T ); \
	Serialization::RegPlacementNew( sym, PlacementNewSerializableClass##T ); \
	return true; \
} \
const bool s_fakeValForStaticInitTrick##T = RegisterSerializableClass##T( util::Symbol( #T ) ); \
//end #define SERIALIZABLE

typedef void *(*FnNewClassByName)();
typedef void *(*FnPlacementNewClassByName)( char *buf );

namespace Serialization
{

	void RegNew( const util::Symbol &sym, FnNewClassByName fnCreate );
	void RegPlacementNew( const util::Symbol &sym, FnPlacementNewClassByName fnCreate );
		
	void *CreateClassFromTypeName_base( const util::Symbol &sym );
	void *CreateClassFromTypeName_base( const util::Symbol &sym, char *buffer );
	
	template<typename T>
	T *CreateClassFromTypeName( const util::Symbol &sym )
	{
		return reinterpret_cast< T * >( CreateClassFromTypeName_base( sym ) );
	}
	
}










// -