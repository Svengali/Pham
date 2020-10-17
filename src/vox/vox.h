//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once


class ChunkMesh;


namespace vox
{

class LPos;
class GPos;
class CPos;

template<i32 t_size>
class ChunkSize
{
public:

	static constexpr i32 size = t_size;

	const f32 fSize = cast<f32>(size);

	/*
	i32 operator *( const i32 r ) const
	{
		return size * r;
	}

	i32 operator *( const ChunkSize<t_size> r ) const
	{
		return size * r.size;
	}
	*/
};


// TODO .:. Should these be in Chunk?  Most likely
// TODO .:. A pos is connected to a particular CPos.  Dont think we can represent that in C++
class GPos: public cb::Vec3i
{
public:
	using cb::Vec3i::Vec3i;

	// DOC eps?  I presume its to make sure 
	static GPos from( const cb::Vec3 pos, const float eps = 1.0f / 32.0f )
	{
		return GPos( pos.x + eps, pos.y + eps, pos.z + eps );
	}

	GPos operator +(const LPos pos) const;

	LPos operator -( const GPos pos ) const;

	GPos operator +( const cb::Vec3i pos ) const;

	static GPos from( const CPos pos );
	static GPos from( const CPos cPos, const LPos lPos );
};

// TODO .:. Should these be in Chunk?  Most likely
// TODO .:. A local pos is connected to a particular CPos.  Dont think we can represent that in C++
class LPos: public cb::Vec3i
{
public:
	using cb::Vec3i::Vec3i;

	//LPos(i32 x, i32 y, i32 z);

	//Get the relative 
	static LPos from( const vox::CPos cPos, const vox::GPos gPos );
};


class CPos: public cb::Vec3i
{

public:
	using cb::Vec3i::Vec3i;

	bool operator ==( const vox::CPos& r )
	{
		return x == r.x && y == r.y && z == r.z;
	}

	GPos operator +(const LPos pos) const
	{
		const auto gPos = GPos::from(*this);

		return gPos + pos;
	}


	static CPos from( const GPos pos )
	{
		return CPos( (pos.x - 0) / 16, (pos.y - 0 ) / 16, (pos.z - 0 ) / 16 );
	}

};


/*
template<i32 t_level>
class TPos: public cb::Vec3i
{
public:

	static const i32 k_level = t_level;

	using cb::Vec3i::Vec3i;


	TPos<t_level - 1> down()
	{
		return TPos<t_level - 1>( x * 16, y * 16, z * 16 );
	}

	TPos<t_level + 1> up( )
	{
		return TPos<t_level + 1>( x / 16, y / 16, z / 16 );
	}

};
*/








}

namespace std
{
template <>
struct hash<vox::CPos>
{
	static const size_t bucket_size = 16;

	std::size_t operator()( const vox::CPos& k ) const
	{
		auto crc = cb::CRC();

		crc.AddL( k.x );
		crc.AddL( k.y );
		crc.AddL( k.z );

		return crc.GetHash();
	}

	bool operator()( const vox::CPos& l, const vox::CPos& r ) const
	{
		const auto lHash = ( *this )( l );
		const auto rHash = ( *this )( r );

		return lHash < rHash;
	}

};

}


namespace vox
{


template<typename TSUB, typename TIN, i32 k_edgeSizeIn>
class Chunk
{
public:
	typedef TIN T;

	static const ChunkSize<k_edgeSizeIn> k_edgeSize;

	static const i32 k_platSize = k_edgeSize.size * k_edgeSize.size;
	static const i32 k_chunkSize = k_edgeSize.size * k_platSize;

	typedef std::shared_ptr<TSUB> Ptr;
	typedef std::optional<Ptr>    Opt;


	Chunk(CPos pos)
		:
		m_cPos( pos ),
		m_gPos( GPos::from( m_cPos ) ),
		m_aabb( )
	{
	}

	virtual void set_slow( T v, LPos pos ) = 0;
	virtual T get_slow( LPos pos ) = 0;

	const CPos m_cPos;
	const GPos m_gPos;

	const cb::AxialBox m_aabb;


private:


};



template<typename TCHUNK>
class Storage
{
public:
	//virtual void set_slow( T v, LPos pos ) = 0;
	//virtual T get_slow( LPos pos ) = 0;

};

template<typename TCHUNK>
class StorageArr: Storage<TCHUNK>
{
public:

	//virtual void set_slow( T v, LPos pos ) = 0;
	//virtual T get_slow( LPos pos ) = 0;

	i32 index( const i32 x, const i32 y, const i32 z ) const
	{
		return z * TCHUNK::k_platSize + y * TCHUNK::k_edgeSize.size + x;
	}

	i32 index( LPos pos ) const
	{
		return pos.z * TCHUNK::k_platSize + pos.y * TCHUNK::k_edgeSize.size + pos.x;
	}

	std::array<typename TCHUNK::T, TCHUNK::k_chunkSize> m_arr;
};

/*
template<typename CHUNK>
class ChunkHolder: public Chunk<ChunkHolder<CHUNK>, typename CHUNK::Ptr, 16>
{
};
*/

class ChunkMesh
{
public:
	typedef std::shared_ptr<ChunkMesh> Ptr;
	typedef std::optional<Ptr>    Opt;

	virtual ~ChunkMesh()
	{

	}

	virtual void release() = 0;

};

//Like an existance plane
template<typename CHUNK>
class Plane
{
public:
	typedef CHUNK TChunk;



	typename CHUNK::Opt get(const CPos pos)
	{
		const auto it = m_sparse.find(pos);

		if( it != m_sparse.end() ) return it->second;

		return CHUNK::Opt();
	}


	typename CHUNK::Opt set( const CPos pos, typename CHUNK::Ptr ch )
	{
		const auto it = m_sparse.find( pos );

		auto oldChunk = CHUNK::Opt();

		if( it != m_sparse.end() ) oldChunk = it->second;

		m_sparse[pos] = ch;

		return oldChunk;
	}

	typename CHUNK::T get_slow( const GPos pos )
	{
		const auto cPos = CPos::from( pos );

		const auto chunkOpt = get( cPos );

		if( chunkOpt.has_value() )
		{
			const auto chunk = chunkOpt.value();

			const auto lPos = LPos::from( cPos, pos );

			if (lPos.x < 0 || lPos.x > 15 ||
				lPos.y < 0 || lPos.y > 15 || 
				lPos.z < 0 || lPos.z > 15 )
			{
				int dummy = 0;
			}

			return chunk->get_slow( lPos );
		}

		return CHUNK::T();
	}

	typename void set_slow( const GPos pos, typename CHUNK::T v )
	{
	}




protected:

	std::hash_map<CPos,typename CHUNK::Ptr, std::hash<CPos>> m_sparse;


};

















class Cubit: public Chunk<Cubit, u16, 16>
{
public:

	using Chunk::Chunk;

	virtual void genWorld( Plane<Cubit> * pPlane, const CPos pos );
	//virtual void genGeo( Plane<Cubit> * pPlane, Vulkan::Device * const pDev, Granite::Scene * const pScene, const CPos pos );

protected:
	//gr::AbstractRenderableHandle m_geo;
};

class CubitArr: public Cubit
{
public:

	using Cubit::Cubit;

	virtual void set_slow( u16 v, LPos pos ) override;
	virtual u16 get_slow( LPos pos ) override;

	virtual void genWorld( Plane<Cubit> * pPlane, CPos pos ) override;
	//virtual void genGeo( Plane<Cubit> * pPlane, Vulkan::Device * const pDev, Granite::Scene * const pScene, const CPos pos ) override;


	StorageArr<Cubit> m_arr;


private:

	friend class DGChunkMesh;

};

class CubitPlane: public Plane<Cubit>
{
public:



	virtual void genWorld( const cb::Vec3 pos );
	//virtual void genGeo( Vulkan::Device * const pDev, Granite::Scene * const pScene, const cb::Vec3 pos );





private:
};






void testVox();

}

