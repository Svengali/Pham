//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
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

enum class EBlockStatus : uint8_t
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


template<typename TEnum, typename ...Args>
class BlockTuple
{
public:
    typedef std::tuple<EBlockStatus, ent::EntityId, Args...> TIndividualTuple;
    typedef std::tuple<Block<EBlockStatus>, Block<ent::EntityId>, Block<Args>...> TBlockTuple;

    static_assert( as_int( TEnum::Status ) == 0, "" );
    static_assert( as_int( TEnum::EntityId ) == 1, "" );

    BlockTuple()
    {
        m_pSrc = &m_blocks_0;
        m_pDst = &m_blocks_1;
    }

    template<uint32_t tupleIndex, typename T, typename... TArgs>
    void setSingle( const BlockTupleIndex index, const T v, TArgs... FArgs )
    {
        setSingle<tupleIndex>( index, v );

        setSingle<tupleIndex - 1>( index, FArgs... );
    }

    template<uint32_t tupleIndex, typename T>
    void setSingle( const BlockTupleIndex index, const T v )
    {
        std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>( *m_pSrc ).m_data.m_v[index] = v;
        std::get<std::tuple_size<TBlockTuple>::value - tupleIndex + 1>( *m_pDst ).m_data.m_v[index] = v;
    }

    void init( const BlockTupleIndex index, const ent::EntityId id, Args...args )
    {
        setSingle<std::tuple_size<TBlockTuple>::value - 1>( index, args... );

        std::get<as_int( TEnum::Status )>( *m_pDst ).m_data.m_v[index] = EBlockStatus::Active;
        std::get<as_int( TEnum::EntityId )>( *m_pDst ).m_data.m_v[index] = id;
	}

	void init( const BlockTupleIndex index, const typename TIndividualTuple &tuple )
	{
		setFromTuple<std::tuple_size<TIndividualTuple>::value - 1>( index, tuple );
	}




    /*
    void setFromArgs( const uint32_t index, const ent::EntityId id, Args...args )
    {
        //setSingle<std::tuple_size<TTuple>::value - 1>( index, args... );

        //std::get<as_int( TEnum::Status )>( m_blocks ).m_data.m_v[index] = EBlockStatus::Active;

        //std::assert( std::get<as_int( TEnum::EntityId )>( m_blocks ).m_data.m_v[index] == id );
    }

    template< uint32_t tIndex>
    void blockToIndividual( TIndividualTuple * const pInd, const uint32_t index )
    {
        //std::get<tIndex>( *pInd ) = std::get<tIndex>( m_blocks ).m_data.m_v[index];

        //blockToIndividual<tIndex - 1>(pInd, index);
    }

    template<>
    void blockToIndividual<0>( TIndividualTuple * const pInd, const uint32_t index )
    {
        std::get<0>( *pInd ) = std::get<0>( m_blocks ).m_data.m_v[index];
    }
    */

	/*
	TIndividualTuple getIndividual( const uint32_t index )
	{
		TIndividualTuple ind;

		getSetIndividual<std::tuple_size<TTuple>::value - 1>( &ind, index );

		return ind;
	}
	*/

	/*
	TIndividualTuple remIndividual( const ent::EntityId id )
	{

	}
	*/

    template<TEnum tIndex, typename T>
	__declspec(noalias) T *src()
    {
        return std::get<tIndex>( *m_pSrc ).m_data.m_v.data();
    }

    template<TEnum tIndex, typename T>
	__declspec(noalias) T *dst()
    {
        return std::get<tIndex>( *m_pDst ).m_data.m_v.data();
    }


    /*
    template<uint32_t tIndex, typename T>
    void getPointer( T **ppT )
    {
        *ppT = std::get<tIndex>( m_blocks ).m_data.m_v.data();
    }

    template<uint32_t tIndex, typename T, typename... TArgs>
    void getPointer( T **ppT, TArgs **...ppArgs )
    {
        getPointer<tIndex>(ppT);
        getPointer<tIndex - 1>( ppArgs... );
    }


    void getPointers( EBlockStatus **ppBS, ent::EntityId **ppEnt, Args **...ppArgs)
    {
        getPointer<std::tuple_size<TBlockTuple>::value - 1>(ppArgs...);

        getPointer<1>( ppEnt );
        getPointer<0>( ppBS );
    }
    */

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


	// TODO :: Change these to pointers, so things like introspection or save/load can take snapshots.  
    TBlockTuple m_blocks_0;
    TBlockTuple m_blocks_1;

    TBlockTuple * __restrict m_pSrc;
    TBlockTuple * __restrict m_pDst;

};

/*
template<typename TEnum>
class BlockIndex
{
public:
    BlockIndex( uint32_t block, uint32_t index )
        :
        m_block( block ),
        m_index( index )
    {
    }



private:
    uint32_t m_block = -1;
    uint32_t m_index = -1;

};
*/


enum class BlockIndexEnum;

typedef Index<BlockIndexEnum> BlockIndex;
//typedef uint32_t BlockIndex;

// ???? :: Is Block Meta just a ComSet?
template<typename TEnum, typename ...Args>
class BlockMeta
{
public:

    typedef BlockTuple<TEnum, Args...> TBlock;

    std::vector<uint32_t> m_allocated;

    std::vector<ent::EntityId> m_start;
    std::vector<ent::EntityId> m_end;

    std::vector<std::shared_ptr<TBlock>> m_block;

	BlockMeta()
	{
		createNewBlock();
	}

	/*
	BlockTupleIndex appendNewBlock( const ent::EntityId initialEntityId, Args... args )
    {
        m_allocated.push_back( 1 );
        m_start.push_back( initialEntityId );
        m_end.push_back( initialEntityId.next() );
        m_tuple.push_back( std::make_shared<BlockTuple<TEnum, Args...>>() );
        m_tuple.back()->init( BlockTupleIndex(0), initialEntityId, args... );

		return BlockTupleIndex( 0 );
    }

	BlockTupleIndex appendNewIndex( const ent::EntityId entityId, Args... args )
    {
        const auto newIndex = BlockTupleIndex(m_allocated.back());

        m_allocated.back()++;

        m_end.back() = entityId.next();
        m_tuple.back()->init( newIndex, entityId, args... );

		return newIndex;
	}
	*/



	/*
    bool remove( const ent::EntityId entityId )
    {
        const int32_t blockCount = cast<int32_t>(m_allocated.size());

        for( int32_t i = 0; i < blockCount; ++i )
        {
            if (entityId >= m_start[i] & entityId <= m_end[i])
            {
                ent::EntityId * pEnt = m_tuple[i].src<0, ent::EntityId>();
            }
        }
    }
	*/

	BlockIndex createNewBlock()
	{
		BlockIndex iBlock = BlockIndex( cast<BlockIndex::Base>( m_allocated.size() ) );

		m_allocated.push_back( 0 );
		m_start.push_back( ent::EntityId::invalid );
		m_end.push_back( ent::EntityId::invalid );
		m_block.push_back( std::make_shared<BlockTuple<TEnum, Args...>>() );

		return iBlock;
	}

	BlockIndex append( const ent::EntityId entityId, Args... args )
	{
		auto curBlock = BlockIndex( m_allocated.size() - 1 );

		if ( m_allocated.back() < g_blockSize )
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

		if( m_allocated.back() < g_blockSize )
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

	void insert( BlockIndex iBlock, const typename TBlock::TIndividualTuple &tuple )
	{
		if ( iBlock < m_allocated.size() )
		{
			if( m_start[iBlock] == ent::EntityId::invalid ) 
			{
				m_start[iBlock] = std::get<1>( tuple );
			}

			append( tuple );

			return;
		}

		while( iBlock >= m_allocated.size() )
		{
			createNewBlock();
		}

		insert( iBlock, tuple );
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


    BlockIndex append( ent::EntityId id, Args ...args )
    {
		return m_blocks.append( id, args... );
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

	typedef float SpecialType;


	typedef ComBlocks<ComDynamicBlocks::EDynamicSlots, SpecialType, SpecialType, SpecialType, SpecialType, SpecialType, SpecialType, SpecialType, SpecialType> TCom;

	TCom m_com;

public:

	int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

	void update( const uint64_t dtMs );
};


class ComDynamicBlocksVec
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

	typedef cb::Vec3 SpecialType;


	typedef ComBlocks<ComDynamicBlocksVec::EDynamicSlots, SpecialType, SpecialType> TCom;

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

    typedef float SpecialType;


    struct Physical
    {
        SpecialType x;
        SpecialType y;
        SpecialType z;
        //SpecialType w;
        SpecialType dx;
        SpecialType dy;
        SpecialType dz;
        //SpecialType dw;
    };

public:

    typedef ComBlocks<ComDynamicBlocksAoS::EDynamicSlots, ComDynamicBlocksAoS::Physical> TCom;

    TCom m_com;

public:

    int updateBlock( const uint64_t dtMs, TCom::AllBlocks::TBlock &blocks );

    void update( const uint64_t dtMs );
};


}