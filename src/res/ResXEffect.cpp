//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"


#include ".\ResXEffect.h"

#include <D3DX9Effect.h>
#include "../DXUT/Core/DXUT.h"

ResourcePtr ResXEffect::Create( const char * const pFilename, const Symbol &type )
{
	ResXEffectPtr ResXEffect( new ResXEffect() );
	
	ResXEffect->Load( pFilename );

	return ResXEffect;
}

ResXEffect::~ResXEffect(void)
{
	if( m_pEffect != NULL )
	{
		m_pEffect->Release();
	}
}

void ResXEffect::Load( const char * const pFilename )
{
	ASSERT( m_pEffect == NULL );

	WCHAR wszBuf[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, pFilename, -1, wszBuf, MAX_PATH );
	wszBuf[MAX_PATH - 1] = L'\0';
	//DXUTFindDXSDKMediaFileCch( strPath, 512, wszBuf );

	// Load the texture
	//const HRESULT hr = D3DXCreateTextureFromFile( DXUTGetD3DDevice(), wszBuf, &m_pMeshTextures );
	
	const HRESULT hr = D3DXCreateEffectFromFile( DXUTGetD3D9Device(), wszBuf, NULL, NULL, 0, NULL, &m_pEffect, NULL );
	
	UNUSED_PARAMETER( hr );
	
	//gD3DUtil::ShowHR( hr );
}














// -