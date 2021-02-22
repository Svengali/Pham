//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#include "map.h"

namespace map
{

TileMetric operator *( const ChunkMetric lhs, const ChunkSize rhs )
{
	return lhs.metric() * rhs.size();
}

TileMetric operator %( const TileMetric lhs, const ChunkSize rhs )
{
	return lhs.metric() % rhs.size();
}

}





map::ChunkMetric operator"" _chunk( unsigned long long int metric )
{
    return map::ChunkMetric( cast<uint32_t>( metric ) );
}

map::TileMetric operator "" _tile( unsigned long long metric )
{
    return map::TileMetric( cast<uint32_t>( metric ) );
}


/*
map::TileMetric map::ChunkMetric::operator *( const map::ChunkSize rhs ) const
{
	return m_v * rhs.size();
}
//*/

map::ChunkMetric::ChunkMetric( const map::TileMetric tm )
    :
    ChunkMetric( tm / ChunkSize( k_standardSideSize ) )
{
}


map::TileMetric::TileMetric( const map::ChunkMetric cm )
    :
    TileMetric( cm * ChunkSize( k_standardSideSize ) )
{
}



void testMap()
{
    {
        const auto map = std::make_shared<map::Map<uint16_t>>( map::ChunkMetric( 65536_tile ), map::ChunkMetric( 32768_tile ) );

        const auto tuInit = Timer<>::execution( [ & ]() {

            map->initChunks();

        } );

        printf( "Ms to init Chunk was %i.%.3i\n", (uint32_t)( tuInit / 1000 ), (uint32_t)( tuInit % 1000 ) );
    }

    {
        const auto map = std::make_shared<map::Map<uint16_t>>( map::ChunkMetric( 65536_tile ), map::ChunkMetric( 32768_tile ) );

        const auto tuInit = Timer<>::execution( [ & ]() {

            map->initChunks();

        } );

        printf( "Ms to init Chunk was %i.%.3i\n", (uint32_t)( tuInit / 1000 ), (uint32_t)( tuInit % 1000 ) );
    }




}