//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

namespace util
{
	typedef std::string RuntimeString;

#ifdef _DEBUG
	typedef std::string DebugString;
#endif _DEBUG




}


template <>
struct cb::TypeTraits<util::RuntimeString>
{
    BoolAsType_False    hasReflection;
    BoolAsType_False	isPrimitive;
    BoolAsType_False	ioBytes;
};
