
//////////////////////////////////////////////////////////////////////////////
//
//   P h a m
//
// copyright 2005-2020 Marc Hernandez

#pragma once

PtrFwd( Geometry );
PtrFwd( RenderContext );



class Renderer : public std::enable_shared_from_this<RenderContext>
{
public:

	CLASS( Renderer );

	static void SetupSingleton( Renderer * const pRenderer );

	static Renderer &Inst();

	Renderer();
	virtual ~Renderer();
		


	REFLECT_BEGIN_ROOT( RenderContext );
	REFLECT_END();


	virtual void render();

	virtual RenderContextPtr getFrameContext();

	void addGeo( GeometryPtr geo );


private:

	std::vector< GeometryWeak > m_geos;

};


PtrDef( Renderer );

