//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "stdafx.h"



#include "./Clock.h"

#include <cblib/timer.h>

static double s_lastTime;
static double s_currentTime;
static double s_deltaTime;

AbsoluteTime::AbsoluteTime( const double time )
	:
	m_time( time )
{
}



void Clock::AppStart()
{
	s_currentTime = cb::Timer::GetSeconds();
	s_deltaTime = ( 1. / 60. );
	s_lastTime = s_currentTime - ( 1. / 60. );
}

void Clock::AppStop()
{
}

void Clock::Tick()
{
	s_lastTime = s_currentTime;
	s_currentTime = cb::Timer::GetSeconds();
	
	s_deltaTime = s_currentTime - s_lastTime;
}

AbsoluteTime GetAbsoluteTime_internal()
{
	return AbsoluteTime( cb::Timer::GetSeconds() );
}

AbsoluteTime Clock::GetAbsoluteTime()
{
	return GetAbsoluteTime_internal();
}

float Clock::dt()
{
	return s_deltaTime;
}










// -