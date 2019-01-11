//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once

namespace map
{

class ChunkSize
{
public:

	constexpr ChunkSize( const int32_t size )
		:
		m_size( size )
	{
	}

	constexpr int32_t size() const
	{
		return m_size;
	}

private:
	int32_t m_size;
};


constexpr static ChunkSize k_standardSideSize = ChunkSize( 64 );






template<typename T, int32_t k_sideSize = k_standardSideSize.size()>
class Chunk
{
public:
    static constexpr uint32_t k_tileCount = k_sideSize * k_sideSize;



    T get_fast( const int32_t x, const int32_t y )
    {
        const auto index = y * k_sideSize + x;

       // std::assert( index < k_tileCount );

        return m_tiles[index];
    }

    void set_fast( const int32_t x, const int32_t y, const T v )
    {
        const auto index = y * k_sideSize + x;

        assert( index < k_tileCount );

        m_tiles[index] = v;
	
		//_mm_stream_si32( (int32_t *)( m_tiles + index ), v );
	}

    void init_very_fast( const int32_t x, const int32_t y, const T v )
    {
        const auto index = y * k_sideSize + x;

        assert( index < k_tileCount );

        _mm_stream_si64( (int64_t *)(m_tiles + index), v );
    }


private:
    
    T m_tiles[k_tileCount];
};


class ChunkMeta
{
public:
    ChunkMeta( const int32_t originX, const int32_t originY)
        :
        m_originX( originX ),
        m_originY( originY )
    {

    }



private:

    int32_t m_originX;
    int32_t m_originY;

};

template< typename SUB, typename T >
class CustomMetric
{
public:

    CustomMetric(const T v)
        :
        m_v( v )
    {
    }



    inline bool operator <( const CustomMetric<SUB, T> rhs ) const
    {
        return m_v < rhs.m_v;
    }

	//*
    inline SUB operator *( const CustomMetric<SUB, T> rhs ) const
    {
        return m_v * rhs.m_v;
    }
	//*/

	inline SUB operator %( const CustomMetric<SUB, T> rhs ) const
	{
		return m_v % rhs.m_v;
	}
	
	SUB operator +( const CustomMetric<SUB, T> rhs ) const
    {
        return m_v + rhs.m_v;
    }

    SUB operator -( const CustomMetric<SUB, T> rhs ) const
    {
        return m_v - rhs.m_v;
    }

    void operator++()
    {
        ++m_v;
        //return (SUB&)*this;
    }

    const T metric() const
    {
        return m_v;
    }

protected:
    T m_v;
};

class TileMetric;

class ChunkMetric: public CustomMetric<ChunkMetric, int32_t>
{
public:
    using CustomMetric::CustomMetric;

    explicit ChunkMetric( const TileMetric tm );




private:
    friend class TileMetric;
};

class TileMetric: public CustomMetric<TileMetric, int32_t>
{
public:
    using CustomMetric::CustomMetric;

    explicit TileMetric(const ChunkMetric cm);


	ChunkMetric operator /( const ChunkSize rhs ) const
	{
		return m_v / rhs.size();
	}


private:
    friend class ChunkMetric;
};

TileMetric operator *( const ChunkMetric lhs, const ChunkSize rhs );
TileMetric operator %( const TileMetric lhs, const ChunkSize rhs );


template<typename T>
class Map
{
public:
    Map( ChunkMetric chunkMaxX, ChunkMetric chunkMaxY )
        :
        m_chunkMaxX( chunkMaxX ),
        m_chunkMaxY( chunkMaxY )
    {
        //initChunks();
    }

    T get_slow( const TileMetric x, const TileMetric y )
    {
        const auto chunkX = x / k_standardSideSize;
        const auto relativeX = x % k_standardSideSize;
        const auto chunkY = y / k_standardSideSize;
        const auto relativeY = y % k_standardSideSize;

        const auto chunkIndex = chunkY * m_chunkMaxX + chunkX;

        const auto chunk = m_chunks[chunkIndex.metric()];

        return chunk->get_fast( relativeX.metric(), relativeY.metric() );
    }

    void set_slow( const TileMetric x, const TileMetric y, const T v )
    {
		const auto chunkX = x / k_standardSideSize;
		const auto relativeX = x % k_standardSideSize;
		const auto chunkY = y / k_standardSideSize;
		const auto relativeY = y % k_standardSideSize;

		const auto chunkIndex = chunkY * m_chunkMaxX + chunkX;

		const auto chunk = m_chunks[chunkIndex.metric()];

		chunk->set_fast( relativeX.metric(), relativeY.metric(), v );
    }





    void initChunks()
    {
        const auto chunkCount = m_chunkMaxX * m_chunkMaxY;

        m_chunks.resize( chunkCount.metric() );

        /*
        for( ChunkMetric cy = 0; cy < m_chunkMaxY; ++cy )
        {
            const ChunkMetric baseX = cy * m_chunkMaxX;
            for( ChunkMetric cx = 0; cx < m_chunkMaxX; ++cx )
            {
                const ChunkMetric index = baseX + cx;

                auto chunk = std::make_shared<Chunk<T>>();

                m_chunks[index.metric()] = chunk;

                for( int32_t y = 0; y < k_standardSideSize; ++y )
                {
                    for( int32_t x = 0; x < k_standardSideSize; x += 4 )
                    {
                        chunk->init_very_fast(x, y, T());
                    }
                }
            }
        }

        /*/

        const auto size = (int)m_chunkMaxY.metric();

		/*
        async::parallel_for( async::irange( 0, size ), [ this ]( int cy ) {
            const ChunkMetric baseX = ChunkMetric( cy ) * m_chunkMaxX;
            for( ChunkMetric cx = 0; cx < m_chunkMaxX; ++cx )
            {
                const ChunkMetric index = baseX + cx;

                auto chunk = std::make_shared<Chunk<T>>();

                m_chunks[index.metric()] = chunk;

                for( int32_t y = 0; y < k_standardSideSize.size(); ++y )
                {
                    for( int32_t x = 0; x < k_standardSideSize.size(); x += 4 )
                    {
                        chunk->init_very_fast( x, y, T() );
                    }
                }
            }
        } );
		*/
        //*/


    }


private:
    ChunkMetric m_chunkMaxX;
    ChunkMetric m_chunkMaxY;

    std::vector<std::shared_ptr<Chunk<T>>> m_chunks;
};








}


//Explicitly out of the namespace

map::ChunkMetric operator"" _chunk( unsigned long long int metric );

map::TileMetric operator "" _tile( unsigned long long metric );


void testMap();