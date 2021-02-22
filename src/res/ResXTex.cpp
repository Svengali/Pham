//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#if 0

#include ".\ResXTex.h"

#include "../DXUT/Core/DXUT.h"

#include <D3D9.h>
#include <D3dx9tex.h>


ResourcePtr ResXTex::Create( const char * const pFilename, const Symbol &type )
{
	ResXTexPtr resXTex( new ResXTex() );
	
	resXTex->Load( pFilename );

	return resXTex;
}


ResXTex::~ResXTex(void)
{
	if( m_pMeshTexture != NULL )
	{
		m_pMeshTexture->Release();
	}
}

void ResXTex::Load( const char * const pFilename )
{
	ASSERT( m_pMeshTexture == NULL );

	WCHAR wszBuf[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, pFilename, -1, wszBuf, MAX_PATH );
	wszBuf[MAX_PATH - 1] = L'\0';
	//DXUTFindDXSDKMediaFileCch( strPath, 512, wszBuf );

	// Load the texture
	const HRESULT hr = D3DXCreateTextureFromFile( DXUTGetD3D9Device(), wszBuf, &m_pMeshTexture );
	
	hr;
	
	//gD3DUtil::ShowHR( hr );
}

#endif
