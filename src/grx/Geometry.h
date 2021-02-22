//////////////////////////////////////////////////////////////////////////////
//
// P H A M
//
// copyright 2005-2021 Marc Hernandez

#pragma once


PtrFwd( RenderContext );

//#include "RenderContext.h"


class Geometry : public Resource
{

public:

	CLASS( Geometry, Resource );

	Geometry();
	virtual ~Geometry();
	
	virtual void render( const RenderContextPtr &rcon, const cb::Frame3 &pos ) = 0;
	
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
	
	//virtual void Reflection( XMLReader &reader ) { Reflection<XMLReader>( reader ); }
	REFLECT_BEGIN( Geometry, Resource );
	REFLECT_END();


private:
	//Frame3 m_frame;
	
};

PtrDef( Geometry );














// -