
//////////////////////////////////////////////////////////////////////////////
//
//   P h a m
//
// copyright 2005-2020 Marc Hernandez
#pragma once


//#include <d3dx9math.h>


template<>
inline cb::Mat4 cast_from_string( const char *const pStr )
{
	return cb::Mat4();
}


class RenderContext : public std::enable_shared_from_this<RenderContext>
{
public:

	CLASS( RenderContext );

	RenderContext();
	virtual ~RenderContext();
		
	void SetProjectionMat( const float near, const float far, const float fov_horiz, const float fov_vert );
	


	const cb::Frame3 &GetProjectionMat() const
	{
		return m_proj;
	}
		


	REFLECT_BEGIN_ROOT( RenderContext );
		REFLECT(m_proj);
	REFLECT_END();



private:

	cb::Frame3 m_proj;

};


PtrDef( RenderContext );














// -