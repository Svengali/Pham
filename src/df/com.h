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


	static constexpr int32_t g_blockSize = 1 * 1024;

	// TODO: Maybe merge Block and BlockData. I foget the split here

	template<typename T, int max>
	class BlockData
	{
	public:
		std::array<T, max> m_v;

		~BlockData()
		{
		}
	};

	template<typename T, int max>
	class Block
	{
	public:
		BlockData<T, max> m_data;
	};

	enum class EBlockStatus: uint8_t
	{
		Invalid = 0,
		Active = 1,
		Inactive = 2,

	};

	template <typename Enumeration>
	constexpr auto as_int( const Enumeration value )
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>( value );
	}

	enum class BlockTupleIndexEnum;

	typedef Index<BlockTupleIndexEnum> BlockTupleIndex;
	//typedef uint32_t BlockTupleIndex;


	template<i32 max, typename TEnum, typename ...Args>
	class BlockTuple
	{
	public:
		typedef std::tuple<EBlockStatus, ent::EntityId, Args...> TIndividualTuple;
		typedef std::tuple<Block<EBlockStatus, max>, Block<ent::EntityId, max>, Block<Args, max>...> TBlockTuple;

		static_assert( as_int( TEnum::Status ) == 0, "" );
		static_assert( as_int( TEnum::EntityId ) == 1, "" );

		BlockTuple()
		{
			m_pSrc = &m_blocks_0;
			m_pDst = &m_blocks_1;
		}

		~BlockTuple()
		{

		}

		template<uint32_t tupleIndex, typename T, typename... TArgs>
		void setSingle_r( const BlockTupleIndex index, const T v, TArgs... FArgs )
		{
			setSingle_r<tupleIndex>( index, v );

			setSingle_r<tupleIndex - 1>( index, FArgs... );
		}

		template<uint32_t tupleIndex, typename T>
		void setSingle_r( const BlockTupleIndex index, const T v )
		{
			std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>( *m_pSrc ).m_data.m_v[index] = v;
			std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>( *m_pDst ).m_data.m_v[index] = v;
		}

		void init( const BlockTupleIndex index, const ent::EntityId id, Args...args )
		{
			setSingle_r<std::tuple_size<TBlockTuple>::value - 1>( index, args... );

			std::get<as_int( TEnum::Status )>( *m_pSrc ).m_data.m_v[index] = EBlockStatus::Active;
			std::get<as_int( TEnum::EntityId )>( *m_pSrc ).m_data.m_v[index] = id;

			std::get<as_int( TEnum::Status )>( *m_pDst ).m_data.m_v[index] = EBlockStatus::Active;
			std::get<as_int( TEnum::EntityId )>( *m_pDst ).m_data.m_v[index] = id;
		}

		void init( const BlockTupleIndex index, const typename TIndividualTuple &tuple )
		{
			setFromTuple<std::tuple_size<TIndividualTuple>::value - 1>( index, tuple );
		}

		void debug_get( const BlockTupleIndex index, TIndividualTuple *pTuple )
		{
			get<std::tuple_size<TIndividualTuple>::value - 1>( pTuple, index, m_pSrc );
		}

		template<uint32_t tupleIndex>
		void makeRoom( const BlockTupleIndex index, const BlockTupleIndex max )
		{
			const i32 count = max - index;

			const i32 dataSize = count * sizeof( decltype( std::get<tupleIndex>( *m_pSrc ).m_data.m_v[index] ) );

			{
				auto *pStart = &std::get<tupleIndex>( *m_pSrc ).m_data.m_v[index];
				auto *pDest = pStart + 1;
				memmove( pDest, pStart, dataSize );
			}

			{
				auto *pStart = &std::get<tupleIndex>( *m_pDst ).m_data.m_v[index];
				auto *pDest = pStart + 1;
				memmove( pDest, pStart, dataSize );
			}
		}


		template<uint32_t tupleIndex>
		void insertAtBlock( const BlockTupleIndex index, const BlockTupleIndex max )
		{
			makeRoom<tupleIndex>( index, max );

			insertAtBlock<tupleIndex - 1>( index, max );
		}

		template<>
		void insertAtBlock<0>( const BlockTupleIndex index, const BlockTupleIndex max )
		{
			makeRoom<0>( index, max );
		}

		void insertAt( const BlockTupleIndex index, const BlockTupleIndex max, const ent::EntityId id, Args...args )
		{
			insertAtBlock<std::tuple_size<TIndividualTuple>::value - 1>( index, max );

			init( index, id, args... );
		}

		BlockTupleIndex findBestIndexFor( const ent::EntityId id, const BlockTupleIndex max ) const
		{
			const auto &data = std::get<as_int( TEnum::EntityId )>( *m_pDst ).m_data.m_v;

			for( i32 i = 0; i < (i32)max; ++i )
			{
				if( data[i] >= id ) return BlockTupleIndex( i );
			}

			return max;
		}

		template<TEnum tIndex, typename T>
		__declspec(restrict)T *src()
		{
			return std::get<tIndex>( *m_pSrc ).m_data.m_v.data();
		}

		template<TEnum tIndex, typename T>
		__declspec(restrict)T *dst()
		{
			return std::get<tIndex>( *m_pDst ).m_data.m_v.data();
		}

		void swap()
		{
			auto pTmp = m_pSrc;
			m_pSrc = m_pDst;
			m_pDst = pTmp;
		}

	public:


		template <uint32_t tupleIndex >
		void setFromTuple( const BlockTupleIndex index, const typename TIndividualTuple &tuple )
		{
			setFromTuple<tupleIndex - 1>( index, tuple );

			const auto v = std::get<tupleIndex>( tuple );

			std::get<tupleIndex>( *m_pSrc ).m_data.m_v[index] = v;
			std::get<tupleIndex>( *m_pDst ).m_data.m_v[index] = v;
		}

		template<>
		void setFromTuple<0>( const BlockTupleIndex index, const typename TIndividualTuple &tuple )
		{
			const auto v = std::get<0>( tuple );

			std::get<0>( *m_pSrc ).m_data.m_v[index] = v;
			std::get<0>( *m_pDst ).m_data.m_v[index] = v;
		}

		template <uint32_t tupleIndex >
		void get( TIndividualTuple *pTuple, const BlockTupleIndex index, TBlockTuple *pBlock )
		{
			const auto v = std::get<tupleIndex>( *pBlock ).m_data.m_v[index];
			std::get<tupleIndex>( *pTuple ) = v;

			get<tupleIndex - 1>( pTuple, index, m_pSrc );
		}

		template<>
		void get<(uint32_t)-1>( TIndividualTuple *pTuple, const BlockTupleIndex index, TBlockTuple *pBlock )
		{
		}

		// TODO :: Change these to pointers, so things like introspection or save/load can take snapshots.  
		TBlockTuple m_blocks_0;
		TBlockTuple m_blocks_1;

		TBlockTuple *__restrict m_pSrc;
		TBlockTuple *__restrict m_pDst;

	};


	enum class BlockIndexEnum;

	typedef Index<BlockIndexEnum> BlockIndex;
	//typedef uint32_t BlockIndex;

	// The container for managing all the blocks.  
	// Each block is a non-contiguous set of data.
	// None of the blocks overlap in ID space.  
	// ???? :: Is Block Meta just a ComSet?
	template<i32 max, typename TEnum, typename ...Args>
	class BlockMeta
	{
	public:

		typedef BlockTuple<max, TEnum, Args...> TBlock;

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

		~BlockMeta()
		{
		}

		BlockIndex find( const ent::EntityId entityId ) const
		{
			for( i32 i = 0; i < cast<i32>( m_end.size() ) - 1; ++i )
			{
				if( entityId < m_end[i] )
				{
					return BlockIndex( i );
				}
			}

			return BlockIndex( cast<i32>( m_end.size() ) - 1 );
		}

		BlockIndex createNewBlock()
		{
			BlockIndex iBlock = BlockIndex( cast<BlockIndex::Base>( m_allocated.size() ) );

			m_allocated.push_back( 0 );
			m_start.push_back( ent::EntityId::invalid );
			m_end.push_back( ent::EntityId::invalid );
			m_block.push_back( std::make_shared<BlockTuple<max, TEnum, Args...>>() );

			return iBlock;
		}

		BlockIndex append( const ent::EntityId entityId, Args... args )
		{
			auto curBlock = BlockIndex( m_allocated.size() - 1 );

			if( m_allocated.back() < max )
			{
				const auto newIndex = BlockTupleIndex( m_allocated.back() );

				m_allocated.back()++;

				m_end.back() = entityId.next();
				m_block.back()->init( newIndex, entityId, args... );

				return curBlock;
			}

			createNewBlock();

			m_start.back() = entityId;

			return append( entityId, args... );
		}

		// DUPE :: Of above, but with a tuple
		BlockIndex append( const typename TBlock::TIndividualTuple &tuple )
		{
			auto curBlock = BlockIndex( cast<BlockIndex::Base>( m_allocated.size() - 1 ) );

			const auto entId = std::get<1>( tuple );

			if( m_allocated.back() < max )
			{
				const auto newIndex = BlockTupleIndex( m_allocated.back() );


				m_allocated.back()++;

				m_end.back() = entId.next();
				m_block.back()->init( newIndex, tuple );

				return curBlock;
			}

			createNewBlock();

			m_start.back() = entId;

			return append( tuple );
		}

		BlockTupleIndex insert( const ent::EntityId entityId, Args... args )
		{
			const BlockIndex bi = find( entityId );

			const std::shared_ptr<TBlock> &block = m_block[bi];

			const BlockTupleIndex currentlyIndexed = (BlockTupleIndex)m_allocated[bi];

			const BlockTupleIndex tupleIndex = block->findBestIndexFor( entityId, currentlyIndexed );

			if( currentlyIndexed >= max )
			{
				//2 cases.  We need to append to the next block, or pull the last one and put it in the next block.
				if( tupleIndex >= max )
				{
					//Just call append
					const auto nbi = append( entityId, args... );

					// @@@ HACK this is just broken
					return tupleIndex;
				}
				else
				{
					// PERF We move 1 tuple at a time, since that use case is likely the most common.
					TBlock::TIndividualTuple tuple;
					BlockTupleIndex lastIndex( max - 1 );

					block->debug_get( tupleIndex, &tuple );

					// @@@@ HACK! This should be an insert!  
					append( tuple );

					//Continue down now that we have space.
				}
			}


			block->insertAt( tupleIndex, currentlyIndexed, entityId, args... );

			m_allocated[bi]++;

			return tupleIndex;
		}

		void debug_get( const ent::EntityId entityId, typename TBlock::TIndividualTuple *pTuple )
		{
			const BlockIndex bi = find( entityId );
			const std::shared_ptr<TBlock> &block = m_block[bi];
			const BlockTupleIndex currentlyIndexed = (BlockTupleIndex)m_allocated[bi];
			const BlockTupleIndex tupleIndex = block->findBestIndexFor( entityId, currentlyIndexed );

			block->debug_get( tupleIndex, pTuple );
		}


	};

#define Src( COM, TYPE, VAR ) const __restrict auto * pSrc##VAR = COM.src<Com##COM::VAR, TYPE>()


#define Dst( COM, TYPE, VAR ) __restrict auto * pDst##VAR = COM.dst<Com##COM::VAR, TYPE>()





	// ??? :: This is just a wrapper for BlockMeta right now.  Remove?
	template<i32 max, typename TEnum, typename ...Args>
	class ComBlocks
	{
	public:
		typedef BlockMeta<max, TEnum, Args...> AllBlocks;

		typedef typename AllBlocks::TBlock::TIndividualTuple TIndividualTuple;

		ComBlocks()
		{
		}

		~ComBlocks()
		{
		}


		BlockTupleIndex insert( const ent::EntityId id, Args ...args )
		{
			return m_blocks.insert( id, args... );
		}

		BlockIndex append( const ent::EntityId id, Args ...args )
		{
			return m_blocks.append( id, args... );
		}

		//Dont use this.
		void debug_get( const ent::EntityId id, TIndividualTuple *pTuple )
		{
			m_blocks.debug_get( id, pTuple );
		}

		AllBlocks m_blocks;
	};



}