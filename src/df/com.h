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

	class Com
	{
	};

	template<typename TCOM>
	class Mgr
	{


	private:



	};


	static constexpr int32_t g_blockSize = 8192;

	// TODO: Maybe merge Block and BlockData. I foget the split here

	template<typename T, int count = g_blockSize>
	class BlockData
	{
	public:
		std::array<T, count> m_v;
	};

	template<typename T, int count = g_blockSize>
	class Block
	{
	public:
		BlockData<T, count> m_data;
	};

	enum class EBlockStatus: uint8_t
	{
		Invalid = 0,
		Active = 1,
		Inactive = 2,

	};

	template <typename Enumeration>
	constexpr auto as_int(const Enumeration value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}

	enum class BlockTupleIndexEnum;

	typedef Index<BlockTupleIndexEnum> BlockTupleIndex;
	//typedef uint32_t BlockTupleIndex;


	template<typename TEnum, typename ...Args>
	class BlockTuple
	{
	public:
		typedef std::tuple<EBlockStatus, ent::EntityId, Args...> TIndividualTuple;
		typedef std::tuple<Block<EBlockStatus>, Block<ent::EntityId>, Block<Args>...> TBlockTuple;

		static_assert(as_int(TEnum::Status) == 0, "");
		static_assert(as_int(TEnum::EntityId) == 1, "");

		BlockTuple()
		{
			m_pSrc = &m_blocks_0;
			m_pDst = &m_blocks_1;
		}

		template<uint32_t tupleIndex, typename T, typename... TArgs>
		void setSingle_r(const BlockTupleIndex index, const T v, TArgs... FArgs)
		{
			setSingle_r<tupleIndex>(index, std::move(v));

			setSingle_r<tupleIndex - 1>(index, FArgs...);
		}

		template<uint32_t tupleIndex, typename T>
		void setSingle_r(const BlockTupleIndex index, const T v)
		{
			std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>(*m_pSrc).m_data.m_v[index] = std::move(v);
			std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>(*m_pDst).m_data.m_v[index] = std::move(v);
		}

		void init(const BlockTupleIndex index, const ent::EntityId id, Args...args)
		{
			setSingle_r<std::tuple_size<TBlockTuple>::value - 1>(index, args...);

			std::get<as_int( TEnum::Status )>( *m_pSrc ).m_data.m_v[index] = EBlockStatus::Active;
			std::get<as_int( TEnum::EntityId )>( *m_pSrc ).m_data.m_v[index] = id;

			std::get<as_int( TEnum::Status )>( *m_pDst ).m_data.m_v[index] = EBlockStatus::Active;
			std::get<as_int( TEnum::EntityId )>( *m_pDst ).m_data.m_v[index] = id;
		}

		void init(const BlockTupleIndex index, const typename TIndividualTuple& tuple)
		{
			setFromTuple<std::tuple_size<TIndividualTuple>::value - 1>(index, tuple);
		}


		template<uint32_t tupleIndex>
		void makeRoom(const BlockTupleIndex index, const BlockTupleIndex max)
		{
			const i32 count = max - index;

			const i32 dataSize = count * sizeof( decltype( std::get<tupleIndex>( *m_pSrc ).m_data.m_v[index] ) );

			{
				auto* pStart = &std::get<tupleIndex>( *m_pSrc ).m_data.m_v[index];
				auto* pDest = pStart + 1;
				memmove( pDest, pStart, dataSize );
			}

			{
				auto* pStart = &std::get<tupleIndex>( *m_pDst ).m_data.m_v[index];
				auto* pDest = pStart + 1;
				memmove( pDest, pStart, dataSize );
			}


		}


		template<uint32_t tupleIndex>
		void insertAtBlock(const BlockTupleIndex index, const BlockTupleIndex max)
		{
			makeRoom<tupleIndex>(index, max);

			insertAtBlock<tupleIndex - 1>(index, max);
		}

		template<>
		void insertAtBlock<0>(const BlockTupleIndex index, const BlockTupleIndex max)
		{
			makeRoom<0>(index, max);
		}

		void insertAt(const BlockTupleIndex index, const BlockTupleIndex max, const ent::EntityId id, Args...args)
		{
			insertAtBlock<std::tuple_size<TIndividualTuple>::value - 1>( index, max );

			init( index, id, args...);
		}

		BlockTupleIndex findBestIndexFor( const ent::EntityId id, const BlockTupleIndex max ) const
		{
			const auto &data = std::get<as_int( TEnum::EntityId )>( *m_pDst ).m_data.m_v;

			for( BlockTupleIndex i = (BlockTupleIndex)0; i < max; ++i )
			{
				if( data[i] >= id ) return i;
			}

			return max;
		}

		template<TEnum tIndex, typename T>
		__declspec(restrict)T* src()
		{
			return std::get<tIndex>(*m_pSrc).m_data.m_v.data();
		}

		template<TEnum tIndex, typename T>
		__declspec(restrict)T* dst()
		{
			return std::get<tIndex>(*m_pDst).m_data.m_v.data();
		}

		void swap()
		{
			auto pTmp = m_pSrc;
			m_pSrc = m_pDst;
			m_pDst = pTmp;
		}

	public:


		template <uint32_t tupleIndex >
		void setFromTuple(const BlockTupleIndex index, const typename TIndividualTuple& tuple)
		{
			setFromTuple<tupleIndex - 1>(index, tuple);

			const auto v = std::get<tupleIndex>(tuple);

			std::get<tupleIndex>(*m_pSrc).m_data.m_v[index] = v;
			std::get<tupleIndex>(*m_pDst).m_data.m_v[index] = v;
		}

		template<>
		void setFromTuple<0>(const BlockTupleIndex index, const typename TIndividualTuple& tuple)
		{
			const auto v = std::get<0>(tuple);

			std::get<0>(*m_pSrc).m_data.m_v[index] = v;
			std::get<0>(*m_pDst).m_data.m_v[index] = v;
		}


		// TODO :: Change these to pointers, so things like introspection or save/load can take snapshots.  
		TBlockTuple m_blocks_0;
		TBlockTuple m_blocks_1;

		TBlockTuple* __restrict m_pSrc;
		TBlockTuple* __restrict m_pDst;

	};


	enum class BlockIndexEnum;

	typedef Index<BlockIndexEnum> BlockIndex;
	//typedef uint32_t BlockIndex;

	// The container for managing all the blocks.  
	// Each block is a non-contiguous set of data.
	// None of the blocks overlap in ID space.  
	// ???? :: Is Block Meta just a ComSet?
	template<typename TEnum, typename ...Args>
	class BlockMeta
	{
	public:

		typedef BlockTuple<TEnum, Args...> TBlock;

		// SoA for the allocated blocks

		//Count in the block (use m_block?)
		std::vector<uint32_t> m_allocated;

		//Starting index in a block.  Used for quickly tracking down an index.
		std::vector<ent::EntityId> m_start;

		//Ending index in a block
		std::vector<ent::EntityId> m_end;

		//The block itself
		std::vector<std::shared_ptr<TBlock>> m_block;

		BlockMeta()
		{
			createNewBlock();
		}

		BlockIndex find( const ent::EntityId entityId )
		{
			for( i32 i = 0; i < m_end.size() - 1; ++i )
			{
				if( entityId < m_end[i] )
				{
					return BlockIndex(i);
				}
			}

			return BlockIndex(m_end.size() - 1);
		}

		BlockIndex createNewBlock()
		{
			BlockIndex iBlock = BlockIndex(cast<BlockIndex::Base>(m_allocated.size()));

			m_allocated.push_back(0);
			m_start.push_back(ent::EntityId::invalid);
			m_end.push_back(ent::EntityId::invalid);
			m_block.push_back(std::make_shared<BlockTuple<TEnum, Args...>>());

			return iBlock;
		}

		BlockIndex append(const ent::EntityId entityId, Args... args)
		{
			auto curBlock = BlockIndex(m_allocated.size() - 1);

			if( m_allocated.back() < g_blockSize )
			{
				const auto newIndex = BlockTupleIndex(m_allocated.back());

				m_allocated.back()++;

				m_end.back() = entityId.next();
				m_block.back()->init(newIndex, entityId, args...);

				return curBlock;
			}

			createNewBlock();

			m_start.back() = entityId;

			return append(entityId, args...);
		}

		// DUPE :: Of above, but with a tuple
		BlockIndex append(const typename TBlock::TIndividualTuple& tuple)
		{
			auto curBlock = BlockIndex(cast<BlockIndex::Base>(m_allocated.size() - 1));

			const auto entId = std::get<1>(tuple);

			if( m_allocated.back() < g_blockSize )
			{
				const auto newIndex = BlockTupleIndex(m_allocated.back());


				m_allocated.back()++;

				m_end.back() = entId.next();
				m_block.back()->init(newIndex, tuple);

				return curBlock;
			}

			createNewBlock();

			m_start.back() = entId;

			return append(tuple);
		}

		BlockTupleIndex insert(const ent::EntityId entityId, Args... args)
		{
			const BlockIndex bi = find( entityId );

			const std::shared_ptr<TBlock> &block = m_block[bi];

			const BlockTupleIndex maxIndex = (BlockTupleIndex)m_allocated[bi];

			const BlockTupleIndex tupleIndex =block->findBestIndexFor( entityId, maxIndex );

			block->insertAt( tupleIndex, maxIndex, entityId, args...);

			m_allocated[bi]++;

			return tupleIndex;
		}
	};

#define Src( COM, TYPE, VAR ) const auto * pSrc##VAR = COM.src<Com##COM::VAR, TYPE>()


#define Dst( COM, TYPE, VAR ) auto * pDst##VAR = COM.dst<Com##COM::VAR, TYPE>()





	// ???? :: This is just a wrapper for BlockMeta right now.  Remove?
	template<typename TEnum, typename ...Args>
	class ComBlocks
	{
	public:
		typedef BlockMeta<TEnum, Args...> AllBlocks;

		typedef typename AllBlocks::TBlock::TIndividualTuple TTuple;

		ComBlocks()
		{
		}


		BlockTupleIndex insert(const ent::EntityId id, Args ...args)
		{
			return m_blocks.insert(id, args...);
		}

		BlockIndex append(const ent::EntityId id, Args ...args)
		{
			return m_blocks.append(id, args...);
		}

		AllBlocks m_blocks;

	protected:



	};


	/*
	template<typename TPrimary, typename ...Args>
	class ComSet
	{
	public:


		template< uint32_t tupleIndex, typename TSecondary >
		void insertSecondary( const BlockIndex iBlock, const TSecondary * const pSecondary )
		{
			if ( pSecondary )
			{
				std::get<tupleIndex>( m_secondaries ).m_com.m_blocks.insert( iBlock, *pSecondary );
			}
		}

		template< uint32_t tupleIndex, typename TSecondary, typename ...TSecondaryRest >
		void insertSecondary( const BlockIndex iBlock, const TSecondary * const pSecondary, const TSecondaryRest * const ... pRest )
		{
			insertSecondary<tupleIndex>( iBlock, pSecondary );

			insertSecondary<tupleIndex + 1>( iBlock, pRest... );
		}


		template< typename ...TTuples >
		void insert( const typename TPrimary::TCom::TTuple &primary, const TTuples * const ... pArgs )
		{
			const auto primaryBlockIndex = m_primary.m_com.m_blocks.append( primary );

			insertSecondary<0>( primaryBlockIndex, pArgs... );

		}

	protected:
		TPrimary m_primary;
		std::tuple<Args...> m_secondaries;

	};
	*/

	extern void timeBlocks(const i32 numLoops, const i32 numEnts, u32* timeSoAIndividualuS, u32* timeAoSuS, u32* timeSoA3uS, u32* timeSoA4uS);


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


		typedef ComBlocks<ComDynamicBlocks::EDynamicSlots, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar, Scalar> TCom;

		TCom m_com;

	public:

		int updateBlock(const uint64_t dtMs, TCom::AllBlocks::TBlock& blocks);

		void update(const uint64_t dtMs);
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


		typedef ComBlocks<ComDynamicBlocksVec3::EDynamicSlots, TVec, TVec> TCom;

		TCom m_com;

	public:

		int updateBlock(const uint64_t dtMs, TCom::AllBlocks::TBlock& blocks);

		void update(const uint64_t dtMs);
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


		typedef ComBlocks<ComDynamicBlocksVec4::EDynamicSlots, TVec, TVec> TCom;

		TCom m_com;

	public:

		int updateBlock(const uint64_t dtMs, TCom::AllBlocks::TBlock& blocks);

		void update(const uint64_t dtMs);
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

		typedef ComBlocks<ComDynamicBlocksAoS::EDynamicSlots, ComDynamicBlocksAoS::Physical> TCom;

		TCom m_com;

	public:

		int updateBlock(const uint64_t dtMs, TCom::AllBlocks::TBlock& blocks);

		void update(const uint64_t dtMs);
	};


}