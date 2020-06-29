//////////////////////////////////////////////////////////////////////////////
//
// P H A M
//
// copyright 2005-2008 Marc Hernandez
#pragma once


PtrFwd( RenderContext );

//#include "RenderContext.h"

class Geometry : public std::enable_shared_from_this<Geometry>
{

public:

	CLASS( Geometry );

	Geometry();
	virtual ~Geometry();
	
	virtual void Render( const RenderContextPtr &rcon, const cb::Mat4 &pos ) = 0;
	
	/*
	void SetPosition( const Vec3 pos )
	{
		m_frame.SetTranslation( pos );
	}
	
	Vec3 GetPosition() const
	{
		return m_frame.GetTranslation();
	}
	*/	
	
	REFLECT_BEGIN_ROOT( Geometry );
	REFLECT_END();


private:
	//Frame3 m_frame;
	
};

PtrDef( Geometry );














// -