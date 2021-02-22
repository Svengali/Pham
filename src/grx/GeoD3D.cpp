//////////////////////////////////////////////////////////////////////////////
//
//   S p a c e
//
// copyright 2005-2021 Marc Hernandez



#include "../stdafx.h"



#if 0

#include ".\GeoD3D.h"
#include "../Resource/ResXMesh.h"
#include "../Resource/ResXEffect.h"
#include "../Resource/ResXTex.h"

#include "../Camera/CameraMgr.h"

#include "../Renderer/RenderContext.h"

SERIALIZABLE( GeoD3D );

GeoD3D::GeoD3D()
{
	//Do Nothing.
}


GeoD3D::GeoD3D( const char * const pMesh )
{
	m_mesh = ResourceMgr::GetResource<ResXMesh>( pMesh );
}

GeoD3D::~GeoD3D(void)
{
}



void GeoD3D::SetEffectDefaults( ID3DXEffect * const pEffect, const D3DXEFFECTINSTANCE &effectInst )
{
	int texIndex = 0;

	for( unsigned i=0; i<effectInst.NumDefaults; ++i )
	{
		const D3DXEFFECTDEFAULT * const pEffectDef = &effectInst.pDefaults[ i ];
		
		D3DXPARAMETER_DESC paramDesc;
		
		pEffect->GetParameterDesc( pEffectDef->pParamName, &paramDesc );
		
		if( paramDesc.Class != D3DXPC_OBJECT || paramDesc.Type != D3DXPT_TEXTURE )
		{
			pEffect->SetValue( pEffectDef->pParamName, pEffectDef->pValue, pEffectDef->NumBytes );
		}
		else
		{
			ASSERT( texIndex < m_mesh->m_tex.size() );
			
			pEffect->SetTexture( pEffectDef->pParamName, m_mesh->m_tex[ texIndex ]->GetD3DTexture() );
		}
	}

}

//extern CModelViewerCamera g_Camera;


void GeoD3D::Render( const RenderContextPtr &rcon, const Frame3 &frame )
{
	HRESULT hr;

	ID3DXEffect * const pEffect = m_mesh->m_effect->GetD3DEffect();

	V( pEffect->SetTechnique( "RenderScene" ) );

	UINT passCount;
	V( pEffect->Begin( &passCount, 0 ) );
	
	SetEffectDefaults( pEffect, m_mesh->m_effectInst );

	const D3DXMATRIXA16 mProj = rcon->GetProjectionMat();

	const Mat4 world( frame.GetMatrix(), frame.GetTranslation() );
	const D3DXMATRIXA16 * const pWorld = reinterpret_cast<const D3DXMATRIXA16 *>( &world );
	
	D3DXMATRIXA16 mWorld = *pWorld; // = *g_Camera.GetWorldMatrix();

	//D3DXMatrixTranslation( &mWorld, frame.GetTranslation().x, frame.GetTranslation().y, frame.GetTranslation().z );
	//D3DXMatrixTranslation( &mWorld, 0, 0, 0 );
	
	const Vec3 camPos = CameraMgr::GetCameraPosition();
	
	const Mat4 view( CameraMgr::GetCameraMatrix(), CameraMgr::GetCameraPosition() );

	const D3DXMATRIXA16 * const pView = reinterpret_cast<const D3DXMATRIXA16 *>( &view );
	


	// Update the effect's variables.  Instead of using strings, it would 
	// be more efficient to cache a handle to the parameter by calling 
	// ID3DXEffect::GetParameterByName
	//V( g_pEffect->SetFloat( "g_fTime", (float)fTime ) );


//shared float4x4 g_mWorldView : WORLDVIEW;               // View matrix for object
//shared float4x4 g_mWorldViewProjection : WORLDVIEWPROJECTION; // World * View * Projection matrix
//shared float4x4 g_mView : VIEW;                         // view matrix

	const D3DXMATRIXA16 mViewProj = (*pView) * mProj;
	const D3DXMATRIXA16 mWorldView = mWorld * (*pView);
	const D3DXMATRIXA16 mWorldViewProjection = mWorld * (*pView) * mProj;
	
	V( pEffect->SetMatrix( "g_mWorldView", &mWorldView ) );
	V( pEffect->SetMatrix( "g_mWorldViewProjection", &mWorldViewProjection ) );
	V( pEffect->SetMatrix( "g_mView", pView ) );

	IDirect3DDevice9 * const pd3dDevice = DXUTGetD3D9Device();
	
	
	const Mat4 * const pMatProj = reinterpret_cast< const Mat4 * >( &mProj );
	const Mat4 * const pMatWorldViewProj = reinterpret_cast< const Mat4 * >( &mWorldViewProjection );

	
	const Vec4 otherPos( 0, 0, 0, 1 );
	
	const Vec4 otherPos_mult = view * otherPos;

	const Vec4 otherPos_screen = *pMatProj * otherPos_mult;

	const Vec4 otherPos_screen_2 = *pMatWorldViewProj * otherPos_mult;
	
	//pd3dDevice->Set
	
	for( UINT pass=0; pass<passCount; ++pass )
	{
		V( pEffect->BeginPass( pass ) );



	//V( m_mesh->m_meshData.m_pMeshSysMem->DrawSubset( 0 ) );

	DWORD dwFVF;
	DWORD cBytesPerVertex;
	//DWORD iStrip;

	dwFVF = m_mesh->m_meshData.m_pMesh->GetFVF();
	cBytesPerVertex = D3DXGetFVFVertexSize( dwFVF );

	V( pd3dDevice->SetFVF( dwFVF ) );
	V( pd3dDevice->SetStreamSource( 0, m_mesh->m_meshData.m_pVertexBuffer, 0, cBytesPerVertex ) );

	//if( g_bShowSingleStrip )
	{
		//if( !g_bCantDoSingleStrip )
		{
			V( pd3dDevice->SetIndices( m_mesh->m_meshData.m_rgStripData[0].m_pStrips ) );

			V( pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0,
				0, m_mesh->m_meshData.m_pMesh->GetNumVertices(),
				0, m_mesh->m_meshData.m_rgStripData[0].m_cStripIndices - 2 ) );
		}
	}
 		/*
	else
	{
		V( pd3dDevice->SetIndices( m_mesh->m_meshData.m_rgStripData[0].m_pStripsMany ) );

		int iCurFace = 0;
		for( iStrip = 0; iStrip < m_mesh->m_meshData.m_rgStripData[0].m_cStrips; iStrip++ )
		{
			V( pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0,
				0, m_mesh->m_meshData.m_pMesh->GetNumVertices(),
				iCurFace, m_mesh->m_meshData.m_rgStripData[0].m_rgcStripLengths[iStrip] ) );

				iCurFace += 2 + m_mesh->m_meshData.m_rgStripData[0].m_rgcStripLengths[iStrip];
		}
	}
	*/
		
		
		V( pEffect->EndPass() );
	}

	V( pEffect->End() );




	/*
    V( g_pEffect->SetTechnique( "RenderScene" ) );
    UINT cPasses;
    V( g_pEffect->Begin( &cPasses, 0 ) );
    for( UINT p = 0; p < cPasses; ++p )
    {
        V( g_pEffect->BeginPass( p ) );

        // Set and draw each of the materials in the mesh
        for( DWORD iMaterial = 0; iMaterial < m_mesh->m_dwNumMaterials; iMaterial++ )
        {
            V( g_pEffect->SetVector( "g_vDiffuse", (D3DXVECTOR4*)&m_mesh->m_pMeshMaterials[iMaterial].Diffuse ) );
            V( g_pEffect->SetTexture( "g_txScene", m_mesh->m_tex[iMaterial]->GetD3DTexture() ) );
            V( g_pEffect->CommitChanges() );
//            V( pd3dDevice->SetMaterial( &g_pMeshMaterials[iMaterial] ) );
//            V( pd3dDevice->SetTexture( 0, g_ppMeshTextures[iMaterial] ) );

            //if( !g_bShowStrips && !g_bShowSingleStrip )
            {
                V( pd3dMesh->DrawSubset( iMaterial ) );
            }
            
            /*
            else  // drawing strips
            {
                DWORD dwFVF;
                DWORD cBytesPerVertex;
                DWORD iStrip;

                dwFVF = m_mesh->m_meshData.m_pMesh->GetFVF();
                cBytesPerVertex = D3DXGetFVFVertexSize( dwFVF );

                V( pd3dDevice->SetFVF( dwFVF ) );
                V( pd3dDevice->SetStreamSource( 0, m_mesh->m_meshData.m_pVertexBuffer, 0, cBytesPerVertex ) );

                if( g_bShowSingleStrip )
                {
                    if( !g_bCantDoSingleStrip )
                    {
                        V( pd3dDevice->SetIndices( m_mesh->m_meshData.m_rgStripData[iMaterial].m_pStrips ) );

                        V( pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0,
                                                    0, m_mesh->m_meshData.m_pMesh->GetNumVertices(),
                                                    0, m_mesh->m_meshData.m_rgStripData[iMaterial].m_cStripIndices - 2 ) );
                    }
                }
                else
                {
                    V( pd3dDevice->SetIndices( m_mesh->m_meshData.m_rgStripData[iMaterial].m_pStripsMany ) );

                    iCurFace = 0;
                    for( iStrip = 0; iStrip < m_mesh->m_meshData.m_rgStripData[iMaterial].m_cStrips; iStrip++ )
                    {
                        V( pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0,
                                                    0, m_mesh->m_meshData.m_pMesh->GetNumVertices(),
                                                    iCurFace, m_mesh->m_meshData.m_rgStripData[iMaterial].m_rgcStripLengths[iStrip] ) );

                        iCurFace += 2 + m_mesh->m_meshData.m_rgStripData[iMaterial].m_rgcStripLengths[iStrip];
                    }
                }
            }
            * /
        }
        V( g_pEffect->EndPass() );
    }
    V( g_pEffect->End() );
    */
    
    
}

#endif

































// -