//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once




class AbsoluteTime
{

public:
	
	REFLECT_BEGIN_ROOT( AbsoluteTime );
		REFLECT( m_time );
	REFLECT_END();

	operator double() const
	{
		return m_time;
	}


private:
	friend AbsoluteTime GetAbsoluteTime_internal();
	friend AbsoluteTime cast_from_string_helper( const char * const pStr );


	AbsoluteTime( const double time );

	double m_time;

};

inline AbsoluteTime cast_from_string_helper( const char * const pStr )
{
	return AbsoluteTime( atof( pStr ) );
}


template<>
inline AbsoluteTime cast_from_string( const char * const pStr )
{
	return cast_from_string_helper( pStr );
}


namespace Clock
{
	void AppStart();
	void AppStop();
	
	void Tick();

	AbsoluteTime GetAbsoluteTime();
	
	float dt();



}














// -