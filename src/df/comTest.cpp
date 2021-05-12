//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#include "comTest.h"


i32 s_lastCreatedEntCount = 0;
df::ComDynamicBlocks* s_blockTest;
df::ComDynamicBlocksAoS* s_blockTestAoS;
df::ComDynamicBlocksVec3* s_blockTestVec3;
df::ComDynamicBlocksVec4* s_blockTestVec4;




void df::timeBlocks( const i32 numLoops, const i32 numEnts, u32* timeSoAIndividualuS, u32* timeAoSuS, u32* timeSoA3uS, u32* timeSoA4uS )
{

	//SetThreadAffinityMask( GetCurrentThread(), 1 );

	//std::unique_ptr<DFPhysicalMgr<DFPhysical<c_arrSize>, c_arrSize> > dfPhysical(new DFPhysicalMgr<DFPhysical<c_arrSize>, c_arrSize>);

	//std::unique_ptr<NormPhysicalMgr<Physical[c_arrSize], c_arrSize> > physical( new NormPhysicalMgr<Physical[c_arrSize], c_arrSize> );

	//auto d1 = Distance<float>::make( 10 );
	//auto d2 = Distance<float>::make( 20 );

	/*
	units::length64::nanometer_t nm( 100 );


	auto optBool = std::optional<bool>( true );


	units::length64::meter_t unitLength( 1 );






	nm = unitLength;
	/*/
	int64_t nm = 10;
	//*/


	/*
	//Release
	const int32_t k_numLoops = 1000;
	const int32_t k_numEntities = 5000000;
	/*/
	//Debug
	//const int32_t k_numLoops = 10;
	//const int32_t k_numEntities = 500000;
	//*/




	//df::ComDynamicBlocksM128 blockTestM128;
	//df::ComDynamicBlocksXM blockTestXM;

	if( s_lastCreatedEntCount != numEnts )
	{
		s_lastCreatedEntCount = numEnts;

		delete s_blockTest;
		delete s_blockTestAoS;
		delete s_blockTestVec3;
		delete s_blockTestVec4;

		s_blockTest = new df::ComDynamicBlocks();
		s_blockTestAoS = new df::ComDynamicBlocksAoS();
		s_blockTestVec3 = new df::ComDynamicBlocksVec3();
		s_blockTestVec4 = new df::ComDynamicBlocksVec4();

		auto entityId = ent::EntityId::makeNext();

		const auto nm_f = cast<float>( nm );
		s_blockTest->m_com.append( entityId, nm_f, 10, 10, 0, nm_f, 0, 0, 0 );
		s_blockTestAoS->m_com.append( entityId, df::ComDynamicBlocksAoS::Physical{ 10, 10, 10, 1, 1, 1 } );
		s_blockTestVec3->m_com.append( entityId, cb::Vec3( 10, 10, 10 ), cb::Vec3( 0, 0, 0 ) );
		s_blockTestVec4->m_com.append( entityId, cb::Vec4( 10, 10, 10, 0 ), cb::Vec4( 0, 0, 0, 0 ) );


		// I N S E R T  T E S T
		const auto entityId2 = ent::EntityId::makeNext();
		//Dont add anything here yet

		// Appendappendappend
		entityId = ent::EntityId::makeNext();
		s_blockTestVec3->m_com.append( entityId, cb::Vec3( 10, 10, 11 ), cb::Vec3( 0, 0, 1 ) );

		entityId = ent::EntityId::makeNext();
		s_blockTestVec3->m_com.append( entityId, cb::Vec3( 10, 10, 12 ), cb::Vec3( 0, 0, 2 ) );

		entityId = ent::EntityId::makeNext();
		s_blockTestVec3->m_com.append( entityId, cb::Vec3( 10, 10, 13 ), cb::Vec3( 0, 0, 3 ) );

		s_blockTestVec3->m_com.insert( entityId2, cb::Vec3( 10, 10, 14 ), cb::Vec3( 0, 0, 4 ) );



			/*
			__m128 val;
			blockTestM128.m_com.append( entityId, val, val );

			const auto pos = dx::XMVectorSet( 10, 10, 10, 0 );
			const auto delta = dx::XMVectorSet( 0, 0, 0, 0 );

			blockTestXM.m_com.append( entityId, pos, delta );
			*/
			const auto time = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numEnts; ++i )
			{
				const auto entityId = ent::EntityId::makeNext();

				df::ComDynamicBlocks::Scalar x = cast<float>( rand() * 2 );
				df::ComDynamicBlocks::Scalar y = cast<float>( rand() );
				df::ComDynamicBlocks::Scalar z = cast<float>( rand() % 16 );

				df::ComDynamicBlocks::Scalar dx = cast<float>( rand() ) / 4095.0f;
				df::ComDynamicBlocks::Scalar dy = cast<float>( rand() ) / 4095.0f;
				df::ComDynamicBlocks::Scalar dz = 0;

				s_blockTest->m_com.append( entityId, x, y, z, 0, dx, dy, dz, 0 );
				s_blockTestAoS->m_com.append( entityId, df::ComDynamicBlocksAoS::Physical{ x, y, z, dx, dy, dz } );
				s_blockTestVec3->m_com.append( entityId, df::ComDynamicBlocksVec3::TVec( x, y, z ), df::ComDynamicBlocksVec3::TVec( dx, dy, dz ) );
				s_blockTestVec4->m_com.append( entityId, df::ComDynamicBlocksVec4::TVec( x, y, z, 0 ), df::ComDynamicBlocksVec4::TVec( dx, dy, dz, 0 ) );

				__m128 val;
				val.m128_f32[0] = x;
				val.m128_f32[1] = y;
				val.m128_f32[2] = z;
				val.m128_f32[3] = 0.0f;

				/*
				blockTestM128.m_com.append( entityId, val, val );


				const auto pos = dx::XMVectorSet( x, y, z, 0 );
				const auto delta = dx::XMVectorSet( dx, dy, dz, 0 );

				blockTestXM.m_com.append( entityId, pos, delta );
				*/
			}
				} );

		const float fTimeNs = (float)time;
		const float fTimeMs = fTimeNs / 1000.0f;

		printf( "Ms to build was %.3f\n", fTimeMs );
	}



	//*
	{
		const auto time_update = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numLoops; ++i )
			{
				s_blockTest->update( rand() & 7 + 8 ); //, df::EThreading::GrossBlocks );
			}
			} );

		printf( "Ms to update soa was %i.%.3i\n", (uint32_t)( time_update / 1000 ), (uint32_t)( time_update % 1000 ) );

		if( timeSoAIndividualuS )
		{
			*timeSoAIndividualuS = (u32)time_update;
		}
	}
	//*/

	//*
	{
		const auto timeUpdateAoS = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numLoops; ++i )
			{
				s_blockTestAoS->update( rand() & 7 + 8 ); //, df::EThreading::GrossBlocks );
			}
			} );

		printf( "Ms to update aos was %i.%.3i\n", (uint32_t)( timeUpdateAoS / 1000 ), (uint32_t)( timeUpdateAoS % 1000 ) );

		if( timeAoSuS )
		{
			*timeAoSuS = (u32)timeUpdateAoS;
		}
	}
	//*/

//*
	{
		const auto timeUpdateVec3 = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numLoops; ++i )
			{
				s_blockTestVec3->update( rand() & 7 + 8 ); //, df::EThreading::GrossBlocks );
			}
			} );

		printf( "Ms to update Vec was %i.%.3i\n", (uint32_t)( timeUpdateVec3 / 1000 ), (uint32_t)( timeUpdateVec3 % 1000 ) );

		if( timeSoA3uS )
		{
			*timeSoA3uS = (u32)timeUpdateVec3;
		}
	}
	//*/

	//*
	{
		const auto timeUpdateVec4 = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numLoops; ++i )
			{
				s_blockTestVec4->update( rand() & 7 + 8 ); //, df::EThreading::GrossBlocks );
			}
			} );

		printf( "Ms to update Vec was %i.%.3i\n", (uint32_t)( timeUpdateVec4 / 1000 ), (uint32_t)( timeUpdateVec4 % 1000 ) );

		if( timeSoA4uS )
		{
			*timeSoA4uS = (u32)timeUpdateVec4;
		}
	}
	//*/


/*
	{
		const auto timeUpdateM128 = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < k_numLoops; ++i )
			{
				blockTestM128.update( rand() & 7 + 8, df::EThreading::GrossBlocks );
			}
		} );

		printf( "Ms to update M128 was %i.%.3i\n", (uint32_t)(timeUpdateM128 / 1000), (uint32_t)(timeUpdateM128 % 1000) );
	}
	//*/

	/*
	{
		const auto timeUpdateXM = Timer<>::execution([&]() {
			for (int32_t i = 0; i < k_numLoops; ++i)
			{
				blockTestXM.update(rand() & 7 + 8, df::EThreading::GrossBlocks);
			}
			});

		printf("Ms to update XM was %i.%.3i\n", (uint32_t)(timeUpdateXM / 1000), (uint32_t)(timeUpdateXM % 1000));

		//blockTestXM.printRandom();
	}
	//*/


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/*
	{
		const auto time_update = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < k_numLoops; ++i )
			{
				blockTest.update( rand() & 7 + 8, df::EThreading::FineBlocks );
			}
		} );

		printf( "Ms to update fine soa was %i.%.3i\n", (uint32_t)(time_update / 1000), (uint32_t)(time_update % 1000) );
	}
	//*/

	/*
	{
		const auto timeUpdateAoS = Timer<>::execution([&]() {
			for (int32_t i = 0; i < k_numLoops; ++i)
			{
				blockTestAoS.update(rand() & 7 + 8, df::EThreading::FineBlocks);
			}
			});

		printf("Ms to update aos was %i.%.3i\n", (uint32_t)(timeUpdateAoS / 1000), (uint32_t)(timeUpdateAoS % 1000));
	}
	//*/

	/*
	{
		const auto timeUpdateVec = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < k_numLoops; ++i )
			{
				blockTestVec.update( rand() & 7 + 8, df::EThreading::FineBlocks );
			}
		} );

		printf( "Ms to update fine Vec was %i.%.3i\n", (uint32_t)(timeUpdateVec / 1000), (uint32_t)(timeUpdateVec % 1000) );
	}
	//*/

	/*
		{
			const auto timeUpdateM128 = Timer<>::execution([&]() {
				for (int32_t i = 0; i < k_numLoops; ++i)
				{
					blockTestM128.update(rand() & 7 + 8, df::EThreading::FineBlocks);
				}
				});

			printf("Ms to update M128 was %i.%.3i\n", (uint32_t)(timeUpdateM128 / 1000), (uint32_t)(timeUpdateM128 % 1000));
		}
		//*/

		/*
		{
			const auto timeUpdateXM = Timer<>::execution([&]() {
				for (int32_t i = 0; i < k_numLoops; ++i)
				{
					blockTestXM.update(rand() & 7 + 8, df::EThreading::FineBlocks);
				}
				});

			printf("Ms to update XM was %i.%.3i\n", (uint32_t)(timeUpdateXM / 1000), (uint32_t)(timeUpdateXM % 1000));

			//blockTestXM.printRandom();
		}
		//*/



	const auto entityId = ent::EntityId::makeNext();

	{
		const auto timeRemoveEntities = Timer<>::execution( [&]() {
			for( int32_t i = 0; i < numLoops; ++i )
			{
			}
			} );

		printf( "Ms to remove entities was %i.%.3i\n", (uint32_t)( timeRemoveEntities / 1000 ), (uint32_t)( timeRemoveEntities % 1000 ) );
	}



	{

		const auto nm_f = cast<f32>( nm );

		s_blockTest->m_com.append( entityId, nm_f, 10, 10, 0, nm_f, 0, 0, 0 );
	}
}



int df::ComDynamicBlocks::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks )
{
	const int hint = _MM_HINT_T0;
	const int ahead = 96;

	int total = 0;


	//EBlockStatus *pBS;
	//ent::EntityId *pId;
	const Scalar *pSrcX = blocks.src<X, Scalar>();
	const Scalar *pSrcY = blocks.src<Y, Scalar>();
	const Scalar *pSrcZ = blocks.src<Z, Scalar>();
	const Scalar *pSrcW = blocks.src<W, Scalar>();
	const Scalar *pSrcDX = blocks.src<DX, Scalar>();
	const Scalar *pSrcDY = blocks.src<DY, Scalar>();
	const Scalar *pSrcDZ = blocks.src<DZ, Scalar>();
	const Scalar *pSrcDW = blocks.src<DW, Scalar>();
	auto *pDstX = (float *)blocks.dst<X, Scalar>();
	auto *pDstY = (float *)blocks.dst<Y, Scalar>();
	auto *pDstZ = (float *)blocks.dst<Z, Scalar>();
	auto *pDstW = (float *)blocks.dst<W, Scalar>();

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


	//const auto size = (int)m_com.m_blocks.m_block.size();

	for( int32_t iBlock = 0; iBlock < (int)m_com.m_blocks.m_block.size(); iBlock += 1 )
	{
			auto &blocks = m_com.m_blocks.m_block[iBlock];

			const auto total = updateBlock( dtMs, *blocks.get() );

			//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

			//counts[hash % 65536] += total;
	}

	/*/


	const auto size = (int)m_com.m_blocks.m_block.size();

	async::parallel_for( async::irange( 0, size ), [this, dtMs]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_block[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
		} );




	//*/
}









////////

int df::ComDynamicBlocksVec3::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks )
{
	const int hint = _MM_HINT_T0;
	const int ahead = 96;

	int total = 0;


	const TVec *pSrcPos = blocks.src<Pos, TVec>();
	const TVec *pSrcDelta = blocks.src<Delta, TVec>();

	TVec *pDstPos = blocks.dst<Pos, TVec>();


	//*
	const float dtSec = cast<float>( dtMs ) / 1000.0f;

	//#pragma loop(no_vector) 
	for( int32_t i = 0; i < g_blockSize; ++i )
	{
		//const cb::Vec3 dtDelta = ( pSrcDelta[i] * dtSec );

		const TVec v = pSrcPos[i] + pSrcDelta[i] * dtSec;

		pDstPos[i] = v;
	}


	blocks.swap();


	return total;

}


void df::ComDynamicBlocksVec3::update( const uint64_t dtMs )
{


	const auto size = (int)m_com.m_blocks.m_block.size();
	//*
	async::parallel_for( async::irange( 0, size ), [this, dtMs]( int iBlock ) {
		/*/
		for( i32 iBlock = 0; iBlock < size; ++iBlock )
		{
		//*/
		auto &blocks = m_com.m_blocks.m_block[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
		}
	);
}





int df::ComDynamicBlocksVec4::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks )
{
	const int hint = _MM_HINT_T0;
	const int ahead = 96;

	int total = 0;


	const TVec *pSrcPos = blocks.src<Pos, TVec>();
	const TVec *pSrcDelta = blocks.src<Delta, TVec>();

	TVec *pDstPos = blocks.dst<Pos, TVec>();


	//*
	const float dtSec = cast<float>( dtMs ) / 1000.0f;

	//#pragma loop(no_vector) 
	for( int32_t i = 0; i < g_blockSize; ++i )
	{
		//const cb::Vec3 dtDelta = ( pSrcDelta[i] * dtSec );

		const TVec v = pSrcPos[i] + pSrcDelta[i] * dtSec;

		pDstPos[i] = v;
	}


	blocks.swap();


	return total;

}


void df::ComDynamicBlocksVec4::update( const uint64_t dtMs )
{


	const auto size = (int)m_com.m_blocks.m_block.size();

	async::parallel_for( async::irange( 0, size ), [this, dtMs]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_block[iBlock];

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


	const auto size = (int)m_com.m_blocks.m_block.size();

	async::parallel_for( async::irange( 0, size ), [ this, dtMs ]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_block[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
	} );
}

void df::ComDynamicBlocksXM::printRandom()
{
	const auto size = (int)m_com.m_blocks.m_block.size();

	for ( int i = 0; i < 10; ++i )
	{
		auto &blocks = *m_com.m_blocks.m_block[i].get();

		SpecialType * pSrcPos = blocks.src<Pos, SpecialType>();

		printf("%f", (double)*pSrcPos[rand() % g_blockSize].m128_f32);
	}

}
*/



int df::ComDynamicBlocksAoS::updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks )
{
	int total = 0;

	//EBlockStatus *pBS;
	//ent::EntityId *pId;
	Physical *pSrc = blocks.src<Pos, Physical>();
	Physical *pDst = blocks.dst<Pos, Physical>();

	//blocks.m_pSrc->

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


	//const auto size = (int)m_com.m_blocks.m_block.size();

	for( int32_t iBlock = 0; iBlock < (int)m_com.m_blocks.m_block.size(); iBlock += 1 )
	{
			auto &blocks = m_com.m_blocks.m_block[iBlock];

			const auto total = updateBlock( dtMs, *blocks.get() );

		 // const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		 // counts[hash % 65536] += total;
	}

	/*/


	const auto size = (int)m_com.m_blocks.m_block.size();

	async::parallel_for( async::irange( 0, size ), [this, dtMs]( int iBlock ) {
		auto &blocks = m_com.m_blocks.m_block[iBlock];

		const auto total = updateBlock( dtMs, *blocks.get() );

		//const auto hash = std::hash<std::thread::id>{}( std::this_thread::get_id() );

		//counts[hash % 65536] += total;
		} );




	//*/
}

