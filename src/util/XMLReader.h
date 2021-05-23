//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once


class TiXmlElement;

#include "./Serialization.h"

#include "../res/ResourceMgr.h"







//
// Base case.  Try and construct from the string text
//
template< typename T >
T cast_from_string( const char * const pStr )
{
	return T( pStr );
}

template<>
inline std::string cast_from_string( const char * const pStr )
{
	return std::string( pStr );
}

template<>
inline float cast_from_string( const char * const pStr )
{
	return cast<float>( atof( pStr ) );
}
template<>
inline double cast_from_string( const char * const pStr )
{
	return cast<double>( atof( pStr ) );
}

template<>
inline int cast_from_string( const char * const pStr )
{
	return atoi( pStr );
}

template<>
inline bool cast_from_string( const char * const pStr )
{
	return !!atoi( pStr );
}

template<>
inline cb::Vec3 cast_from_string( const char * const pStr )
{
	float x,y,z;

	sscanf( pStr, "%f,%f,%f", &x, &y, &z );

	return cb::Vec3( x, y, z );
}

template<>
inline cb::Frame3 cast_from_string( const char * const pStr )
{
	float x,y,z;

	// @@@@ TODO BROKEN Need to properly parse Frame3 text.
	sscanf( pStr, "%f,%f,%f", &x, &y, &z );

	return cb::Frame3( cb::Frame3::eIdentity );
}



class XMLWriter
{
public:
	template <class T>
	void operator() (const char * name, T &val )
	{
	}	
};

class XMLReader
{
	class ScopedCurElement
	{
	public:
		ScopedCurElement( XMLReader *pReader, const TiXmlElement *pNewCurElement )
			:
			m_pReader( pReader ),
			m_pOldCurElement( pReader->m_pCurElement )
		{
			m_pReader->m_pCurElement = pNewCurElement;
		}
		
		~ScopedCurElement()
		{
			m_pReader->m_pCurElement = m_pOldCurElement;
		}
		
		
	private:
		XMLReader *m_pReader;
		const TiXmlElement *m_pOldCurElement;
	};

	const std::string getPathName( const TiXmlElement *const pCurElement )
	{
		if( pCurElement == nullptr ) return m_filename;

		const auto pElem = pCurElement->Parent()->ToElement();

		return getPathName( pElem ) + pCurElement->ValueStr();
	}




public:

	std::string m_filename;

	std::hash_map< int, int > m_ptrs;

	const TiXmlElement *m_pCurElement;

	XMLReader( const std::string &filename, const TiXmlElement * const pCurElement )
		:
		m_filename( filename ),
		m_pCurElement( pCurElement )
	{
		
	}


	template < typename T >
	void operator() ( const TiXmlElement * const pNamedElem, T &val, cb::BoolAsType_False )
	{
		const char * const pValText = pNamedElem->Attribute( "v" );
		
		if( pValText != NULL )
		{
			val = cast_from_string< T >( pValText );
		}
		else
		{
			//What to do?  LOG it?
		}
	}

	template < typename T >
	void operator()( const TiXmlElement * const pNamedElem, typename T &val, cb::BoolAsType_True )
	{
		ScopedCurElement curElement( this, pNamedElem );
					
		val.Reflection( *this );
	}

	template < typename T >
	void operator() ( const TiXmlElement *const pNamedElem, T &val, CreatorBoolAsType_False )
	{
		( *this )( pNamedElem, val, cb::TypeTraits<T>().hasReflection );
	}

	template < typename T >
	void operator() ( const TiXmlElement *const pNamedElem, T &val, CreatorBoolAsType_True )
	{
		blah2;
	}

	template < typename T >
	void operator() ( const TiXmlElement * const pNamedElem, T &val )
	{

		(*this)( pNamedElem, val, CreatorTraits<T>().hasACustomCreator );

	}	


	/*
	template <class T>
	void operator() (const TiXmlElement * const pNamedElem, cb::Reflect< T > &val )
	{
		ScopedCurElement curElement( this, pNamedElem );
		
		val.Reflection( *this );
	}
	*/


	template <class T>
	void operator() (const TiXmlElement * const pNamedElem, std::shared_ptr< T > &val )
	{
		const char * const pValSource = pNamedElem->Attribute( "source" ) ? pNamedElem->Attribute( "source" ) : "";

		if( strcmp( "embed", pValSource ) == 0 )
		{
			const char * const pValType = pNamedElem->Attribute( "t" );
			
			if( pValType )
			{
				const auto pathName = getPathName( pNamedElem );

				val = ResourceMgr::LookupResource<T>(pathName.c_str());

				if( !val )
				{
					ScopedCurElement curElement( this, pNamedElem );

					T *pT = Serialization::CreateClassFromTypeName< T >( util::Symbol( pValType ) );

					pT->Reflection( *this );

					val = std::shared_ptr<T>( pT );

					ResourceMgr::AddResource( pathName.c_str(), val );
				}

			}
						
			return;
		}
		else if( T::SIsSubclassOf( util::Symbol( "Resource" ) ) )
		{
			const char *const pValCreator = pNamedElem->Attribute( "creator" );

			if( !pValCreator )
			{
				const auto pValType = pNamedElem->Attribute( "t" ) ? util::Symbol( pNamedElem->Attribute( "t" ) ) : T::SClass();

				val = std::static_pointer_cast<T>( ResourceMgr::GetResource( pValSource, pValType ) );

				return;
			}
			else
			{
				ScopedCurElement curElement( this, pNamedElem );

				//const TiXmlElement *pChild = m_pCurElement->FirstChildElement();

				//std::unique_ptr<ResCreator> creator( Serialization::CreateClassFromTypeName<ResCreator>( util::Symbol( pValCreator ) ) );


				typename CreatorTraits<T>::Creator creator;

				( *this )( pNamedElem, creator );

				val = std::static_pointer_cast<T>( ResourceMgr::GetResource( pValSource, &creator ) );
			}
		}
		else 
		{
			TiXmlDocument doc;

			doc.LoadFile( pValSource );
			
			//const TiXmlElement * const pRoot = doc.RootElement();
			
			T * const pT = Serialization::CreateClassFromTypeName< T >( util::Symbol( "Hello" ) );
			
			val = std::shared_ptr<T>( pT );
			
		}
	}
	
	/*
	Doesnt work.
	template <>
	void operator() (const char * name, gPtr< Resource > * const pVal )
	{
		int dummy = 0; dummy;
	}
	*/

	template <typename T> 
	void operator()( const TiXmlElement * const pNamedElem, std::vector< T > &vec )
	{
		ScopedCurElement curElement( this, pNamedElem );
		
		const TiXmlElement *pVecElem = m_pCurElement->FirstChildElement();
	
		while( pVecElem )
		{
			T t;
			
			(*this)( pVecElem, t );
			
			vec.push_back( t );		
		
			pVecElem = pVecElem->NextSiblingElement();
		}
	}


	template < typename T >
	void operator() ( const char * name, T &val )
	{
		const TiXmlElement * const pNamedElem = m_pCurElement->FirstChildElement( name );
		
		if( pNamedElem )
		{
			(*this)( pNamedElem, val );
		}
		else
		{
			//Element wasnt found.
		}
	}	



};
