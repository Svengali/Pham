//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"


#include ".\ResourceMgr.h"

#include "Resource.h"

#include <hash_map>

typedef unsigned long DWORD;

#include "../../../cblib/DirChangeWatcher.h"

//std::hash_map< util::Symbol 

typedef stdext::hash_map< util::Symbol, ResourceMgr::FnCreator > MapTypeToCreator;

typedef stdext::hash_map< util::Symbol, MapTypeToCreator > MapExtToMapTypeToCreator;


static MapExtToMapTypeToCreator s_mapExtToCreator;

static stdext::hash_map< util::Symbol, ResourcePtr > s_mapSymToResource;

static AbsoluteTime m_curTime = Clock::GetAbsoluteTime();


const util::Symbol s_DEBUG_breakOn("config/geo/test.xml");



std::vector< const char * > s_watchDir;
cb::DirChangeWatcherPtr    s_watcher;

void ResourceMgr::AppStart()
{
	m_curTime = Clock::GetAbsoluteTime();
	
	s_watchDir.push_back( "." );

	s_watcher = cb::StartWatchingDirs( &s_watchDir[0], s_watchDir.size(), 0xf );
	
}


void ResourceMgr::AppStop()
{
	//stdext::hash_map< util::Symbol, ResourcePtr >::iterator it = s_mapSymToResource.begin();
	
	//++it;
	
	//ResourcePtr res = it->second;

	s_watcher = NULL;
	
	const util::Symbol sym("config/geo/test.xml");

	const auto res = s_mapSymToResource[sym];

	s_mapSymToResource.clear();
	
	s_mapExtToCreator.clear();
	
	
}

void ResourceMgr::RegisterCreator( const char * const pExt, const util::Symbol &type, FnCreator func )
{
	const util::Symbol extSym( pExt );
	
	/*
	// TODO: ifdef debug?
	for( int i=0; i<s_mapExtToCreator.size(); ++i )
	{
		MapExtToMapTypeToCreator::iterator it = s_mapExtToCreator.find( extSym );
		
		if( it != s_mapExtToCreator.end() )
		{
//			gLog::Error( "Extension %s already registered.\n", pExt );
			return;
		}
	}
	*/
	
	s_mapExtToCreator[ extSym ][type] = func;
}



void GetTail( const char * const pStr, char * const pBuf, const int maxLen )
{
	const int strLen = cast<int>( strlen( pStr ) );
	
	int strIndex = strLen - 1;
	int extIndex = 0;
	
	while( extIndex < (maxLen - 1) && extIndex < strLen && pStr[ strIndex ] != '.' )
	{
		pBuf[ extIndex ] = pStr[ strIndex ];
		--strIndex;
		++extIndex;
	}
	
	ASSERT( extIndex <= strLen );
	ASSERT( extIndex < maxLen );

	if( pStr[ strIndex ] == '.' )
	{
		pBuf[ extIndex ] = 0;
		
		//If we have any chars, reverse the string.
		if( extIndex > 1 )
		{
			//Index of the last char.
			--extIndex;
			for( int i=0; i<extIndex; ++i, --extIndex )
			{
				char temp = pBuf[ i ];
				pBuf[ i ] = pBuf[ extIndex ];
				pBuf[ extIndex ] = temp;
			}
		}
	}
	else
	{
		pBuf[0]=0;
	}
}

const int c_maxExt = 16;

void ResourceMgr::AddResource( const char *const pResName, const ResourcePtr &ptr )
{
	//15 max chars on an extension plus 0
	char extBuf[c_maxExt];

	GetTail( pResName, extBuf, c_maxExt );

	const util::Symbol extSym( extBuf );

	const util::Symbol resSym( pResName );

	if( s_DEBUG_breakOn == resSym )
	{
		int dummy = 0;
	}

	const auto it = s_mapSymToResource.find( resSym );

	if( it == s_mapSymToResource.end() )
	{
		s_mapSymToResource[resSym] = ptr;

		ptr->onPostLoad();
	}
	else
	{
		// TODO LOG
		// Replace?
	}
}


ResourcePtr ResourceMgr::LookupResource( const char * const pResName )
{
	//15 max chars on an extension plus 0
	char extBuf[ c_maxExt ];

	GetTail( pResName, extBuf, c_maxExt );

	const util::Symbol extSym( extBuf );

	const util::Symbol resSym( pResName );

	const auto it = s_mapSymToResource.find( resSym );

	if( it == s_mapSymToResource.end() )
	{
		return nullptr;
	}

	return it->second;
}

ResourcePtr ResourceMgr::GetResource( const char *const pResName, const ResCreator *const pCreator )
{
	//lprintf( "Get res %s\n", pResName );

	//15 max chars on an extension plus 0
	char extBuf[c_maxExt];

	GetTail( pResName, extBuf, c_maxExt );

	const util::Symbol extSym( extBuf );

	const util::Symbol resSym( pResName );

	ResourcePtr resource; // = s_MapTknToResource[ resTkn ];

	//HACK: scripts create new resources when loaded.
	if( extSym != util::Symbol( "script" ) )
	{
		resource = s_mapSymToResource[resSym];
	}

	if( resource != NULL )
	{
		return resource;
	}

	resource = pCreator->create();

	if( resource != NULL && resSym != util::Symbol::Empty() )
	{
		lprintf( "Storing res %s\n", pResName );

		const i64 resCount1 = resource.use_count();

		s_mapSymToResource[resSym] = resource;
		resource->onPostLoad();

		const i64 resCount2 = resource.use_count();

		resource->ResourceMgr_setFilename( util::RuntimeString( pResName ) );
	}

	return resource;
}

void ResourceMgr::RemResource( const char *const pResName )
{
	const util::Symbol resSym( pResName );

	const auto removed = s_mapSymToResource.erase( resSym );

	lprintf( "Remove %I64d res %s\n", removed, pResName );
}


ResourcePtr ResourceMgr::GetResource( const char * const pResName, const util::Symbol &type )
{
	//lprintf( "Get res %s of type %s\n", pResName, type.GetString() );

	//15 max chars on an extension plus 0
	char extBuf[ c_maxExt ];

	GetTail( pResName, extBuf, c_maxExt );

	const util::Symbol extSym( extBuf );

	const util::Symbol resSym( pResName );

	ResourcePtr resource; // = s_MapTknToResource[ resTkn ];

	//HACK: scripts create new resources when loaded.
	if( extSym != util::Symbol( "script" ) )
	{
		resource = s_mapSymToResource[ resSym ];
	}
	
	if( resource != NULL )
	{
		return resource;
	}

	if( extBuf[0] != 0 )
	{
		MapExtToMapTypeToCreator::iterator it = s_mapExtToCreator.find( extSym );
			
		ResourcePtr res;

		if( it != s_mapExtToCreator.end() )
		{
			MapTypeToCreator::iterator itCreate;
				
			//HACK:
			if( it->second.size() == 1 )
			{
				itCreate = it->second.begin();
			}
			else
			{
				itCreate = it->second.find( type );
			}
				
			if( itCreate != it->second.end() )
			{					
				FnCreator fnCreator = itCreate->second;

				lprintf( "Creating new resource %s\n", type.GetString() );

				res = fnCreator( pResName, type );
			}
			else
			{
				ASSERT( false && "False now that we have a useful config system" );

				lprintf( "Broken path\n" );

				//Create a null resource and return it.
				res = ResourcePtr( cast<Resource *>( Serialization::CreateClassFromTypeName_base( type ) ) );
			}					
		}
		else
		{
			lprintf( "Fallback to using load\n" );

			// Fall back to serializing the type if you dont have an explicit creator.  
			res = ResourcePtr( cast<Resource *>( Serialization::CreateClassFromTypeName_base( type ) ) );

			res->ResourceMgr_setFilename( util::RuntimeString( pResName ) );

			res->load( pResName, extSym );

		}
			
		//TODO: Handle using default resources here.
		if( res != NULL )
		{
			lprintf( "Storing res %s\n", pResName );

			res->ResourceMgr_setFilename( util::RuntimeString( pResName ) );

			// @@@@ PERF HACK
			/*
			if( extSym != util::Symbol( "verts" ) && 
				extSym != util::Symbol( "indices" ) &&
				resSym != util::Symbol( "config/geo/test.xml" ) 
					)
			//*/
			{
				const i64 resCount1 = res.use_count();

				s_mapSymToResource[resSym] = res;
				res->onPostLoad();

				const i64 resCount2 = res.use_count();

			}

		}
		else
		{
			// @@@@ TODO Add fallback code here.  
		}
			
		return res;
	}
	
	return resource;
}

void ResourceMgr::Tick()
{
	if( s_watcher != NULL )
	{
		cb::vector<cb::DirChangeRecord> changedDirs;
		
		if( s_watcher->GetDirChanges( &changedDirs ) )
		{
			//14 changes for 1 real file save (at least from dev studio)
			for( int i = 0; i < changedDirs.size(); ++i )
			{
				const cb::DirChangeRecord &change = changedDirs[i];
				
				//Numbers are from the DirChangeWatcher header
				if( change.action == 3 || change.action == 5 )
				{
					const char *pDir = change.path;
					
					if( pDir[0] == '.' && pDir[1] == '\\' )
					{
						pDir = pDir + 2;
					}
					
					ResourcePtr res = LookupResource( pDir );
					
					if( res != NULL )
					{
						lprintf( "Resource has changed %s\n", pDir );

						//Hook recreation here.. 
						//const int originalRefCount = res->GetRefCount();
						

						char *pBuf = (char *)Serialization::CreateClassFromTypeName_base( res->Class(), (char *)res.get() );
						
						ASSERT( pBuf == (char *)res.get() );
						
						//res->SetRefCount( originalRefCount );
						
						//res->load( pDir, extSym );
					}
				}
				
			}
		}
		
		
	}
	
	
	
	
	
	
	
}
















// -