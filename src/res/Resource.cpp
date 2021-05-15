//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"



#include "./Resource.h"

#include "./ResourceMgr.h"

//#include "../util/Clock.h"

Resource::Resource()
	:
	m_lastUsedTime( Clock::GetAbsoluteTime() )
{
}

Resource::~Resource(void)
{
}


void Resource::ResourceMgr_setFilename( const util::RuntimeString &filename )
{
	m_filename = filename;
}

void Resource::use()
{
	m_lastUsedTime = Clock::GetAbsoluteTime();
}

void Resource::onPreLoad()
{
}

void Resource::onPostLoad()
{
}

void Resource::onPreChange()
{
}

void Resource::onPostChange()
{
}
