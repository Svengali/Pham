//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "AngelReg.h"

#include <hash_map>

/*
template <>
void XMLReader::operator() ( const char * name, cb::hasReflection &val )
{
	const TiXmlElement * const pNamedElem = m_pCurElement->FirstChildElement( name );
	
	{
		ScopedCurElement curElement( this, pNamedElem );
		
		val.Reflection( *this );
	}
}	
*/