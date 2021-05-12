//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

//Only here to stop ~~~~~~~~
#include <cstdint>
#include <array>



namespace df
{


	extern void timeBlocks( const i32 numLoops, const i32 numEnts, u32 *timeSoAIndividualuS, u32 *timeAoSuS, u32 *timeSoA3uS, u32 *timeSoA4uS );


	class ComDynamicBlocks
	{
	public:


		enum EDynamicSlots
		{
			Status = 0,
			EntityId = 1,
			X = 2,
			Y = 3,
			Z = 4,
			W = 5,
			DX = 6,
			DY = 7,
			DZ = 8,
			DW = 9,
		};

	public:

		typedef float Scalar;


		typedef ComBlocks<g_blockSize, ComDynamicBlocks::EDynamicSlots, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar> TCom;

		TCom m_com;

	public:

		int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

		void update( const uint64_t dtMs );
	};


	class ComDynamicBlocksVec3
	{
	public:


		enum EDynamicSlots
		{
			Status = 0,
			EntityId = 1,
			Pos = 2,
			Delta = 3,
		};

	public:

		typedef cb::Vec3 TVec;


		typedef ComBlocks<g_blockSize, ComDynamicBlocksVec3::EDynamicSlots, TVec, TVec> TCom;

		TCom m_com;

	public:

		int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

		void update( const uint64_t dtMs );
	};


	class ComDynamicBlocksVec4
	{
	public:


		enum EDynamicSlots
		{
			Status = 0,
			EntityId = 1,
			Pos = 2,
			Delta = 3,
		};

	public:

		typedef cb::Vec4 TVec;


		typedef ComBlocks<g_blockSize, ComDynamicBlocksVec4::EDynamicSlots, TVec, TVec> TCom;

		TCom m_com;

	public:

		int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

		void update( const uint64_t dtMs );
	};


	/*
	class ComDynamicBlocksXM
	{
	public:


		enum EDynamicSlots
		{
			Status = 0,
			EntityId = 1,
			Pos = 2,
			Delta = 3,
		};

	public:

		typedef dx::XMVECTOR SpecialType;


		typedef ComBlocks<ComDynamicBlocksXM::EDynamicSlots, SpecialType, SpecialType> TCom;

		TCom m_com;

	public:

		int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

		void update( const uint64_t dtMs );

		void printRandom();
	};
	*/

	class ComDynamicBlocksAoS
	{
	public:


		enum EDynamicSlots
		{
			Status = 0,
			EntityId = 1,
			Pos = 2,
		};

		typedef float Scalar;


		struct Physical
		{
			Scalar x;
			Scalar y;
			Scalar z;
			//SpecialType w;
			Scalar dx;
			Scalar dy;
			Scalar dz;
			//SpecialType dw;
		};

	public:

		typedef ComBlocks<g_blockSize, ComDynamicBlocksAoS::EDynamicSlots, ComDynamicBlocksAoS::Physical> TCom;

		TCom m_com;

	public:

		int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

		void update( const uint64_t dtMs );
	};


}