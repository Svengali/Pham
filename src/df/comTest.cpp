//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#include "com.h"


i32 s_lastCreatedEntCount = 0;
df::ComDynamicBlocks		*s_blockTest;
df::ComDynamicBlocksAoS *s_blockTestAoS;
df::ComDynamicBlocksVec3 *s_blockTestVec3;
df::ComDynamicBlocksVec4 *s_blockTestVec4;




void df::timeBlocks( const i32 numLoops, const i32 numEnts, u32 *timeSoAIndividualuS, u32 *timeAoSuS, u32 *timeSoA3uS, u32 *timeSoA4uS )
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
		s_blockTestVec3= new df::ComDynamicBlocksVec3();
		s_blockTestVec4= new df::ComDynamicBlocksVec4();

		const auto entityId = ent::EntityId::makeNext();

		const auto nm_f = cast<float>( nm );
		s_blockTest->m_com.append( entityId, nm_f, 10, 10, 0, nm_f, 0, 0, 0 );
		s_blockTestAoS->m_com.append( entityId, df::ComDynamicBlocksAoS::Physical{ 10, 10, 10, 1, 1, 1 } );
		s_blockTestVec3->m_com.append( entityId, cb::Vec3( 10, 10, 10 ), cb::Vec3( 0, 0, 0 ) );
		s_blockTestVec4->m_com.append( entityId, cb::Vec4( 10, 10, 10, 0 ), cb::Vec4( 0, 0, 0, 0 ) );

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

		printf( "Ms to update soa was %i.%.3i\n", (uint32_t)(time_update / 1000), (uint32_t)(time_update % 1000) );

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

		printf( "Ms to update aos was %i.%.3i\n", (uint32_t)(timeUpdateAoS / 1000), (uint32_t)(timeUpdateAoS % 1000) );

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
				s_blockTestVec3->update( rand() & 7 + 8); //, df::EThreading::GrossBlocks );
			}
		} );

		printf( "Ms to update Vec was %i.%.3i\n", (uint32_t)(timeUpdateVec3 / 1000), (uint32_t)(timeUpdateVec3 % 1000) );

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

		printf( "Ms to update Vec was %i.%.3i\n", (uint32_t)(timeUpdateVec4 / 1000), (uint32_t)(timeUpdateVec4 % 1000) );

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

		printf( "Ms to remove entities was %i.%.3i\n", (uint32_t)(timeRemoveEntities / 1000), (uint32_t)(timeRemoveEntities % 1000) );
	}



	{

		const auto nm_f = cast<f32>( nm );

		s_blockTest->m_com.append( entityId, nm_f, 10, 10, 0, nm_f, 0, 0, 0 );
	}
}

