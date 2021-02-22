//////////////////////////////////////////////////////////////////////////////
//
//   S p a c e
//
// copyright 2005-2008 Marc Hernandez



#include "../stdafx.h"
#include ".\Renderer.h"

Renderer *s_pRenderer;

void Renderer::startup( Renderer *const pRenderer )
{
  s_pRenderer = pRenderer;
}


Renderer &Renderer::Inst()
{
  return *s_pRenderer;
}



Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}




void Renderer::render()
{
  const RenderContextPtr &rc = getFrameContext();
}

RenderContextPtr Renderer::getFrameContext()
{
  return nullptr;
}

void Renderer::addGeo( GeometryPtr geo )
{
}






/*
D3DXMATRIX 
ProjectionMatrix(const float near_plane, // Distance to near clipping 
                                         // plane
                 const float far_plane,  // Distance to far clipping 
                                         // plane
                 const float fov_horiz,  // Horizontal field of view 
                                         // angle, in radians
                 const float fov_vert)   // Vertical field of view 
                                         // angle, in radians
{
	/*
    float    h, w, Q;

    w = (float)1/tan(fov_horiz*0.5);  // 1/tan(x) == cot(x)
    h = (float)1/tan(fov_vert*0.5);   // 1/tan(x) == cot(x)
    Q = far_plane/(near_plane - far_plane);

    D3DXMATRIX ret;
    ZeroMemory(&ret, sizeof(ret));

    ret(0, 0) = w;
    ret(1, 1) = h;
    ret(2, 2) = Q;
    ret(3, 2) = -Q*near_plane;
    ret(2, 3) = -1;
    return ret;
    //* /
    
    //*
    D3DXMATRIX ret;
    D3DXMatrixPerspectiveRH( &ret, fov_horiz, fov_vert, near_plane, far_plane );
    
    //D3DXMATRIX rotX;
    //D3DXMatrixRotationX( &rotX, -D3DX_PI / 2 );
    
    return ret;
    //* /
    
}   // End of ProjectionMatrix

*/

/*
void RenderContext::SetProjectionMat( const float near_plane, const float far_plane, const float fov_horiz, const float fov_vert )
{
	//m_proj = ProjectionMatrix( near_plane, far_plane, fov_horiz, fov_vert );
}
*/