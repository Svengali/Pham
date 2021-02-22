//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

#if 0

SPtrFwd( ResScript );

class asIScriptContext;

template< typename T >
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, T t )
{
	//If you hit this, the Script.cpp specialization needs to be updated with the type of T
	//return -1;
};

template< typename T >
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, T *val )
{
	return pContext->SetArgObject( whichArg, reinterpret_cast<void *>( const_cast< T * >( val ) ) );
};

template< typename T >
int SetArgOnContext( asIScriptContext * const pContext, const int whichArg, SPtr<T> val )
{
	return pContext->SetArgObject( whichArg, reinterpret_cast<void *>( const_cast< T * >( val.GetPtr() ) ) );
};


template< typename T >
struct TypenameResolver
{
	const char *operator ()()
	{
		return typeid( T ).name();
	}
};

template< typename T >
struct TypenameResolver< T * >
{
	const char *operator ()()
	{
		return T::SClass().GetString();
	}
};

template< typename T >
struct TypenameResolver< SPtr<T> >
{
	const char *operator ()()
	{
		return T::SClass().GetString();
	}
};

template<>
struct TypenameResolver< CEGUIWrapper * >
{
	const char *operator ()()
	{
		return "Window@";
	}
};


class Script : public RefCounted
{

public:
	
	static Script *s_curScript;
	
	~Script();
	
	void Init( const char * const pFilename );

	
	template< typename T1 >
	T1 Call( const RuntimeString &name )
	{
		TypenameResolver< T1 > t1;

		const char * const pReturnType = t1();
	
		MakeFnCall_raw( name, RuntimeString( pReturnType ), RuntimeString( "" ) );
		
		return T1();
	}
	
	template< typename T1, typename T2 >
	T1 Call( const RuntimeString &name, const T2 &arg0 )
	{
		char buf[ 256 ];
	
		TypenameResolver< T1 > t1;
		TypenameResolver< T2 > t2;
		
		_snprintf_s( buf, 256, "%s", t2() );
		
		SetArgOnContext( m_pContext, 0, arg0 );
	
		const char * const pReturnType = t1();

		MakeFnCall_raw( name, RuntimeString( pReturnType ), RuntimeString( buf ) );
		return T1();
	}

private:

	void MakeFnCall_raw( const RuntimeString &name, const RuntimeString &ret_type, const RuntimeString &args );

	ResScriptPtr m_script;
	asIScriptContext *m_pContext;


};


SPtrDef( Script );

#endif









// -