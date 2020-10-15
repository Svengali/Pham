//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "../stdafx.h"


#include "vox.h"
#include "math/SimplexNoise.h"

/*

void SphereMesh::on_device_created( const DeviceCreatedEvent &event )
{
	auto &device = event.get_device();

	struct Attribute
	{
		gr::vec3 normal;
		gr::vec2 uv;
	};

	std::vector<gr::vec3> positions;
	std::vector<Attribute> attributes;
	std::vector<uint16_t> indices;

	positions.reserve( 6 * density * density );
	attributes.reserve( 6 * density * density );
	indices.reserve( 2 * density * density * 6 );

	float density_mod = 1.0f / float( density - 1 );
	const auto to_uv = [ & ]( unsigned x, unsigned y ) -> gr::vec2 {
		return gr::vec2( density_mod * x, density_mod * y );
	};

	static const gr::vec3 base_pos[6] = {
		gr::vec3( 1.0f, 1.0f, 1.0f ),
		gr::vec3( -1.0f, 1.0f, -1.0f ),
		gr::vec3( -1.0f, 1.0f, -1.0f ),
		gr::vec3( -1.0f, -1.0f, +1.0f ),
		gr::vec3( -1.0f, 1.0f, +1.0f ),
		gr::vec3( +1.0f, 1.0f, -1.0f ),
	};

	static const gr::vec3 dx[6] = {
		gr::vec3( 0.0f, 0.0f, -2.0f ),
		gr::vec3( 0.0f, 0.0f, +2.0f ),
		gr::vec3( 2.0f, 0.0f, 0.0f ),
		gr::vec3( 2.0f, 0.0f, 0.0f ),
		gr::vec3( 2.0f, 0.0f, 0.0f ),
		gr::vec3( -2.0f, 0.0f, 0.0f ),
	};

	static const gr::vec3 dy[6] = {
		gr::vec3( 0.0f, -2.0f, 0.0f ),
		gr::vec3( 0.0f, -2.0f, 0.0f ),
		gr::vec3( 0.0f, 0.0f, +2.0f ),
		gr::vec3( 0.0f, 0.0f, -2.0f ),
		gr::vec3( 0.0f, -2.0f, 0.0f ),
		gr::vec3( 0.0f, -2.0f, 0.0f ),
	};

	// I don't know how many times I've written this exact code in different projects by now. :)
	for( unsigned face = 0; face < 6; face++ )
	{
		unsigned index_offset = face * density * density;
		for( unsigned y = 0; y < density; y++ )
		{
			for( unsigned x = 0; x < density; x++ )
			{
				gr::vec2 uv = to_uv( x, y );
				gr::vec3 pos = normalize( base_pos[face] + dx[face] * uv.x + dy[face] * uv.y );
				positions.push_back( pos );
				attributes.push_back( { pos, uv } );
			}
		}

		unsigned strips = density - 1;
		for( unsigned y = 0; y < strips; y++ )
		{
			unsigned base_index = index_offset + y * density;
			for( unsigned x = 0; x < density; x++ )
			{
				indices.push_back( base_index + x );
				indices.push_back( base_index + x + density );
			}
			indices.push_back( 0xffff );
		}
	}

	BufferCreateInfo info = {};
	info.size = positions.size() * sizeof( gr::vec3 );
	info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	info.domain = BufferDomain::Device;
	vbo_position = device.create_buffer( info, positions.data() );

	info.size = attributes.size() * sizeof( Attribute );
	vbo_attributes = device.create_buffer( info, attributes.data() );

	this->attributes[ecast( MeshAttribute::Position )].format = VK_FORMAT_R32G32B32_SFLOAT;
	this->attributes[ecast( MeshAttribute::Position )].offset = 0;
	this->attributes[ecast( MeshAttribute::Normal )].format = VK_FORMAT_R32G32B32_SFLOAT;
	this->attributes[ecast( MeshAttribute::Normal )].offset = offsetof( Attribute, normal );
	this->attributes[ecast( MeshAttribute::UV )].format = VK_FORMAT_R32G32_SFLOAT;
	this->attributes[ecast( MeshAttribute::UV )].offset = offsetof( Attribute, uv );
	position_stride = sizeof( gr::vec3 );
	attribute_stride = sizeof( Attribute );

	info.size = indices.size() * sizeof( uint16_t );
	info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	ibo = device.create_buffer( info, indices.data() );
	ibo_offset = 0;
	index_type = VK_INDEX_TYPE_UINT16;
	count = indices.size();
	topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;

	bake();
}




void vox::World::generate()
{






}

*/

/*
void vox::CubitWorld::generate( const cb::Vec3 pos )
{

	vox::LPos startingPos = vox::LPos::from( pos );

	vox::CPos startingChunkPos = vox::CPos::from( startingPos );

	const auto chunk = m_chunks.getChunk(startingChunkPos);

	if( chunk.has_value() )
	{
		return;
	}

	generateChunk( startingChunkPos );



}



void vox::CubitWorld::generateChunk( const CPos pos )
{
	const auto chunkOpt = m_chunks.getChunk( pos );

	assert( chunkOpt.has_value() );

	const auto chunk = chunkOpt.value();

	Cubit::Single * pC = new Cubit::Single( 8 );

	Cubit::Ptr ptr( pC );


}
*/
vox::LPos vox::LPos::from( const vox::CPos cPos, const vox::GPos gPos )
{
	const auto chunkBase_gPos = GPos::from( cPos );

	const auto lPos = gPos - chunkBase_gPos;

	return lPos;
}

/*
vox::LPos::LPos( i32 n_x, i32 n_y, i32 n_z )
	:
	x( n_x ),
	y( n_y ),
	z( n_z )
{

}
*/

vox::LPos vox::GPos::operator -( const vox::GPos pos ) const
{
	return vox::LPos( x - pos.x, y - pos.y, z - pos.z );
}

vox::GPos vox::GPos::operator +( const vox::LPos pos ) const
{
	return vox::GPos( x + pos.x, y + pos.y, z + pos.z );
}

vox::GPos vox::GPos::operator +( const cb::Vec3i pos ) const
{
	return vox::GPos( x + pos.x, y + pos.y, z + pos.z );
}



vox::GPos vox::GPos::from( const CPos pos )
{
	// TODO CHUNK SIZE
	return GPos( pos.x * 16, pos.y * 16, pos.z * 16 );
}




void vox::CubitArr::set_slow( u16 v, LPos pos )
{

}

u16 vox::CubitArr::get_slow( LPos pos )
{
	return m_arr.m_arr[ m_arr.index( pos ) ];
}






/*

class ChunkMesh: public Granite::StaticMesh, public Granite::EventHandler
{
public:
	ChunkMesh()
	{
	}

	enum Faces
	{
		ePX = 1 << 0,
		eNX = 1 << 1,
		ePY = 1 << 2,
		eNY = 1 << 3,
		ePZ = 1 << 4,
		eNZ = 1 << 5,
	};

	void pushSingleCube( Vulkan::Device * const pDev, Faces faces, std::vector<float> * const pPos, std::vector<float> * const pAttr, std::vector<u16> * const pInd, const cb::Vec3 pos )
	{
		static const f32 N = 0;
		static const f32 P = 1;

		static const f32 positions[] = {
			// Right
			P, N, P,
			P, N, N,
			P, P, P,
			P, P, N,

			// Left
			N, N, N,
			N, N, P,
			N, P, N,
			N, P, P,

			// Top
			N, P, P,
			P, P, P,
			N, P, N,
			P, P, N,

			// Bottom
			N, N, N,
			P, N, N,
			N, N, P,
			P, N, P,

			// Near
			N, N, P,
			P, N, P,
			N, P, P,
			P, P, P,

			// Far
			P, N, N,
			N, N, N,
			P, P, N,
			N, P, N,
		};

		static const f32 attr[] = {
			// Right
			P, 0, 0, 0, 0, 0, N, 0, 0, P,
			P, 0, 0, 0, 0, 0, N, 0, P, P,
			P, 0, 0, 0, 0, 0, N, 0, 0, 0,
			P, 0, 0, 0, 0, 0, N, 0, P, 0,

			// Left
			N, 0, 0, 0, 0, 0, P, 0, 0, P,
			N, 0, 0, 0, 0, 0, P, 0, P, P,
			N, 0, 0, 0, 0, 0, P, 0, 0, 0,
			N, 0, 0, 0, 0, 0, P, 0, P, 0,

			// Top
			0, P, 0, 0, P, 0, 0, 0, 0, P,
			0, P, 0, 0, P, 0, 0, 0, P, P,
			0, P, 0, 0, P, 0, 0, 0, 0, 0,
			0, P, 0, 0, P, 0, 0, 0, P, 0,

			// Bottom
			0, N, 0, 0, P, 0, 0, 0, 0, P,
			0, N, 0, 0, P, 0, 0, 0, P, P,
			0, N, 0, 0, P, 0, 0, 0, 0, 0,
			0, N, 0, 0, P, 0, 0, 0, P, 0,

			// Near
			0, 0, P, 0, P, 0, 0, 0, 0, P,
			0, 0, P, 0, P, 0, 0, 0, P, P,
			0, 0, P, 0, P, 0, 0, 0, 0, 0,
			0, 0, P, 0, P, 0, 0, 0, P, 0,

			// Far
			0, 0, N, 0, N, 0, 0, 0, 0, P,
			0, 0, N, 0, N, 0, 0, 0, P, P,
			0, 0, N, 0, N, 0, 0, 0, 0, 0,
			0, 0, N, 0, N, 0, 0, 0, P, 0,
		};

		static const u16 indices[] = {
			0, 1, 2, 3, 2, 1,
			4, 5, 6, 7, 6, 5,
			8, 9, 10, 11, 10, 9,
			12, 13, 14, 15, 14, 13,
			16, 17, 18, 19, 18, 17,
			20, 21, 22, 23, 22, 21,
		};


		u32 curFace = 1 << 0;

		const u32 posStride = 3 * 4;
		const u32 attrStride = 10 * 4;
		const u32 indexStride = 6;

		for(i32 iFace = 0; iFace < 6; ++iFace )
		{
			if(curFace & faces)
			{
				const i32 posStart = posStride * iFace;
				const i32 posEnd = posStart + posStride;

				const i32 attrStart = attrStride * iFace;
				const i32 attrEnd = attrStart + attrStride;

				//const i32 indexStart = indexStride * i;
				//const i32 indexEnd = indexStart + indexStride;


				for(i32 iAttr = attrStart; iAttr < attrEnd; ++iAttr)
				{
					pAttr->push_back( attr[iAttr] );
				}

				const i32 indexStart = pPos->size() / 3;
				const i32 otherIndexStart = pInd->size();

				s_triangleCount += 2;

				for(i32 iIndex = 0; iIndex < 6; ++iIndex)
				{
					pInd->push_back( indices[iIndex] + indexStart );
				}

				for( i32 iPos = posStart; iPos<posEnd; ++iPos )
				{
					pPos->push_back( positions[iPos] + pos[iPos % 3] );
				}
			}

			curFace <<= 1;
		}




	}



	void cube( 
		Vulkan::Device * const pDev, 
		vox::CubitArr * const pCubit, 
		std::vector<float> * const pPositions, 
		std::vector<float> * const pAttr, 
		std::vector<u16> * const pIndices, 
		const vox::LPos pos, 
		const gr::vec3 worldPos, 
		const u16 posX,
		const u16 negX,
		const u16 posY,
		const u16 negY,
		const u16 posZ,
		const u16 negZ
	)
	{
		const i32 index = pCubit->m_arr.index( pos );

		const auto cur = pCubit->m_arr.m_arr[index];

		const auto l = cb::Vec3( pos.x, pos.y, pos.z );

		//If its air, skip
		if( !cur ) return;

		Faces faces = (Faces)0;

		faces = cast<Faces>( faces | ( Faces::ePX * cast<int>( true && cur != posX ) ) );
		faces = cast<Faces>( faces | ( Faces::eNX * cast<int>( true && cur != negX ) ) );

		faces = cast<Faces>( faces | ( Faces::ePY * cast<int>( true && cur != posY ) ) );
		faces = cast<Faces>( faces | ( Faces::eNY * cast<int>( true && cur != negY ) ) );

		faces = cast<Faces>( faces | ( Faces::ePZ * cast<int>( true && cur != posZ ) ) );
		faces = cast<Faces>( faces | ( Faces::eNZ * cast<int>( true && cur != negZ ) ) );

		const auto h = l + cb::Vec3( 1, 1, 1 );

		if( faces )
		{
			int dummy = 0;
		}

		if( faces )
		{
			const auto startIndex = cast<u16>( pPositions->size() );

			pushSingleCube( pDev, faces, pPositions, pAttr, pIndices, cb::Vec3( worldPos.x + pos.x, worldPos.y + pos.y, worldPos.z + pos.z ) );
		}

	}



	i32 fill( vox::Plane<vox::Cubit> * pPlane, Vulkan::Device * const pDev, Granite::Scene * const pScene, vox::CubitArr * const pCubit, const vox::CPos chunkPos, const gr::vec3 worldPos )
	{
		std::vector<float> positions;
		//std::vector<float> attributes;
		std::vector<float> attr;
		std::vector<u16> indices;

		material = gr::StockMaterials::get().get_checkerboard();
		static_aabb = gr::AABB( gr::vec3( -1000 ) + worldPos, gr::vec3( 1000 ) + worldPos );

		const auto uv00 = gr::vec2( 0, 0 );
		const auto uv01 = gr::vec2( 0, 1 );
		const auto uv10 = gr::vec2( 1, 0 );
		const auto uv11 = gr::vec2( 1, 1 );

		for( i32 z = 1; z < pCubit->k_edgeSize.size - 1; ++z )
		{
			for( i32 y = 1; y < pCubit->k_edgeSize.size - 1; ++y )
			{
				for( i32 x = 1; x < pCubit->k_edgeSize.size - 1; ++x )
				{
					const auto pos = vox::LPos(x, y, z);

					const u16 posX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 1, pos.y + 0, pos.z + 0 )];
					const u16 negX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x - 1, pos.y + 0, pos.z + 0 )];
					const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 1, pos.z + 0 )];
					const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y - 1, pos.z + 0 )];
					const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z + 1 )];
					const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z - 1 )];

					cube(pDev, pCubit, &positions, &attr, &indices, pos, worldPos, posX, negX, posY, negY, posZ, negZ );
					
				}
			}
		}

		const i32 zSmall = 0;
		const i32 zBig = pCubit->k_edgeSize.size - 1;

		const auto vPosX = cb::Vec3i( 1, 0, 0 );
		const auto vNegX = cb::Vec3i(-1, 0, 0 );
		const auto vPosY = cb::Vec3i( 0, 1, 0 );
		const auto vNegY = cb::Vec3i( 0,-1, 0 );
		const auto vPosZ = cb::Vec3i( 0, 0, 1 );
		const auto vNegZ = cb::Vec3i( 0, 0,-1 );

		for( i32 y = 0; y < pCubit->k_edgeSize.size; ++y )
		{
			for( i32 x = 0; x < pCubit->k_edgeSize.size; ++x )
			{
				{
					const auto lPos = vox::LPos( x, y, zSmall );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pPlane->get_slow( gPos + vPosY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pPlane->get_slow( gPos + vNegY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pPlane->get_slow( gPos + vPosZ ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pPlane->get_slow( gPos + vNegZ ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}

				{
					const auto lPos = vox::LPos( x, y, zBig );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pPlane->get_slow( gPos + vPosY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pPlane->get_slow( gPos + vNegY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pPlane->get_slow( gPos + vPosZ ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pPlane->get_slow( gPos + vNegZ ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}


			}
		}

		const i32 ySmall = 0;
		const i32 yBig = pCubit->k_edgeSize.size - 1;

		for( i32 z = 1; z < pCubit->k_edgeSize.size - 1; ++z )
		{
			for( i32 x = 0; x < pCubit->k_edgeSize.size - 0; ++x )
			{
				{
					const auto lPos = vox::LPos( x, ySmall, z );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pPlane->get_slow( gPos + vPosY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pPlane->get_slow( gPos + vNegY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}

				{
					const auto lPos = vox::LPos( x, yBig, z );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pPlane->get_slow( gPos + vPosY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pPlane->get_slow( gPos + vNegY ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}


			}
		}



		const i32 xSmall = 0;
		const i32 xBig = pCubit->k_edgeSize.size - 1;

		for( i32 z = 1; z < pCubit->k_edgeSize.size - 1; ++z )
		{
			for( i32 y = 1; y < pCubit->k_edgeSize.size - 1; ++y )
			{
				{
					const auto lPos = vox::LPos( xSmall, y, z );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}

				{
					const auto lPos = vox::LPos( xBig, y, z );
					const auto gPos = chunkPos + lPos;

					const u16 posX = pPlane->get_slow( gPos + vPosX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 1, lPos.y + 0, lPos.z + 0 )];
					const u16 negX = pPlane->get_slow( gPos + vNegX ); //pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x - 1, lPos.y + 0, lPos.z + 0 )];
					const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 1, lPos.z + 0 )];
					const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y - 1, lPos.z + 0 )];
					const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z + 1 )];
					const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( lPos.x + 0, lPos.y + 0, lPos.z - 1 )];

					cube( pDev, pCubit, &positions, &attr, &indices, lPos, worldPos, posX, negX, posY, negY, posZ, negZ );
				}


			}
		}




		/*
		{
			auto negX = chunkPos;
			negX += vox::CPos( -1, 0, 0 );

			const auto chunkNegXOpt = pPlane->get( negX );

			const i32 x = 0;

			if( chunkNegXOpt.has_value() )
			{
				const auto chunkNegX = chunkNegXOpt.value();

				for( i32 z = 0; z < pCubit->k_edgeSize.size - 1; ++z )
				{
					for( i32 y = 0; y < pCubit->k_edgeSize.size - 1; ++y )
					{
						const auto pos = vox::LPos( x, y, z );

						const u16 posX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 1, pos.y + 0, pos.z + 0 )];
						//const u16 negX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x - 1, pos.y + 0, pos.z + 0 )];
						const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 1, pos.z + 0 )];
						const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y - 1, pos.z + 0 )];
						const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z + 1 )];
						const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z - 1 )];

						auto otherPos = vox::LPos( 15, y, z );

						const u16 negX = chunkNegX->get_slow( otherPos );

						cube( pDev, pCubit, &positions, &attr, &indices, pos, worldPos, posX, negX, posY, negY, posZ, negZ );
					}
				}
			}
			else
			{
				for( i32 z = 0; z < pCubit->k_edgeSize.size - 1; ++z )
				{
					for( i32 y = 0; y < pCubit->k_edgeSize.size - 1; ++y )
					{
						const auto pos = vox::LPos( x, y, z );

						const u16 posX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 1, pos.y + 0, pos.z + 0 )];
						//const u16 negX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x - 1, pos.y + 0, pos.z + 0 )];
						const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 1, pos.z + 0 )];
						const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y - 1, pos.z + 0 )];
						const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z + 1 )];
						const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z - 1 )];

						const u16 negX = 0;

						cube( pDev, pCubit, &positions, &attr, &indices, pos, worldPos, posX, negX, posY, negY, posZ, negZ );
					}
				}
			}
		}

		{
			auto posX = chunkPos;
			posX += vox::CPos( 1, 0, 0 );

			const auto chunkNegXOpt = pPlane->get( posX );

			const i32 x = 15;

			if( chunkNegXOpt.has_value() )
			{
				const auto chunkNegX = chunkNegXOpt.value();

				for( i32 z = 0; z < pCubit->k_edgeSize.size - 1; ++z )
				{
					for( i32 y = 0; y < pCubit->k_edgeSize.size - 1; ++y )
					{
						const auto pos = vox::LPos( x, y, z );

						//const u16 posX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 1, pos.y + 0, pos.z + 0 )];
						const u16 negX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x - 1, pos.y + 0, pos.z + 0 )];
						const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 1, pos.z + 0 )];
						const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y - 1, pos.z + 0 )];
						const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z + 1 )];
						const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z - 1 )];

						auto otherPos = vox::LPos( 0, y, z );

						const u16 posX = chunkNegX->get_slow( otherPos );

						cube( pDev, pCubit, &positions, &attr, &indices, pos, worldPos, posX, negX, posY, negY, posZ, negZ );
					}
				}
			}
			else
			{
				for( i32 z = 0; z < pCubit->k_edgeSize.size - 1; ++z )
				{
					for( i32 y = 0; y < pCubit->k_edgeSize.size - 1; ++y )
					{
						const auto pos = vox::LPos( x, y, z );

						const u16 posX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 1, pos.y + 0, pos.z + 0 )];
						//const u16 negX = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x - 1, pos.y + 0, pos.z + 0 )];
						const u16 posY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 1, pos.z + 0 )];
						const u16 negY = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y - 1, pos.z + 0 )];
						const u16 posZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z + 1 )];
						const u16 negZ = pCubit->m_arr.m_arr[pCubit->m_arr.index( pos.x + 0, pos.y + 0, pos.z - 1 )];

						const u16 negX = 0;

						cube( pDev, pCubit, &positions, &attr, &indices, pos, worldPos, posX, negX, posY, negY, posZ, negZ );
					}
				}
			}
		}
		* /

		if(positions.size() == 0) 
			return 0;

		Vulkan::BufferCreateInfo info = {};
		info.size = positions.size() * sizeof( float );
		info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		info.domain = Vulkan::BufferDomain::Device;
		vbo_position = pDev->create_buffer( info, positions.data() );

		info.size = attr.size() * sizeof( float );
		vbo_attributes = pDev->create_buffer( info, attr.data() );

		attributes[cast<i32>( gr::MeshAttribute::Position )].offset = 0;
		attributes[cast<i32>( gr::MeshAttribute::Position )].format = VK_FORMAT_R32G32B32_SFLOAT;

		attributes[cast<i32>( gr::MeshAttribute::Normal )].offset = 0;
		attributes[cast<i32>( gr::MeshAttribute::Normal )].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributes[cast<i32>( gr::MeshAttribute::Tangent )].offset = 4;
		attributes[cast<i32>( gr::MeshAttribute::Tangent )].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributes[cast<i32>( gr::MeshAttribute::UV )].offset = 8;
		attributes[cast<i32>( gr::MeshAttribute::UV )].format = VK_FORMAT_R32G32_SFLOAT;
		position_stride = sizeof( gr::vec3 );
		attribute_stride = sizeof( float ) * 10;

		info.size = indices.size() * sizeof( uint16_t );
		info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		ibo = pDev->create_buffer( info, indices.data() );
		ibo_offset = 0;
		index_type = VK_INDEX_TYPE_UINT16;
		count = indices.size();
		topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		bake();

		return positions.size();
	}

};

*/




void vox::Cubit::genWorld( Plane<Cubit> * pPlane, const CPos pos )
{

}


/*
void vox::Cubit::genGeo( Plane<Cubit> * pPlane, Vulkan::Device * const pDev, Granite::Scene * const pScene, const CPos pos )
{
}
*/

static SimplexNoise noise;
static f32 s_fractalMultXY = 1.0f / 256.0f;
static f32 s_fractalMultZ  = 1.0f / 64.0f;


void vox::CubitArr::genWorld( Plane<Cubit> * pPlane, const CPos pos )
{
	for( i32 z = 0; z < k_edgeSize.size; ++z )
	{
		const i32 cubeWorldZ = m_gPos.z + z;
		const f32 worldZ = cubeWorldZ;

		const f32 perlinZ = worldZ * s_fractalMultZ;

		for( i32 y = 0; y < k_edgeSize.size; ++y )
		{
			const i32 cubeWorldY = m_gPos.y + y;
			const f32 worldY = cubeWorldY;

			const f32 perlinY = worldY * s_fractalMultXY;

			for( i32 x = 0; x < k_edgeSize.size; ++x )
			{
				const i32 cubeWorldX = m_gPos.x + x;
				const f32 worldX = cubeWorldX;

				const f32 perlinX = worldX * s_fractalMultXY;

				const i32 index = m_arr.index( x, y, z );

				const f32 rawPerlinValue = noise.fractal( 4, perlinX, perlinY, perlinZ );

				const f32 perlinValue = rawPerlinValue + perlinZ - 1;



				m_arr.m_arr[index] = perlinValue < 0;


				/*
				if(worldZ > 8) 
				{
					m_arr.m_arr[index] = 0;
				}
				else if( worldZ > 4 )
				{
					m_arr.m_arr[index] = ( (cubeWorldX & 4) + (cubeWorldY & 6) ) > 0;
				}
				else
				{
					m_arr.m_arr[index] = 1;
				}
				*/
			}
		}
	}
}

/*

void vox::CubitArr::genGeo( Plane<Cubit> * pPlane, Vulkan::Device * const pDev, Granite::Scene * const pScene, const CPos pos )
{
	const auto pGeo = new ChunkMesh();

	const auto worldPos = GPos::from( pos );
	const auto wP = gr::vec3( worldPos.x, worldPos.y, worldPos.z ) ;

	const auto vertCount = pGeo->fill( pPlane, pDev, pScene, this, pos, wP );

	if( vertCount == 0 )
		return;

	m_geo = pGeo;

	auto node = pScene->create_node();

	auto root = pScene->get_root_node();


	root->add_child( node );

	//node->transform.translation.x = rand() & 511;
	//node->transform.translation.y = rand() & 511;
	//node->transform.translation.z = rand() & 511;

	auto entity = pScene->create_renderable( m_geo, node.get() );

}

*/

void vox::CubitPlane::genWorld( const cb::Vec3 pos )
{
	//const auto cp = LPos::from( chunkPos );
	//const auto chunkWS = cb::Vec3( cp.x, cp.y, cp.z );
	const auto gPos = GPos::from( pos );

	const auto v = CPos::from( gPos );

	const cb::Vec3i startingChunkPos( v.x, v.y, v.z );






	for( i32 z = 1; z < 8; ++z )
	{
		for( i32 y = 1; y < 10; ++y )
		{
			for( i32 x = 1; x < 50; ++x )
			{
			//async::parallel_for( async::irange( 1, 100 ), [ startingChunkPos, z, y, this ]( int x ) {
				auto cbChunkPos = startingChunkPos;

				cbChunkPos += cb::Vec3i( x, y, z );

				const CPos chunkPos( cbChunkPos.x, cbChunkPos.y, cbChunkPos.z );


				//auto chunk = get( chunkPos );


				const auto cubit = TChunk::Ptr( new CubitArr( chunkPos ) );

				cubit->genWorld( this, chunkPos );

				//if( !chunk.has_value() ) chunk = cubit

				const auto hashFn = std::hash<CPos>();
				const auto hash = hashFn( chunkPos );


				m_sparse[chunkPos] = cubit;

				//cubit->genGeo( this, pDev, pScene, chunkPos );
			//} );
			}
		}
	}

	//int dummy = 0;

}

/*
void vox::CubitPlane::genGeo( Vulkan::Device * const pDev, Granite::Scene * const pScene, const cb::Vec3 pos )
{

	for(auto it = m_sparse.begin(); it != m_sparse.end(); ++it)
	{
		it->second->genGeo(this, pDev, pScene, it->first);
	}



}
*/






template< typename T >
class Value
{
public:

	typedef typename T TYPE;

	Value( const T &v )
		:
		m_v( v )
	{
	}

	explicit operator T() const
	{
		return m_v;
	}

	T operator =( const T &v )
	{
		m_v = v;
		return m_v;
	}

private:
	T m_v;
};

template< typename SUPER >
class ValuePrint : public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValuePrint( const T &v )
		:
		SUPER( v )
	{
	}

	explicit operator T() const
	{
		return cast<T>(*(SUPER *)this);
	}

	T operator =( const T &v )
	{
		const T &oldVal = cast<T>(*this);

		std::cout << "Old value:" << oldVal << std::endl;
		const auto newVal = SUPER::operator =(v);
		std::cout << "New value:" << newVal << std::endl;

		return newVal;
	}


private:

};

template< typename T >
T clamp(T v, T min, T max)
{
	return std::min( max, std::max(v, min) );
}

template< class SUPER, typename SUPER::TYPE min, typename SUPER::TYPE max >
class ValueRange: public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValueRange( const T &v )
		:
		SUPER( v )
	{
	}

	explicit operator T() const
	{
		const auto v = cast<T>( *(SUPER *)this );
		return clamp(v, min, max);
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		return clamp( newVal, min, max );
	}


private:

};


template< typename SUPER >
class ValueRangeFloat: public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValueRangeFloat( const T &v )
		:
		SUPER( v )
	{
	}

	T m_min;
	T m_max;

	ValueRangeFloat<SUPER> &initRangeFloat(const T min, const T max)
	{
		m_min = min;
		m_max = max;
		return *this;
	}

	explicit operator T() const
	{
		const auto v = cast<T>( *(SUPER *)this );
		return clamp( v, m_min, m_max );
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		return clamp( newVal, m_min, m_max );
	}


private:

};


template< typename SUPER >
class ValueTrack: public SUPER
{
public:

	typedef typename SUPER::TYPE T;

	ValueTrack( const T &v )
		:
		SUPER( v )
	{
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		m_changedSinceChecked = true;
		return newVal;
	}

	bool hasChanged()
	{
		const auto changed = m_changedSinceChecked;
		m_changedSinceChecked = false;
		return changed;
	}

private:
	bool m_changedSinceChecked = false;
};



template< typename SUPER >
class ValueOnChange: public SUPER
{
public:

	typedef typename SUPER::TYPE T;

	ValueOnChange( const T &v )
		:
		SUPER( v )
	{
	}

	ValueOnChange<SUPER> &initOnChange( std::function<void( T, T )> fn )
	{
		m_fn = fn;
		return *this;
	}

	T operator =( const T &v )
	{
		const auto oldV = cast<T>( *(SUPER *)this );

		const auto newV = SUPER::operator =( v );

		m_fn( oldV, newV );

		return newV;
	}

private:
	std::function<void(T, T)> m_fn;
};

template< class TValue >
void doSomething( TValue &v )
{

	const auto v_1 = cast<TValue::TYPE>(v);

	std::cout << "Do something on " << v_1 << std::endl;

}


void vox::testVox()
{

	//CubitPlane plane;

	//plane.genWorld( cb::Vec3( 55.4f, 72.3f, 14.4f ) );



}


void testDatatypes()
{
	//*
	/*
	TPos<0> pos;
	TPos<0> pos_2;

	TPos<1> cubePos;

	pos_2 = pos;

	cubePos = pos.up();

	pos_2 = cubePos.down();
	*/

	ValuePrint<ValueRange<ValueTrack<Value<i32>>, 10, 20>> val( 100 );

	const auto change_0 = val.hasChanged();

	val = 200;

	const auto change_1 = val.hasChanged();

	const auto change_2 = val.hasChanged();

	const auto v_0 = cast<i32>( val );

	val = -100;

	doSomething( val );


	const auto v_1 = cast<i32>( val );


	auto val_f_1 = ValuePrint<ValueOnChange<ValueRangeFloat<ValueTrack<Value<f32>>>>>( 100.0f );

	//*
	val_f_1.initOnChange( []( f32 oldV, f32 newV ) {
		std::cout << "Value is changing from " << oldV << " " << newV << std::endl;
	} ).initRangeFloat( 35, 75 );
	//*/

	doSomething( val_f_1 );

	//auto connect = FSMRetry<10, FSMExponentialBackoff<FSMTimeout<1000, <FSMState>>>>();



	val_f_1 = -50;


	doSomething( val_f_1 );

	/*
	auto port = ValueOnChange<ValueRange<Value<i32>, 1024, 65536>>>( 100 );

	port.ValueOnChange::init( []( i32 oldV, i32 newV ) {

		//kill current listen port, then remake it

	} );
	*/



	//*/

}

#include <string>

template <typename Value, typename Struct>
struct param
{
	Value Struct::*pmd;
	Value value;

	void set( Struct &s )
	{
		s.*pmd = std::move( value );
	}
};

template <typename Value, typename Struct>
param<Value, Struct> make_param( Value Struct::*pmd, Value value )
{
	return param<Value, Struct>{pmd, value};
}

template <typename T, typename... Params>
T copy( const T &val, Params &&...params )
{
	T value_copy = val;

	( params.set( value_copy ), ... );

	return value_copy;
}

struct person {
	std::string name;
	int age;
};

void test()
{
	const person p1{ "name1", 25 };
	const person p2 = copy( p1,
		make_param( &person::name, std::string( "name2" ) ) );
}
