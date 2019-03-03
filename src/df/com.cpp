//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "stdafx.h"


#include "com.h"



union Thingy
{
    int32_t i;
    float   f;

    Thingy( float n_f )
        :
        f( n_f )
    {
    }
        
};

#define BitwiseCast( f ) (*(int*)&f)


int df::ComDynamicBlocks::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TTuple &blocks )
{
    const int hint = _MM_HINT_T0;
    const int ahead = 96;

    int total = 0;


    //EBlockStatus *pBS;
    //ent::EntityId *pId;
	const SpecialType * pSrcX = blocks.src<X, SpecialType>();
	const SpecialType * pSrcY = blocks.src<Y, SpecialType>();
	const SpecialType * pSrcZ = blocks.src<Z, SpecialType>();
	const SpecialType * pSrcW = blocks.src<W, SpecialType>();
	const SpecialType * pSrcDX = blocks.src<DX, SpecialType>();
	const SpecialType * pSrcDY = blocks.src<DY, SpecialType>();
	const SpecialType * pSrcDZ = blocks.src<DZ, SpecialType>();
	const SpecialType * pSrcDW = blocks.src<DW, SpecialType>();
    auto * pDstX = (float*)blocks.dst<X, SpecialType>();
    auto * pDstY = (float*)blocks.dst<Y, SpecialType>();
    auto * pDstZ = (float*)blocks.dst<Z, SpecialType>();
    auto * pDstW = (float*)blocks.dst<W, SpecialType>();

    //auto * pDstDX_debug = (float*)blocks.dst<DX, SpecialType>();


    //blocks.getPointers( &pBS, &pId, &pX, &pY, &pZ, &pDX, &pDY, &pDZ );


//#pragma loop(hint_parallel(12))
//#pragma loop(ivdep) // ivdep will force this through.  

    /*
    for( int32_t i = 0; i < g_blockSize; ++i )
    {

        pDstX[i] = pSrcX[i] + pSrcDX[i] * dtMs;
        pDstY[i] = pSrcY[i] + pSrcDY[i] * dtMs;
        pDstZ[i] = pSrcZ[i] + pSrcDZ[i] * dtMs;
        pDstW[i] = pSrcW[i] + pSrcDW[i] * dtMs;
    }
  
    //*/

    //*
    const float dtSec = cast<float>( dtMs ) / 1000.0f;

//#pragma loop(no_vector) 
    for( int32_t i = 0; i < g_blockSize; ++i )
    {

        const auto newX = pSrcX[i] + pSrcDX[i] * dtSec;
        const auto newY = pSrcY[i] + pSrcDY[i] * dtSec;
        const auto newZ = pSrcZ[i] + pSrcDZ[i] * dtSec;
        //const auto newW = pSrcW[i] + pSrcDW[i] * dtSec;

		/*
        _mm_stream_si32( (int *)( pDstX + i ), BitwiseCast( newX ) );
        _mm_stream_si32( (int *)( pDstY + i ), BitwiseCast( newY ) );
        _mm_stream_si32( (int *)( pDstZ + i ), BitwiseCast( newZ ) );
		//_mm_stream_si32( (int *)( pDstW + i ), BitwiseCast( newW ) );
		*/

		//*
        pDstX[i] = newX;
        pDstY[i] = newY;
        pDstZ[i] = newZ;
        //pDstW[i] = newW;
		//*/

        //_mm_prefetch( (const char *)( pSrcX ) + ahead, hint );
        //_mm_prefetch( (const char *)( pSrcY ) + ahead, hint );
        //_mm_prefetch( (const char *)( pSrcZ ) + ahead, hint );
        //_mm_prefetch( (const char *)( pSrcDX ) + ahead, hint );
        //_mm_prefetch( (const char *)( pSrcDY ) + ahead, hint );
        //_mm_prefetch( (const char *)( pSrcDZ ) + ahead, hint );

    }

    //*/

    /*
    const float dtSec = cast<float>( dtMs ) / 1000.0f;


    for( int32_t i = 0; i < g_blockSize; i+=4 )
    {
        {
            const auto newX = pSrcX[i + 0] + pSrcDX[i + 0] * dtMs;
            const auto newY = pSrcY[i + 0] + pSrcDY[i + 0] * dtMs;
            const auto newZ = pSrcZ[i + 0] + pSrcDZ[i + 0] * dtMs;
            pDstX[i + 0] = newX;
            pDstY[i + 0] = newY;
            pDstZ[i + 0] = newZ;
        }

        {
            const auto newX = pSrcX[i + 1] + pSrcDX[i + 1] * dtMs;
            const auto newY = pSrcY[i + 1] + pSrcDY[i + 1] * dtMs;
            const auto newZ = pSrcZ[i + 1] + pSrcDZ[i + 1] * dtMs;
            pDstX[i + 1] = newX;
            pDstY[i + 1] = newY;
            pDstZ[i + 1] = newZ;
        }

        {
            const auto newX = pSrcX[i + 2] + pSrcDX[i + 2] * dtMs;
            const auto newY = pSrcY[i + 2] + pSrcDY[i + 2] * dtMs;
            const auto newZ = pSrcZ[i + 2] + pSrcDZ[i + 2] * dtMs;
            pDstX[i + 2] = newX;
            pDstY[i + 2] = newY;
            pDstZ[i + 2] = newZ;
        }

        {
            const auto newX = pSrcX[i + 3] + pSrcDX[i + 3] * dtMs;
            const auto newY = pSrcY[i + 3] + pSrcDY[i + 3] * dtMs;
            const auto newZ = pSrcZ[i + 3] + pSrcDZ[i + 3] * dtMs;
            pDstX[i + 3] = newX;
            pDstY[i + 3] = newY;
            pDstZ[i + 3] = newZ;
        }

        /* Useless
        _mm_prefetch( (const char *)( pSrcX + ahead ), hint );
        _mm_prefetch( (const char *)( pSrcY + ahead ), hint );
        _mm_prefetch( (const char *)( pSrcZ + ahead ), hint );
        _mm_prefetch( (const char *)( pSrcDX+ ahead ), hint );
        _mm_prefetch( (const char *)( pSrcDY+ ahead ), hint );
        _mm_prefetch( (const char *)( pSrcDZ+ ahead ), hint );
        * /
    }

    //*/

    blocks.swap();

    /*/


    for( int32_t i = 0; i < 100000; ++i )
    {
        total += 1 + i & 0x0f + dtMs;
    }



    //*/

    return total;

}


void df::ComDynamicBlocks::update( const uint64_t dtMs )
{
    //int counts[65536];

    /*


    //const auto size = (int)m_com.m_blocks.m_tuple.size();

    for( int32_t iBlock = 0; iBlock < (int)m_com.m_blocks.m_tuple.size(); iBlock += 1 )
    {
        auto &blocks = m_com.m_blocks.m_tuple[iBlock];

        const auto total = updateBlock( dtMs, *blocks.get() );

        //const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

        //counts[hash % 65536] += total;
    }

    /*/


    const auto size = (int)m_com.m_blocks.m_tuple.size();

    async::parallel_for( async::irange( 0, size ), [this, dtMs ]( int iBlock ) {
        auto &blocks = m_com.m_blocks.m_tuple[iBlock];

        const auto total = updateBlock( dtMs, *blocks.get() );

        //const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

        //counts[hash % 65536] += total;
    });




    //*/
}









////////

int df::ComDynamicBlocksVec::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TTuple &blocks )
{
	const int hint = _MM_HINT_T0;
	const int ahead = 96;

	int total = 0;


	const SpecialType * pSrcPos = blocks.src<Pos, SpecialType>();
	const SpecialType * pSrcDelta = blocks.src<Delta, SpecialType>();

	SpecialType * pDstPos = blocks.dst<Pos, SpecialType>();


	//*
	const float dtSec = cast<float>( dtMs ) / 1000.0f;

//#pragma loop(no_vector) 
	for( int32_t i = 0; i < g_blockSize; ++i )
	{
		//const cb::Vec3 dtDelta = ( pSrcDelta[i] * dtSec );

		const SpecialType v = pSrcPos[i] + pSrcDelta[i] * dtSec;

		pDstPos[i] = v;
	}


	blocks.swap();


	return total;

}


void df::ComDynamicBlocksVec::update( const uint64_t dtMs )
{


	const auto size = (int)m_com.m_blocks.m_tuple.size();

	async::parallel_for( async::irange( 0, size ), [ this, dtMs ]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_tuple[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
	} );
}



/*
int df::ComDynamicBlocksXM::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TTuple &blocks )
{
	const int hint = _MM_HINT_T0;
	const int ahead = 96;

	int total = 0;


	const SpecialType * pSrcPos = blocks.src<Pos, SpecialType>();
	const SpecialType * pSrcDelta = blocks.src<Delta, SpecialType>();

	SpecialType * pDstPos = blocks.dst<Pos, SpecialType>();


	//*
	const float dtSec = cast<float>( dtMs ) / 1000.0f;

	//#pragma loop(no_vector) 
	for( int32_t i = 0; i < g_blockSize; ++i )
	{
		//dx::XMStoreFloat3

		const auto res = dx::XMVectorAdd( pSrcPos[i], dx::XMVectorScale( pSrcDelta[i], dtSec ) );

		//pDstPos[i] = res;

		dx::XMStoreFloat3A( (dx::XMFLOAT3A *)(pDstPos + i), res);
	}


	blocks.swap();


	return total;

}


void df::ComDynamicBlocksXM::update( const uint64_t dtMs )
{


	const auto size = (int)m_com.m_blocks.m_tuple.size();

	async::parallel_for( async::irange( 0, size ), [ this, dtMs ]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_tuple[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
	} );
}

void df::ComDynamicBlocksXM::printRandom()
{
	const auto size = (int)m_com.m_blocks.m_tuple.size();

	for ( int i = 0; i < 10; ++i )
	{
		auto &blocks = *m_com.m_blocks.m_tuple[i].get();

		SpecialType * pSrcPos = blocks.src<Pos, SpecialType>();

		printf("%f", (double)*pSrcPos[rand() % g_blockSize].m128_f32);
	}

}
*/



int df::ComDynamicBlocksAoS::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TTuple &blocks )
{
    int total = 0;

    //EBlockStatus *pBS;
    //ent::EntityId *pId;
    Physical * pSrc = blocks.src<Pos, Physical>();
    Physical * pDst = blocks.dst<Pos, Physical>();

    //blocks.getPointers( &pBS, &pId, &pX, &pY, &pZ, &pDX, &pDY, &pDZ );

    //*

//#pragma loop(hint_parallel(12))
//#pragma loop(ivdep) // ivdep will force this through.  

    const float dtSec = cast<float>( dtMs ) / 1000.0f;


    for( int32_t i = 0; i < g_blockSize; ++i )
    {

        const auto newX = pSrc[i].x + pSrc[i].dx * dtSec;
        const auto newY = pSrc[i].y + pSrc[i].dy * dtSec;
        const auto newZ = pSrc[i].z + pSrc[i].dz * dtSec;
        //const auto newW = pSrc[i].w + pSrc[i].dw * dtMs;

        //_mm_stream_si32( (int *)( pDst + i ), BitwiseCast( newZ ) );
        //_mm_stream_si32( (int *)( ( pDst + i ) + offsetof( Physical, x ) ), BitwiseCast( newX ) );
        //_mm_stream_si32( (int *)( ( pDst + i ) + offsetof( Physical, x ) ), BitwiseCast( newY ) );
        //_mm_stream_si32( (int *)( ( pDst + i ) + offsetof( Physical, x ) ), BitwiseCast( newZ ) );
        //_mm_stream_si64( (int64_t *)( ( pDst + i ) + offsetof( Physical, x ) ), newW );

        pDst[i].x = newX;
        pDst[i].y = newY;
        pDst[i].z = newZ;

    }

    blocks.swap();

    /*/


    for( int32_t i = 0; i < 100000; ++i )
    {
    total += 1 + i & 0x0f + dtMs;
    }



    //*/

    return total;

}


void df::ComDynamicBlocksAoS::update( const uint64_t dtMs )
{
    //int counts[65536];

    /*


    //const auto size = (int)m_com.m_blocks.m_tuple.size();

    for( int32_t iBlock = 0; iBlock < (int)m_com.m_blocks.m_tuple.size(); iBlock += 1 )
    {
        auto &blocks = m_com.m_blocks.m_tuple[iBlock];

        const auto total = updateBlock( dtMs, *blocks.get() );

       // const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

       // counts[hash % 65536] += total;
    }

    /*/


    const auto size = (int)m_com.m_blocks.m_tuple.size();

    async::parallel_for( async::irange( 0, size ), [this, dtMs ]( int iBlock ) {
        auto &blocks = m_com.m_blocks.m_tuple[iBlock];

        const auto total = updateBlock( dtMs, *blocks.get() );

        //const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

        //counts[hash % 65536] += total;
    });




    //*/
}