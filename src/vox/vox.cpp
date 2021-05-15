//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#include "vox.h"
#include "../math/SimplexNoise.h"




vox::LPos vox::LPos::from( const vox::CPos cPos, const vox::GPos gPos )
{
	const auto chunkBase_gPos = GPos::from( cPos );

	const auto lPos = gPos - chunkBase_gPos;

	return lPos;
}

vox::LPos vox::GPos::operator -( const vox::GPos pos ) const
{
	return vox::LPos( x - pos.x, y - pos.y, z - pos.z );
}

vox::GPos vox::GPos::operator +( const vox::LPos pos ) const
{
	return vox::GPos( x + pos.x, y + pos.y, z + pos.z );
}

vox::GPos vox::GPos::operator +( const cb::Vec3i pos ) const
{
	return vox::GPos( x + pos.x, y + pos.y, z + pos.z );
}



vox::GPos vox::GPos::from( const CPos pos )
{
	// TODO CHUNK SIZE
	return GPos( pos.x * 16, pos.y * 16, pos.z * 16 );
}







template< typename T >
class Value
{
public:

	typedef typename T TYPE;

	Value( const T &v )
		:
		m_v( v )
	{
	}

	explicit operator T() const
	{
		return m_v;
	}

	T operator =( const T &v )
	{
		m_v = v;
		return m_v;
	}

private:
	T m_v;
};

template< typename SUPER >
class ValuePrint : public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValuePrint( const T &v )
		:
		SUPER( v )
	{
	}

	explicit operator T() const
	{
		return cast<T>(*(SUPER *)this);
	}

	T operator =( const T &v )
	{
		const T &oldVal = cast<T>(*this);

		std::cout << "Old value:" << oldVal << std::endl;
		const auto newVal = SUPER::operator =(v);
		std::cout << "New value:" << newVal << std::endl;

		return newVal;
	}


private:

};

template< typename T >
T clamp(T v, T min, T max)
{
	return std::min( max, std::max(v, min) );
}

template< class SUPER, typename SUPER::TYPE min, typename SUPER::TYPE max >
class ValueRange: public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValueRange( const T &v )
		:
		SUPER( v )
	{
	}

	explicit operator T() const
	{
		const auto v = cast<T>( *(SUPER *)this );
		return clamp(v, min, max);
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		return clamp( newVal, min, max );
	}


private:

};


template< typename SUPER >
class ValueRangeFloat: public SUPER
{
public:
	typedef typename SUPER::TYPE T;

	ValueRangeFloat( const T &v )
		:
		SUPER( v )
	{
	}

	T m_min;
	T m_max;

	ValueRangeFloat<SUPER> &initRangeFloat(const T min, const T max)
	{
		m_min = min;
		m_max = max;
		return *this;
	}

	explicit operator T() const
	{
		const auto v = cast<T>( *(SUPER *)this );
		return clamp( v, m_min, m_max );
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		return clamp( newVal, m_min, m_max );
	}


private:

};


template< typename SUPER >
class ValueTrack: public SUPER
{
public:

	typedef typename SUPER::TYPE T;

	ValueTrack( const T &v )
		:
		SUPER( v )
	{
	}

	T operator =( const T &v )
	{
		const auto newVal = SUPER::operator =( v );
		m_changedSinceChecked = true;
		return newVal;
	}

	bool hasChanged()
	{
		const auto changed = m_changedSinceChecked;
		m_changedSinceChecked = false;
		return changed;
	}

private:
	bool m_changedSinceChecked = false;
};



template< typename SUPER >
class ValueOnChange: public SUPER
{
public:

	typedef typename SUPER::TYPE T;

	ValueOnChange( const T &v )
		:
		SUPER( v )
	{
	}

	ValueOnChange<SUPER> &initOnChange( std::function<void( T, T )> fn )
	{
		m_fn = fn;
		return *this;
	}

	T operator =( const T &v )
	{
		const auto oldV = cast<T>( *(SUPER *)this );

		const auto newV = SUPER::operator =( v );

		m_fn( oldV, newV );

		return newV;
	}

private:
	std::function<void(T, T)> m_fn;
};

template< class TValue >
void doSomething( TValue &v )
{

	const auto v_1 = cast<TValue::TYPE>(v);

	std::cout << "Do something on " << v_1 << std::endl;

}

void testImmutables();



void vox::testVox()
{

	//CubitPlane plane;

	//plane.genWorld( cb::Vec3( 55.4f, 72.3f, 14.4f ) );

	//testDatatypes();

	testImmutables();

}


void testDatatypes()
{
	//*
	/*
	TPos<0> pos;
	TPos<0> pos_2;

	TPos<1> cubePos;

	pos_2 = pos;

	cubePos = pos.up();

	pos_2 = cubePos.down();
	*/

	ValuePrint<ValueRange<ValueTrack<Value<i32>>, 10, 20>> val( 100 );

	const auto change_0 = val.hasChanged();

	val = 200;

	const auto change_1 = val.hasChanged();

	const auto change_2 = val.hasChanged();

	const auto v_0 = cast<i32>( val );

	val = -100;

	doSomething( val );


	const auto v_1 = cast<i32>( val );


	auto val_f_1 = ValuePrint<ValueOnChange<ValueRangeFloat<ValueTrack<Value<f32>>>>>( 100.0f )
	.initOnChange( []( f32 oldV, f32 newV ) {
		std::cout << "Value is changing from " << oldV << " " << newV << std::endl;
	} ).initRangeFloat( 35, 75 );

	doSomething( val_f_1 );

	//auto connect = FSMRetry<10, FSMExponentialBackoff<FSMTimeout<1000, <FSMState>>>>();



	val_f_1 = -50;


	doSomething( val_f_1 );

	/*
	auto port = ValueOnChange<ValueRange<Value<i32>, 1024, 65536>>>( 100 );

	port.ValueOnChange::init( []( i32 oldV, i32 newV ) {

		//kill current listen port, then remake it

	} );
	*/



	//*/

}

#include <string>

template <typename Value, typename Struct>
struct param
{
	const Value Struct::*pmd;
	Value value;

	void set( Struct &s )
	{
        //This is hinky, but necessary
        Value Struct::*pmd_nc = (Value Struct::*)pmd;

        s.*pmd_nc = std::move(value);
	}
};

template <typename Value, typename Struct>
param<Value, Struct> with( const Value Struct::*pmd, Value value )
{
	return param<Value, Struct>{pmd, value};
}

template <typename T, typename... Params>
T copy( const T &val, Params &&...params )
{
	T value_copy = val;

	( params.set( value_copy ), ... );

	return value_copy;
}

template< typename T >
struct Imm
{
    /*
    template <typename Value>
    param<Value, T> with(const Value T::*pmd, const Value value)
    {
        return param<Value, Struct>{pmd, value};
    }
	*/



	template <typename Value>
	T with(const Value T::*pmd, Value value)
    {
        return param<Value, T>{pmd, value}.set(this);
    }

};


struct ImmPerson : public Imm<ImmPerson>
{
	//using Imm::Imm;
    //ImmPerson() = default;

	ImmPerson(std::string _name, int _age)
		:
		name(_name),
		age(_age)
	{

	}

    const std::string name;
    const int         age;
};

struct Person {
	const std::string name;
	const int age;
};

struct Person_nc
{
    std::string name;
    int         age;
};

void testImmutables()
{
    ImmPerson immP1 { "hello", 32 };

	//immP1.with(&ImmPerson::name, std::string("name2"));


	Person p1{ "name1", 25 };
	Person p2 = copy( p1,
		with( &Person::name, std::string( "name2" ) ),
		with( &Person::age, -21 )
		);

	Person p5 = p1;


	
	//Illegal
	//p1.name = "badname";

	const Person_nc p3 { "name3", 43 };

	Person_nc p4 = copy(p3, with(&Person_nc::name, std::string("name4")));

	Person_nc p6;


	//Also illegal, but requires every use case to use const
	//p3.name = "badname";
	
}
