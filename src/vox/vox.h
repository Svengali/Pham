//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once


#include <optional>


typedef std::optional<int> OptTest;


namespace vox
{

template<i32 t_size>
class ChunkSize
{
public:

	static constexpr i32 size = t_size;

	static constexpr f32 fSize = (f32)size;

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

namespace vox
{


template<typename TSUB, typename TIN, i32 k_edgeSizeIn>
class Chunk
{
public:

	//I generally dont like to put APIs in headers like this, but these need to be relative to chunks, as well as 
	//inlined.
	typedef TIN T;

	static const ChunkSize<k_edgeSizeIn> kChunkSize;

	static const i32 k_edgeSize = k_edgeSizeIn;
	static const i32 k_platSize = k_edgeSize * k_edgeSize;
	static const i32 k_chunkSize = k_edgeSize * k_platSize;

	typedef std::shared_ptr<TSUB> Ptr;
	
	// PORT FIX UE4
	typedef std::optional<Ptr>    Opt;

	//These are now defined Chunk type relative which means theyre always correct with respect to edge size
	class LPos;
	class GPos;
	class CPos;

	class GPos: public cb::Vec3i
	{
	public:
		using cb::Vec3i::Vec3i;

		// DOC eps?  I presume its to make sure 
		static GPos from( const cb::Vec3 pos, const float eps = 1.0f / (f32)k_edgeSizeIn )
		{
			const auto untrans = pos - FramePlane<Cubit>::m_translation;

			const auto untransUnscale  = cb::Vec3(
				untrans.x * FramePlane<Cubit>::m_invScaleFactor.x,
				untrans.y * FramePlane<Cubit>::m_invScaleFactor.y,
				untrans.z * FramePlane<Cubit>::m_invScaleFactor.z );

			return GPos( cast<i32>( untransUnscale.x + eps ), cast<i32>( untransUnscale.y + eps ), cast<i32>( untransUnscale.z + eps ) );
		}


		LPos operator -( const GPos pos ) const
		{
			return LPos( x - pos.x, y - pos.y, z - pos.z );
		}

		//*
		GPos operator +( const LPos pos ) const
		{
			return GPos( x + pos.x, y + pos.y, z + pos.z );
		}

		GPos operator +( const cb::Vec3i pos ) const
		{
			return GPos( x + pos.x, y + pos.y, z + pos.z );
		}
		//*/

		static GPos from( const CPos pos )
		{
			return GPos( pos.x * k_edgeSizeIn, pos.y * k_edgeSizeIn, pos.z * k_edgeSizeIn );
		}


		cb::Vec3 toWorld() const
		{
			const auto worldPosRaw = cb::Vec3( (f32)x, (f32)y, (f32)z );

			const auto worldPosScaled = cb::Vec3(
				worldPosRaw.x * FramePlane<Cubit>::m_scaleFactor.x,
				worldPosRaw.y * FramePlane<Cubit>::m_scaleFactor.y,
				worldPosRaw.z * FramePlane<Cubit>::m_scaleFactor.z );

			const auto worldPos = worldPosScaled + FramePlane<Cubit>::m_translation;

			return worldPos;
		}

		static GPos from( const CPos cPos, const LPos lPos )
		{
			return GPos( lPos.x + cPos.x * k_edgeSizeIn, lPos.y + cPos.y * k_edgeSizeIn, lPos.z + cPos.z * k_edgeSizeIn );
		}


	};

	class LPos: public cb::Vec3i
	{
	public:
		using cb::Vec3i::Vec3i;

		//LPos(i32 x, i32 y, i32 z);

		//Get the relative 
		static LPos from( const CPos cPos, const GPos gPos )
		{
			const auto chunkBase_gPos = GPos::from( cPos );

			const auto lPos = gPos - chunkBase_gPos;

			return lPos;
		}

		__forceinline static const LPos MakeMin( const LPos &a, const LPos &b )
		{
			ASSERT( a.IsValid() && b.IsValid() );
			return LPos(
				MIN( a.x, b.x ),
				MIN( a.y, b.y ),
				MIN( a.z, b.z )
			);
		}
		__forceinline static const LPos MakeMax( const LPos &a, const LPos &b )
		{
			ASSERT( a.IsValid() && b.IsValid() );
			return LPos(
				MAX( a.x, b.x ),
				MAX( a.y, b.y ),
				MAX( a.z, b.z )
			);
		}

	};

	class CPos: public cb::Vec3i
	{

	public:
		using cb::Vec3i::Vec3i;

		using cb::Vec3i::operator -;
		using cb::Vec3i::operator +;


		bool operator ==( const CPos &r )
		{
			return x == r.x && y == r.y && z == r.z;
		}

		GPos operator +( const LPos pos ) const
		{
			const auto gPos = GPos::from( *this );

			return gPos + pos;
		}

		bool operator <=( const CPos rhs ) const
		{
			return ( x <= rhs.x ) & ( y <= rhs.y ) & ( z <= rhs.z );
		}

		bool operator >=( const CPos rhs ) const
		{
			return ( x >= rhs.x ) & ( y >= rhs.y ) & ( z >= rhs.z );
		}

		static CPos from( const GPos pos )
		{
			return CPos( ( pos.x - 0 ) / 32, ( pos.y - 0 ) / 32, ( pos.z - 0 ) / 32 );
		}

	};


	static inline const LPos LMax = LPos( k_edgeSize, k_edgeSize, k_edgeSize );



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



template <typename TCHUNK>
struct PosHash
{
	static const size_t bucket_size = 2;

	std::size_t operator()( const typename TCHUNK::CPos &k ) const
	{
		auto crc = cb::CRC();

		crc.AddL( k.x );
		crc.AddL( k.y );
		crc.AddL( k.z );

		return crc.GetHash();
	}

	bool operator()( const typename TCHUNK::CPos &l, const typename TCHUNK::CPos &r ) const
	{
		const auto lHash = ( *this )( l );
		const auto rHash = ( *this )( r );

		return lHash < rHash;
	}

};



template<typename TCHUNK>
class Storage
{
public:
	//Unsure if I want these
	//virtual void set_slow( T v, LPos pos ) = 0;
	//virtual T get_slow( LPos pos ) = 0;

};

template<typename TCHUNK>
class StorageArr: Storage<TCHUNK>
{
public:
	
	StorageArr() {}


	//virtual void set_slow( T v, LPos pos ) = 0;
	//virtual T get_slow( LPos pos ) = 0;

	i32 index( const i32 x, const i32 y, const i32 z ) const
	{
		return z * TCHUNK::k_platSize + y * TCHUNK::k_edgeSize + x;
	}

	i32 index( typename TCHUNK::LPos pos ) const
	{
		return pos.z * TCHUNK::k_platSize + pos.y * TCHUNK::k_edgeSize + pos.x;
	}

	std::array<typename TCHUNK::T, TCHUNK::k_chunkSize> m_arr;
};


//Like an existance plane
template<typename TCHUNK>
class Plane
{
public:
	typedef TCHUNK TChunk;

	typename TCHUNK::Opt get(const typename TCHUNK::CPos pos)
	{
		const auto it = m_sparse.find(pos);

		if( it != m_sparse.end() ) return it->second;

		return TCHUNK::Opt();
	}


	typename TCHUNK::Opt set( const typename TCHUNK::CPos pos, typename TCHUNK::Ptr ch )
	{
		const auto it = m_sparse.find( pos );

		auto chunkOpt = TCHUNK::Opt();

		if( it != m_sparse.end() ) chunkOpt = it->second;

		m_sparse[pos] = ch;

		return chunkOpt;
	}

	typename TCHUNK::T get_slow( const typename TCHUNK::GPos pos )
	{
		const auto cPos = typename TCHUNK::CPos::from( pos );

		const auto TCHUNKOpt = get( cPos );

		if( TCHUNKOpt.has_value() )
		{
			const auto tcVal = TCHUNKOpt.value();

			const auto lPos = typename TCHUNK::LPos::from( cPos, pos );

			if( (lPos.x < 0) | (lPos.x >= TCHUNK::k_edgeSize ) |
					(lPos.y < 0) | (lPos.y >= TCHUNK::k_edgeSize ) |
					(lPos.z < 0) | (lPos.z >= TCHUNK::k_edgeSize ) )
			{
				lprinterr( "Local pos is (%s)\n", lPos );
			}

			return tcVal->get_slow( lPos );
		}

		return TCHUNK::T(0);
	}



	std::hash_map<typename TCHUNK::CPos,typename TCHUNK::Ptr, PosHash<TCHUNK>> m_sparse;

protected:

};


//Like an existance plane
template<typename TCHUNK>
class FramePlane: public Plane<TCHUNK>
{
public:

	
	typename TChunk::GPos from( const cb::Vec3 worldPos )
	{
		const auto trans = worldPos - m_translation;

		const auto scaled= cb::Vec3( trans.x * m_invScaleFactor.x, trans.y * m_invScaleFactor.y, trans.z * m_invScaleFactor.z );

		return typename TChunk::GPos( (i32)scaled.x, (i32)scaled.y, (i32)scaled.z );
	}

	static cb::Vec3 m_translation; // = cb::Vec3( 0.0f, 0.0f, 0.0f );
	static cb::Vec3 m_scaleFactor; // = cb::Vec3( 1.0f, 1.0f, 1.0f );
	static cb::Vec3 m_invScaleFactor;

protected:

};











void testVox();

}

