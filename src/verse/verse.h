//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

namespace grx
{
class SimpleMesh;
}

PtrFwd(Geometry);

namespace verse
{

class Factory
{
public:


	virtual GeometryPtr convert( const grx::SimpleMesh * const pMesh ) = 0;



};

	












}

